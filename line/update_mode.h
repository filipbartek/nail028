#ifndef UPDATE_MODE_H
#define UPDATE_MODE_H

#include "Body.h"

// Mode of movement - low level
enum Mode { WAIT, FORWARD, LEFT, RIGHT, LEFT_STRONG, RIGHT_STRONG };
// WAIT: Wait for button press

// Mode of line following - high level
enum ModeFollow { FOLLOW_CENTER, FOLLOW_LEFT, FOLLOW_RIGHT };

// Modifies mode if necessary
void
update_mode(Mode& mode, const ModeFollow& mode_follow, const Body& body);

#endif // UPDATE_MODE_H
