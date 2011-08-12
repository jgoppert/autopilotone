#ifndef APO_CONTROLLER_H
#define APO_CONTROLLER_H


#include "Task.h"

namespace APO { class AutoPilot; } 

namespace APO {

class Controller : public Task {
  protected:
    AutoPilot * autoPilot;

};

} // namespace APO
#endif
