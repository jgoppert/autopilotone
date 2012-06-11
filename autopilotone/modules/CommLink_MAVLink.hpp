#ifndef AUTOPILOTONE_MODULES_COMMLINK_MAVLink_HPP_
#define AUTOPILOTONE_MODULES_COMMLINK_MAVLink_HPP_

#include <autopilotone/autopilotone.hpp>
#include <mavlink/v1.0/common/mavlink.h>

namespace autopilotone {

class CommLink_MAVLink : public CommLink {
public:
    CommLink_MAVLink(const uint8_t sysid, const uint8_t compid, const MAV_TYPE type,
                     BoardInterface * board,
                     NavigatorInterface * navigator,
                     GuideInterface * guide,
                     ControllerInterface * controller) :
        CommLink(board,navigator,guide,controller),
        m_system(), m_status() {

        // system
        m_system.sysid = sysid;
        m_system.compid = compid;
        m_system.type = type;
    }
    void send() {
        // attitude states (rad)
        float roll = 1;
        float pitch = 2;
        float yaw = 3;

        // body rates
        float rollRate = 0.1;
        float pitchRate = 0.2;
        float yawRate = 0.3;

        // position
        int32_t lat = 1*m_rad2deg*1e7;
        int32_t lon = 2*m_rad2deg*1e7;
        int16_t alt = 3*1e3;

        int16_t vx = 1*1e2;
        int16_t vy = 2*1e2;
        int16_t vz = -3*1e2;

        int16_t xacc = 1*1e3;
        int16_t yacc = 2*1e3;
        int16_t zacc = 3*1e3;

        mavlink_message_t msg;
        mavlink_msg_hil_state_pack(m_system.sysid, m_system.compid, &msg,
                                   get_board()->get_clock()->get_micros()/1000000.0,
                                   roll,pitch,yaw,
                                   rollRate,pitchRate,yawRate,
                                   lat,lon,alt,
                                   vx,vy,vz,
                                   xacc,yacc,zacc);
        sendMessage(msg);
    }
    void receive() {
        mavlink_message_t msg;
        while(get_board()->get_serial()->available())
        {
            uint8_t c = get_board()->get_serial()->read();

            // try to get new message
            if(mavlink_parse_char(MAVLINK_COMM_0,c,&msg,&m_status))
            {
                switch(msg.msgid)
                {

                case MAVLINK_MSG_ID_HIL_CONTROLS:
                {
                    //std::cout << "receiving messages" << std::endl;
                    mavlink_hil_controls_t hil_controls;
                    mavlink_msg_hil_controls_decode(&msg,&hil_controls);
                    std::cout << "roll: " << hil_controls.roll_ailerons << std::endl;
                    std::cout << "pitch: " << hil_controls.pitch_elevator << std::endl;
                    std::cout << "yaw: " << hil_controls.yaw_rudder << std::endl;
                    std::cout << "throttle: " << hil_controls.throttle << std::endl;
                    std::cout << "mode: " << hil_controls.mode << std::endl;
                    std::cout << "nav mode: " << hil_controls.nav_mode << std::endl;
                    break;
                }

                default:
                {
                    std::cout << "received message: " << uint32_t(msg.msgid) << std::endl;
                }

                }
            }
        }
    }
    void update() {
        send();
        receive();
    }
private:

    // private attributes

    mavlink_system_t m_system;
    mavlink_status_t m_status;
    static const double m_rad2deg = 180.0/3.14159;

    // private methods

    // send a mavlink message to the comm port
    void sendMessage(const mavlink_message_t & msg) {
        uint8_t buf[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
        get_board()->get_serial()->write((const char *)buf, len);
    }
};

}

#endif /* AUTOPILOTONE_MODULES_COMMLINK_MAVLink_HPP_ */
