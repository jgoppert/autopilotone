#ifndef APO_INTERFACES_HPP_
#define APO_INTERFACES_HPP_

#include <inttypes.h>
#include <string>
#include "apoMacros.hpp"

namespace apo {

// Component Interface
struct MutexInterface {
    virtual bool try_lock() = 0;
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

struct DebugInterface {
    virtual void send(const std::string & str) = 0;
};

// null debug object
class NullDebug : public DebugInterface {
public:
    virtual void send(const std::string & str) {};
} nullDebug;

struct ComponentInterface {
    virtual void update() = 0;
    virtual void set_debug(DebugInterface * debug) = 0;
    virtual DebugInterface * get_debug() = 0;
};

// Time
struct ClockInterface {
    virtual void sleepMicros(uint64_t micros) = 0;
    virtual uint64_t get_micros() = 0;
};

struct NavigatorReadInterface {
    virtual int32_t get_lat_degE7() = 0;
    virtual int32_t get_lon_degE7() = 0;
    virtual int16_t get_alt_degE3() = 0;
    virtual float get_lat() = 0;
    virtual float get_lon() = 0;
    virtual float get_alt() = 0;
    virtual float get_vNorth() = 0;
    virtual float get_vEast() = 0;
    virtual float get_vDown() = 0;
    virtual float get_roll() = 0;
    virtual float get_pitch() = 0;
    virtual float get_yaw() = 0;
    virtual float get_rollRate() = 0;
    virtual float get_pitchRate() = 0;
    virtual float get_yawRate() = 0;
};

struct NavigatorWriteInterface {
    virtual void set_lat_degE7(int32_t val) = 0;
    virtual void set_lon_degE7(int32_t val) = 0;
    virtual void set_alt_degE3(int16_t val) = 0;
    virtual void set_lat(float val) = 0;
    virtual void set_lon(float val) = 0;
    virtual void set_alt(float val) = 0;
    virtual void set_vNorth(float val) = 0;
    virtual void set_vEast(float val) = 0;
    virtual void set_vDown(float val) = 0;
    virtual void set_roll(float val) = 0;
    virtual void set_pitch(float val) = 0;
    virtual void set_yaw(float val) = 0;
    virtual void set_rollRate(float val) = 0;
    virtual void set_pitchRate(float val) = 0;
    virtual void set_yawRate(float val) = 0;
};

struct NavigatorInterface :
    public NavigatorReadInterface,
    public NavigatorWriteInterface,
    public ComponentInterface
{
};

// Guide
struct Command {
    int32_t lat_degIntE7;
    int32_t lon_degIntE7;
    int16_t alt_degIntE3;
    float velocity;
    float heading;
    int param3;
    int param4;
};

enum guideMode_t {
    GUIDE_MODE_AUTO=0,
    GUIDE_MODE_MANUAL,
    GUIDE_MODE_COUNT
};

struct GuideReadInterface {
    //virtual uint16_t get_currentCommandIndex() = 0;
    //virtual uint16_t get_lastCommandIndex() = 0;
    //virtual uint16_t get_nextCommandIndex() = 0;
    //virtual uint16_t get_commandCount() = 0;
    //virtual Waypoint get_command(uint16_t index) = 0;
    //virtual guideMode_t get_mode() = 0;
};

struct GuideWriteInterface {
    //virtual void addWaypoint(uint16_t index, Waypoint waypoint) = 0;
    //virtual void removeWaypoint(uint16_t index) = 0;
    //virtual void clearWaypoints() = 0;
    //virtual set_mode(guideMode_t mode) = 0;
};

struct GuideInterface :
    public GuideReadInterface,
    public GuideWriteInterface,
    public ComponentInterface
{
};

// Controller
enum controllerMode_t {
    CONTROLLER_MODE_COUNT
};

struct ControllerReadInterface {
    //virtual controllerMode_t get_mode() = 0;
};

struct ControllerWriteInterface {
    //virtual set_mode(controllerMode_t mode) = 0;
};

struct ControllerInterface :
    public ControllerReadInterface,
    public ControllerWriteInterface,
    public ComponentInterface
{
};

// CommLink
struct CommLinkReadInterface {
};

struct CommLinkWriteInterface {
};

struct CommLinkInterface :
    public CommLinkReadInterface,
    public CommLinkWriteInterface,
    public ComponentInterface
{
};

} // namespace apo

#endif
