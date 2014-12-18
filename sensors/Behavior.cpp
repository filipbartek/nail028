#include "Behavior.h"

void
BehaviorFollowCenter::tick(const boolean& val_l, const boolean& val_c, const boolean& val_r) {
  if ((val_c && !val_l && !val_r) || (val_l && val_r)) {
    // Go forward
    runner.run(90, 90);
    return;
  }
  
  if (val_l && !val_r) {
    // Go left
    if (val_c) {
      // Go left weak
      runner.run(0, 90);
      return;
    } else {
      // Go left strong
      runner.run(-90, 90);
      return;
    }
  }
  
  if (val_r && !val_l) {
    // Go right
    if (val_c) {
      // Go right weak
      runner.run(90, 0);
      return;
    } else {
      // Go right strong
      runner.run(90, -90);
      return;
    }
  }
  
  // Default: Go slowly forward
  runner.run(20, 20);
  return;
}

void
BehaviorFollowLeft::tick(const boolean& val_l, const boolean& val_c, const boolean& val_r) {
  if (val_l && val_r) {
    // Go left weak
    runner.run(0, 90);
    return;
  }
  
  if (val_r && val_c && !val_l) {
    // Go forward
    runner.run(90, 90);
    return;
  }
  
  behavior_follow_center.tick(val_l, val_c, val_r);
}

void
BehaviorFollowRight::tick(const boolean& val_l, const boolean& val_c, const boolean& val_r) {
  if (val_l && val_r) {
    // Go right weak
    runner.run(90, 0);
    return;
  }
  
  if (val_l && val_c && !val_r) {
    // Go forward
    runner.run(90, 90);
    return;
  }
  
  behavior_follow_center.tick(val_l, val_c, val_r);
}

