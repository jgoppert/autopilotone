#ifndef APO_COMMLINK_H
#define APO_COMMLINK_H


#include "Task.h"

namespace APO { class AutoPilot; } 

namespace APO {

class CommLink : public Task {
  protected:
    AutoPilot * autoPilot;

};

} // namespace APO
#endif
