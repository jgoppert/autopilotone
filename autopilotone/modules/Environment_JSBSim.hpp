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

class Environment_JSBSim : public Environment {
public:
    Environment_JSBSim(BoardInterface * board) :
        Environment(board),
        m_channel("127.0.0.1", "5124", "tcp")
    {
        if (!m_channel.open(SG_IO_OUT)) {
            throw std::runtime_error("failed to connect to jsbsim channel");
        }
        send("pause\n");
        send("resume\n");
    }
    void update() {
        set("fcs/aileron-cmd-norm",sin(get_board()->get_clock()->get_micros()/1000000.0));
        std::cout << "environment jsbsim update" << std::endl;
        std::cout << "aileron: " << get("fcs/aileron-cmd-norm") << std::endl;
    }
    void send(const char * string) {
        m_channel.writestring(string);
    }
    void set(const char * variable, const char * value) {
        char buf[1000];
        sprintf(buf,"set %s %s\n",variable,value);
        send(buf);
    }
    void set(const char * variable, const float & value) {
        char buf[1000];
        sprintf(buf,"set %s %f\n",variable,value);
        send(buf);
    }
    double get(const char * variable) {
        char buf[1000];
        sprintf(buf,"get %s\n",variable);
        send(buf);
        char readbuf[1000];
        uint16_t bytes = m_channel.readline(readbuf,1000);
        float val = 0;
        char name[50];
        sscanf(readbuf,"JSBSim> JSBSim> %s = %f\n",name,&val);
        if (strcmp(variable,name)) {
            std::cout  << "failed to receive proper message from jsbsim: " << readbuf << std::endl;
        }
        return val;
    }
private:
    SGSocket m_channel;
    //SGSocket m_channelReceive;
    Mutex m_mutex;
};

}

#endif /* AUTOPILOTONE_MODULES_ENVIRONMENT_JSBSIM_HPP_ */
