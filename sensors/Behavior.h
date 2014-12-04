#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Runner.h"

class Behavior {
public:
  Behavior(Runner& runner)
    : runner(runner) {}
  virtual void tick(const int& val_l, const int& val_c, const int& val_r) = 0;
protected:
  Runner& runner;
};

class BehaviorNull: public Behavior {
  void tick() {}
};

class BehaviorFollowCenter: public Behavior {
public:
  BehaviorFollowCenter(Runner& runner)
    : Behavior(runner) {}
  
  void tick(const int& val_l, const int& val_c, const int& val_r) {
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
    
    // Default: Go backward
    runner.run(-5, -5);
    return;
  }
};

class BehaviorFollowLeft: public Behavior {
public:
  BehaviorFollowLeft(Runner& runner)
    : Behavior(runner), behavior_follow_center(runner) {}
  
  void tick(const int& val_l, const int& val_c, const int& val_r) {
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
private:
  BehaviorFollowCenter behavior_follow_center;
};

class BehaviorFollowRight: public Behavior {
public:
  BehaviorFollowRight(Runner& runner)
    : Behavior(runner), behavior_follow_center(runner) {}
  
  void tick(const int& val_l, const int& val_c, const int& val_r) {
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
private:
  BehaviorFollowCenter behavior_follow_center;
};

#endif // BEHAVIOR_H

