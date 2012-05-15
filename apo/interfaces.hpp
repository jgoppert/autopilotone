#ifndef APO_INTERFACES_HPP_
#define APO_INTERFACES_HPP_

#include <inttypes.h>
#include <string>

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

struct ComponentInterface {
    virtual void update() = 0;
    virtual void setDebug(DebugInterface * debug) = 0;
    virtual DebugInterface * getDebug() = 0;
};

// Navigator
enum navState_t {
    NAV_LAT=0,
    NAV_LON,
    NAV_ALT,
    NAV_V_NORTH,
    NAV_V_EAST,
    NAV_V_DOWN,
    NAV_ROLL,
    NAV_PITCH,
    NAV_YAW,
    NAV_ROLL_RATE,
    NAV_PITCH_RATE,
    NAV_YAW_RATE,
    NAV_COUNT
};

enum navInt16State_t {
    NAV_INT_ALT_DEGE3,
    NAV_INT16_COUNT
};

enum navInt32State_t {
    NAV_INT32_LAT_DEGE7=0,
    NAV_INT32_LON_DEGE7,
    NAV_INT32_COUNT
};

struct NavigatorReadInterface {
    virtual float get(navState_t navState) = 0;    
    virtual int32_t get(navInt32State_t navState) = 0;    
    virtual int16_t get(navInt16State_t navState) = 0;    
};

struct NavigatorWriteInterface {
    virtual void set(navState_t navState, float val) = 0;    
    virtual void set(navInt32State_t navState, int32_t val) = 0;    
    virtual void set(navInt16State_t navState, int16_t val) = 0;    
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
    //virtual uint16_t getCurrentCommandIndex() = 0;
    //virtual uint16_t getLastCommandIndex() = 0;
    //virtual uint16_t getNextCommandIndex() = 0;
    //virtual uint16_t getCommandCount() = 0;
    //virtual Waypoint getCommand(uint16_t index) = 0;
    //virtual guideMode_t getMode() = 0;
};

struct GuideWriteInterface {
    //virtual void addWaypoint(uint16_t index, Waypoint waypoint) = 0;
    //virtual void removeWaypoint(uint16_t index) = 0;
    //virtual void clearWaypoints() = 0;
    //virtual setMode(guideMode_t mode) = 0;
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
    //virtual controllerMode_t getMode() = 0;
};

struct ControllerWriteInterface {
    //virtual setMode(controllerMode_t mode) = 0;
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
