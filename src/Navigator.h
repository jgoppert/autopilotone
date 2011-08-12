#ifndef APO_NAVIGATOR_H
#define APO_NAVIGATOR_H


#include "Task.h"

namespace APO { class AutoPilot; } 

namespace APO {

class Navigator : public Task {
  protected:
    AutoPilot * autoPilot;

};

} // namespace APO
#endif
