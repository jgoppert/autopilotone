autopilotone: A universal autopilot interface library.

Features:
* Standardizes guidance/navigatoin/control module interfaces so that they can be used on any autopilot running autopilotone.
* Limits access to components for security and better object-oriented design.
* Thread-safe: Can run on multi-threaded applications. Each component( guide, navigator, control) is assumed to run in a unique thread. Communication between modules is garunteed thread-safe through the use of mutex locks.
* Mutex locks are added per attribute, to ensure little time is wasted waiting for a lock. This had memory overhead of 1 byte/ attribute as a trade-off.

Requirements:
* C++
* OS:
    * Currently supports Unix/ Windows for pc build.
    * Planned support for ArduPilotMega. 
    * Planned support for PX4

Future Plans:
* Add alternative subscription based mult-threading environment for comparison. 
