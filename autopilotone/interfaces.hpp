#ifndef AUTOPILOTONE_INTERFACES_HPP_
#define AUTOPILOTONE_INTERFACES_HPP_

#include <inttypes.h>
#include "macros.hpp"

namespace autopilotone {

/**
 * Constants
 */
float deg2rad = 3.14159/180.0;

/**
 * Threading
 */
struct MutexInterface {
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual ~MutexInterface() {};
};

class ScopedLock {
public:
    inline ScopedLock(MutexInterface & l) : lock(l) { lock.lock(); }
    inline ~ScopedLock() { lock.unlock(); }
private:
    MutexInterface & lock;

    // disable copying
    ScopedLock(const ScopedLock&);
    ScopedLock& operator = (const ScopedLock&);
};

struct ProcessInterface {
    virtual void update() = 0;
    virtual ~ProcessInterface() {};
};

/**
 * Debug
 */
struct DebugInterface {
    virtual void write(const char * buf, uint32_t bytes) = 0;
    virtual void writeString(const char * buf) = 0;
    virtual ~DebugInterface() {};
};

/**
 * General
 */
struct ClockInterface {
    virtual void sleepMicros(uint64_t micros) = 0;
    virtual uint64_t get_micros() = 0;
    virtual ~ClockInterface() {};
};

/**
 * Navigator
 */
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
    virtual ~NavigatorReadInterface() {};
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
    virtual ~NavigatorWriteInterface() {};
};

struct NavigatorInterface :
    public NavigatorReadInterface,
    public NavigatorWriteInterface,
    public ProcessInterface
{
    virtual ~NavigatorInterface() {};
};

/**
 * Guide
 */
struct Command {
    int32_t lat_degIntE7;
    int32_t lon_degIntE7;
    int16_t alt_degIntE3;
    float velocity;
    float heading;
    int param3;
    int param4;
};

struct FlightPlanReadInterface {
    virtual uint16_t get_currentCommandIndex() = 0;
    virtual uint16_t get_lastCommandIndex() = 0;
    virtual uint16_t get_nextCommandIndex() = 0;
    virtual uint16_t get_commandCount() = 0;
    virtual Command get_command(uint16_t index) = 0;
    virtual Command get_currentCommand() = 0;
    virtual ~FlightPlanReadInterface() {};
};

struct FlightPlanWriteInterface {
    virtual void addWaypoint(uint16_t index, Command waypoint) = 0;
    virtual void removeWaypoint(uint16_t index) = 0;
    virtual void clearWaypoints() = 0;
    virtual ~FlightPlanWriteInterface() {};
};

struct FlightPlanInterface :
    public FlightPlanReadInterface,
    public FlightPlanWriteInterface
{
};

enum guideMode_t {
    GUIDE_MODE_AUTO=0,
    GUIDE_MODE_MANUAL,
    GUIDE_MODE_COUNT
};

struct GuideReadInterface {
    virtual FlightPlanInterface * get_flightPlan() = 0;
    virtual guideMode_t get_mode() = 0;
    virtual float get_latError_degFloat() = 0;
    virtual float get_lonError_degFloat() = 0;
    virtual float get_altError_ftFloat() = 0;
    virtual ~GuideReadInterface() {};
};

struct GuideWriteInterface {
    virtual void set_flightPlan(FlightPlanInterface * flightPlan) = 0;
    virtual void set_mode(guideMode_t mode) = 0;
    //virtual float update_error() = 0;
    virtual ~GuideWriteInterface() {};
};

struct GuideInterface :
    public GuideReadInterface,
    public GuideWriteInterface,
    public ProcessInterface
{
};

/**
 * Controller
 */
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
    public ProcessInterface
{
    virtual ~ControllerInterface() {};
};


/**
 * CommLink
 */
struct CommLinkReadInterface {
};

struct CommLinkWriteInterface {
};

struct CommLinkInterface :
    public CommLinkReadInterface,
    public CommLinkWriteInterface,
    public ProcessInterface
{
    virtual ~CommLinkInterface() {};
};

struct SerialPortInterface : public ProcessInterface {
    virtual bool available() = 0;
    virtual uint8_t read() = 0;
    virtual void write(const char * c, uint32_t bytes) = 0;
    virtual void writeString(const char * c) = 0;
    virtual ~SerialPortInterface() {};
};

class BoardInterface;

/**
 * Environment Simulation
 */
struct EnvironmentReadInterface : public NavigatorReadInterface {
    virtual ~EnvironmentReadInterface() {};
};

struct EnvironmentWriteInterface : public NavigatorWriteInterface {
    virtual ~EnvironmentWriteInterface() {};
};

struct EnvironmentInterface :
    public EnvironmentReadInterface,
    public EnvironmentWriteInterface,
    public ProcessInterface
{
    virtual BoardInterface * get_board() = 0;
    virtual ~EnvironmentInterface() {};
};

/**
 * Board
 */
struct BoardInterface {
    virtual ClockInterface * get_clock() = 0;
    virtual SerialPortInterface * get_serialPort() = 0;
    virtual DebugInterface * get_debug() = 0;
    virtual EnvironmentReadInterface * get_environment() = 0;
    virtual ~BoardInterface() {};
};


} // namespace autopilotone

#endif
