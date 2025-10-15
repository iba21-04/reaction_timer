#include <stdio.h>
#include <stdint.h>
#include "joystick.h"
#include <stdlib.h>
#include <math.h>

joystick_direction joystick_get_direction(int ch0, int ch1)
{
    int x = ch0 - CENTER_X;
    int y = ch1 - CENTER_Y;

    if (y > THRESHOLD)
        return JOY_UP;
    else if (y < -THRESHOLD)
        return JOY_DOWN;
    else if (x > THRESHOLD)
        return JOY_RIGHT;
    else if (x < -THRESHOLD)
        return JOY_LEFT;
    else
        return JOY_CENTER;
}
