#ifndef AUTOPILOTONE_MODULES_ENVIRONMENT_JSBSIM_HPP_
#define AUTOPILOTONE_MODULES_ENVIRONMENT_JSBSIM_HPP_

#ifndef OS_PC
#error Environment can only be constructed on PC
#endif

#include <autopilotone/autopilotone.hpp>
#include <simgear/io/sg_socket.hxx>
#include <cstdio>
#include <cstdlib>

namespace autopilotone {

int hd(std::string s1, std::string s2) {
    // hd stands for "Hamming Distance"
    int dif = 0;

    uint16_t size = std::min(s1.size(),s2.size());
    for (unsigned i = 0; i < size; i++ ) {
        std::string b1 = s1.substr(i,1);
        std::string b2 = s2.substr(i,1);

        if (b1 != b2) {
                dif++;
        }
    }  

    return dif;
}

class Environment_JSBSim : public Environment {
public:
    static const float ft2m = 0.3048;
    Environment_JSBSim(BoardInterface * board) :
        Environment(board),
        m_channel("127.0.0.1", "5124", "tcp")
    {
        if (!m_channel.open(SG_IO_OUT)) {
            throw std::runtime_error("failed to connect to jsbsim channel");
        }
        expect("Connected to JSBSim server\nJSBSim>");
        resume();
    }
    void update() {
        set("fcs/aileron-cmd-norm",sin(get_board()->get_clock()->get_micros()/1000000.0));
        std::cout << "environment jsbsim update" << std::endl;
        std::cout << "aileron: " << get("fcs/aileron-cmd-norm") << std::endl;

        set_lat_degE7(get("position/lat-geod-deg")*1e7);
        set_lon_degE7(get("position/long-gc-deg")*1e7);
        set_asl_mE3(get("position/h-sl-meters"));
        set_agl_mE3(get("position/h-agl-ft")*ft2m);

        std::cout << "lat: " << get_lat_degE7() << std::endl;
    }
    void hold() {
        send("hold\r\n");
        expect("JSBSim>");
    }
    void resume() {
        send("resume\r\n");
        expect("JSBSim>");
    }
    void send(const std::string & string) {
        //std::cout << string << std::endl;
        m_channel.writestring(string.c_str());
    }
    std::string receive() {
        int length = 1000;
        char buf[length];
        memset(buf,' ',length);
        int bytes = 0;
        while(1) {
            bytes = m_channel.read(buf,length);
            if (bytes>length) {
                bytes = length;
            } else if (bytes < 0) {
                bytes = 0;
            }
            if (bytes !=0) {
                break;
            } else {
                usleep(1000);
                //std::cout << "waiting for message" << std::endl;
            }
        }
        //std::cout << "bytes read: " << bytes << std::endl;
        std::string out(buf,bytes);
        return out;
    }
    void set(const char * variable, const char * value) {
        //std::cout << "==================================" << std::endl;
        std::ostringstream stream;
        stream << "set " << variable << " " << value << std::endl;
        send(stream.str());
        expect("JSBSim>");
        //std::cout << "==================================" << std::endl;
    }
    void set(const char * variable, const float & value) {
        //std::cout << "==================================" << std::endl;
        std::ostringstream stream;
        stream << "set " << variable << " " << value << std::endl;
        send(stream.str());
        expect("JSBSim>");
        //std::cout << "==================================" << std::endl;
    }
    void expect(const std::string & string) {
        std::string response = receive();
        if (response.size()==0) {
            std::ostringstream stream;
            stream << "expected: " << string << ", received no response" << std::endl;
            throw std::runtime_error(stream.str());
        }
        uint16_t diff = hd(response,string);
        if (diff != 0) {
            std::ostringstream stream;
            stream << "expected: " << string << ", received: " << response << std::endl;
            stream << "diff: " << diff << std::endl;
            stream << "bytes: " << response.size() << std::endl;
            throw std::runtime_error(stream.str());
        }
        //std::cout << "expect received: " << response << std::endl;
        //std::cout << "bytes: " << response.size() << std::endl;
    }
    double get(const std::string variable) {
        //std::cout << "==================================" << std::endl;

        std::ostringstream stream;
        hold();
        stream << "get " << variable << std::endl;
        send(stream.str());

        float val = 0;
        char name[100];

        std::string response = receive();
        expect("JSBSim>");
        if (response.size() == 0) {
            throw std::runtime_error("failed to receive a message from jsbsim");
        }
        if (!sscanf(response.c_str(),"%s = %f\r\n",name,&val)) {
            std::ostringstream stream;
            stream << "failed to receive proper message from jsbsim: " << response << std::endl;
            throw std::runtime_error(stream.str());
        }
        if (hd(name,variable) != 0) {
            std::ostringstream stream;
            stream << "wronge message name: " << name << ", expected: " << variable << std::endl;
            throw std::runtime_error(stream.str());

            throw std::runtime_error("wrong message");
        }
        //std::cout << "response: " << response << std::endl;
        //std::cout << "name: " << name << std::endl;
        //std::cout << "value: " << val << std::endl;
        //std::cout << "==================================" << std::endl;
        resume();
        return val;
    }
private:
    SGSocket m_channel;
    //SGSocket m_channelReceive;
    Mutex m_mutex;
};

}

#endif /* AUTOPILOTONE_MODULES_ENVIRONMENT_JSBSIM_HPP_ */
