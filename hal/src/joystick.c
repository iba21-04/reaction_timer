#include <stdio.h>
#include <stdint.h>
#include "joystick.h"
#include <stdlib.h>
#include <math.h>

JoystickDirection joystick_get_direction(int ch0, int ch1)
{
    int dx = ch0 - CENTER_X;
    int dy = ch1 - CENTER_Y;

    if (abs(dx) < DEADZONE && abs(dy) < DEADZONE)
        return JOY_CENTER;

    if (dy > THRESHOLD)
        return JOY_UP;
    else if (dy < -THRESHOLD)
        return JOY_DOWN;
    else if (dx > THRESHOLD)
        return JOY_RIGHT;
    else if (dx < -THRESHOLD)
        return JOY_LEFT;
    else
        return JOY_CENTER;
}
