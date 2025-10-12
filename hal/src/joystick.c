#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include "joystick.h"
// #include "read_channel.h"

// static int joystickFd = -1;
// static uint32_t spiSpeed = 500000; // default SPI speed
// static int isInitialized = 0;

// // You’ll tune these after testing raw readings
// #define JOY_CENTER_X 2048
// #define JOY_CENTER_Y 2048
// #define JOY_THRESHOLD 600

// // Channel mapping
// #define JOY_CH_Y 0 // vertical (up/down)
// #define JOY_CH_X 1 // horizontal (left/right)

// int Joystick_init(const char *spiDevice, uint32_t speed_hz)
// {
//     joystickFd = open(spiDevice, O_RDWR);
//     if (joystickFd < 0)
//     {
//         perror("Failed to open SPI device for joystick");
//         return -1;
//     }

//     spiSpeed = speed_hz;
//     isInitialized = 1;
//     return 0;
// }

void Joystick_cleanup(void)
{
    // if (joystickFd >= 0)
    // {
    //     close(joystickFd);
    //     joystickFd = -1;
    // }
    // isInitialized = 0;
}

// int Joystick_readChannel(int channel)
// {
//     assert(isInitialized);
//     return read_channel(joystickFd, channel, spiSpeed);
// }

// JoystickDirection Joystick_readDirection(void)
// {
//     assert(isInitialized);

//     int x = Joystick_readChannel(JOY_CH_X);
//     int y = Joystick_readChannel(JOY_CH_Y);

//     if (y > JOY_CENTER_Y + JOY_THRESHOLD)
//         return JOY_UP;
//     else if (y < JOY_CENTER_Y - JOY_THRESHOLD)
//         return JOY_DOWN;
//     else if (x > JOY_CENTER_X + JOY_THRESHOLD)
//         return JOY_RIGHT;
//     else if (x < JOY_CENTER_X - JOY_THRESHOLD)
//         return JOY_LEFT;
//     else
//         return JOY_NONE;
// }
