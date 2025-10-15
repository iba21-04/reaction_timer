#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

// Calibration constants
#define CENTER_X 2080
#define CENTER_Y 2055
#define THRESHOLD 1000

// Direction enum
typedef enum
{
    JOY_CENTER,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
} joystick_direction;

joystick_direction joystick_get_direction(int ch0, int ch1);

#endif // JOYSTICK_H
