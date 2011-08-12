#ifndef APO_GUIDE_H
#define APO_GUIDE_H


#include "Task.h"

namespace APO { class AutoPilot; } 

namespace APO {

class Guide : public Task {
  protected:
    AutoPilot * autoPilot;

};

} // namespace APO
#endif
