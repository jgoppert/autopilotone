#ifndef APO_INTERFACES_HPP_
#define APO_INTERFACES_HPP_

#include <inttypes.h>
#include "os/os.hpp"

namespace apo {

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

struct NavigatorInterface : public NavigatorReadInterface, NavigatorWriteInterface {
    virtual void update() = 0;
};

// Guide
struct Waypoint {
    int32_t lat_degIntE7;
    int32_t lon_degIntE7;
    int16_t alt_degIntE3;
    float param1;
    float param2;
    int param3;
    int param4;
};

struct GuideReadInterface {
};

struct GuideWriteInterface {
};

struct GuideInterface : public GuideReadInterface, GuideWriteInterface {
    virtual void update() = 0;
};

// Controller
struct ControllerReadInterface {
};

struct ControllerWriteInterface {
};

struct ControllerInterface : public ControllerReadInterface, ControllerWriteInterface {
    virtual void update() = 0;
};

// CommLink
struct CommLinkReadInterface {
};

struct CommLinkWriteInterface {
};

struct CommLinkInterface : public CommLinkReadInterface, CommLinkWriteInterface {
    virtual void update() = 0;
};

} // namespace apo

#endif
