#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

// Calibration constants (you can tweak later)
#define CENTER_X 2080
#define CENTER_Y 2050
#define THRESHOLD 450
#define DEADZONE 150

// Direction enum
typedef enum
{
    JOY_CENTER,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
} joystick_direction;

// Function declarations
joystick_direction joystick_get_direction(int ch0, int ch1);

#endif // JOYSTICK_H
