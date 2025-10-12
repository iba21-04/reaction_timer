#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "led.h"

// File paths for LED control on BeagleBone
#define GREEN_TRIGGER_PATH "/sys/class/leds/ACT/trigger"
#define GREEN_BRIGHTNESS_PATH "/sys/class/leds/ACT/brightness"

#define RED_TRIGGER_PATH "/sys/class/leds/PWR/trigger"
#define RED_BRIGHTNESS_PATH "/sys/class/leds/PWR/brightness"
// for nanosleep
#define _POSIX_C_SOURCE 200809L

static void disableLedTrigger(const char *triggerPath);
static void writeBrightness(const char *brightnessPath, int value);

// initialize the led
void led_init(void)
{
    disableLedTrigger(GREEN_TRIGGER_PATH);
    disableLedTrigger(RED_TRIGGER_PATH);
}

// set green led on or off
void led_setGreen(int on)
{
    writeBrightness(GREEN_BRIGHTNESS_PATH, on ? 1 : 0);
}

// set red led on or off
void led_setRed(int on)
{
    writeBrightness(RED_BRIGHTNESS_PATH, on ? 1 : 0);
}

// flash green led 'times' times
void led_flashGreen(int times, int delayMs)
{
    for (int i = 0; i < times; ++i)
    {
        led_setGreen(1);
        led_sleepMs(delayMs);
        led_setGreen(0);
        led_sleepMs(delayMs);
    }
}

// flash red led 4 times
void led_flashRed(int times, int delayMs)
{
    for (int i = 0; i < times; ++i)
    {
        led_setRed(1);
        led_sleepMs(delayMs);
        led_setRed(0);
        led_sleepMs(delayMs);
    }
}

// cleanup the led
void led_off(void)
{
    led_setGreen(0);
    led_setRed(0);
}

//**********helper functions*****************//

// helper funtion to disable the led trigger
static void disableLedTrigger(const char *triggerPath)
{
    FILE *f = fopen(triggerPath, "w");
    if (!f)
    {
        perror("Error opening LED trigger file");
        exit(EXIT_FAILURE);
    }

    if (fprintf(f, "none") <= 0)
    {
        perror("Error writing to LED trigger file");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    fclose(f);
    led_sleepMs(100);
}

// helper function to write brightness value to brightness file
static void writeBrightness(const char *brightnessPath, int value)
{
    FILE *f = fopen(brightnessPath, "w");
    if (!f)
    {
        perror("Error opening LED brightness file");
        exit(EXIT_FAILURE);
    }
    if (fprintf(f, "%d", value) <= 0)
    {
        perror("Error writing to LED brightness file");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    fclose(f);
}

// helper function for sleep in ms
void led_sleepMs(long long ms)
{
    const long long ns_per_ms = 1000000;
    long long delay = ms * ns_per_ms;
    struct timespec req = {
        .tv_sec = delay / 1000000000,
        .tv_nsec = delay % 1000000000};
    nanosleep(&req, NULL);
    // reference: LED Guide
}
