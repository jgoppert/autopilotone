#ifndef APO_AUTOPILOT_H
#define APO_AUTOPILOT_H


namespace APO { class Guide; } 
namespace APO { class Navigator; } 
namespace APO { class Controller; } 
namespace APO { class CommLink; } 
namespace APO { class HAL; } 

namespace APO {

class AutoPilot {
  protected:
    Guide * guide;

    Navigator * navigator;

    Controller * controller;

    CommLink * commLink;


  public:
    HAL * hal;

};

} // namespace APO
#endif
