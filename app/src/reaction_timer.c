#include <stdio.h>
#include "led.h"
// #include "joystick.h"
#include "reaction_timer.h"

void reaction_timer_run(void)
{
    printf("Welcome to Reaction Timer Game!\n");
    // Step 1: Flash LEDs 4 times to start
    for (int i = 0; i < 4; ++i)
    {
        led_setGreen(1);
        led_sleepMs(250);
        led_setGreen(0);
        led_sleepMs(100);
        led_setRed(1);
        led_sleepMs(250);
        led_setRed(0);
        led_sleepMs(100);
    }
}
