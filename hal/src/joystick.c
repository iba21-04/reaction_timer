#include <stdio.h>
#include <stdint.h>

#define CENTER_X 2080
#define CENTER_Y 2050
#define THRESHOLD 500

typedef enum
{
    JOY_CENTER,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
} JoystickDirection;

JoystickDirection joystick_get_direction(int ch0, int ch1)
{
    if (ch1 > CENTER_Y + THRESHOLD)
        return JOY_UP;
    else if (ch1 < CENTER_Y - THRESHOLD)
        return JOY_DOWN;
    else if (ch0 > CENTER_X + THRESHOLD)
        return JOY_RIGHT;
    else if (ch0 < CENTER_X - THRESHOLD)
        return JOY_LEFT;
    else
        return JOY_CENTER;
}
