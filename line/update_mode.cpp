#include "update_mode.h"

void
update_mode(Mode& mode, const ModeFollow& mode_follow, const Body& body) {
  // Works like magic!
  if (mode != WAIT) {
    const boolean l = body.sensor_l();
    const boolean c = body.sensor_c();
    const boolean r = body.sensor_r();
    
    if (l) {
      // May change to turning left
      if (!r && !c) {
        mode = LEFT;
      } else if (mode_follow == FOLLOW_LEFT) {
        mode = LEFT;
      }
    }
    if (r) {
      // May change to turning right
      if (!l && !c) {
        mode = RIGHT;
      } else if (mode_follow == FOLLOW_RIGHT) {
        mode = RIGHT;
      }
    }
    if (c) {
      // May change to going straight ahead
      if (!l && !r) {
        mode = FORWARD;
      }
      if (l && !r && mode_follow == FOLLOW_RIGHT) {
        mode = FORWARD;
      }
      if (r && !l && mode_follow == FOLLOW_LEFT) {
        mode = FORWARD;
      }
    }
    if (!l && !c && !r) {
      if (mode == LEFT) {
        mode = LEFT_STRONG;
      }
      if (mode == RIGHT) {
        mode = RIGHT_STRONG;
      }
    }
  }
}
