#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

typedef enum
{
    JOY_NONE,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
} JoystickDirection;

// Initialize and close joystick
int Joystick_init(const char *spiDevice, uint32_t speed_hz);
void Joystick_cleanup(void);

// Read current joystick direction
JoystickDirection Joystick_readDirection(void);

// Optionally, read raw channels
// int Joystick_readChannel(int channel);

#endif
