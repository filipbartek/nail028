#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Runner.h"

class Behavior {
public:
  Behavior(Runner& runner)
    : runner(runner) {}
  virtual void tick(const boolean& val_l, const boolean& val_c, const boolean& val_r) = 0;
protected:
  Runner& runner;
};

class BehaviorNull: public Behavior {
public:
  BehaviorNull(Runner& runner)
    : Behavior(runner) {}

  void tick(const boolean& val_l, const boolean& val_c, const boolean& val_r) {}
};

class BehaviorFollowCenter: public Behavior {
public:
  BehaviorFollowCenter(Runner& runner)
    : Behavior(runner) {}
  
  void tick(const boolean& val_l, const boolean& val_c, const boolean& val_r);
};

class BehaviorFollowLeft: public Behavior {
public:
  BehaviorFollowLeft(Runner& runner)
    : Behavior(runner), behavior_follow_center(runner) {}
  
  void tick(const boolean& val_l, const boolean& val_c, const boolean& val_r);
private:
  BehaviorFollowCenter behavior_follow_center;
};

class BehaviorFollowRight: public Behavior {
public:
  BehaviorFollowRight(Runner& runner)
    : Behavior(runner), behavior_follow_center(runner) {}
  
  void tick(const boolean& val_l, const boolean& val_c, const boolean& val_r);
private:
  BehaviorFollowCenter behavior_follow_center;
};

#endif // BEHAVIOR_H

