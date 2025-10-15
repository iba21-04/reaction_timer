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

static void disable_led_trigger(const char *triggerPath);
static void write_brightness(const char *brightnessPath, int value);

// initialize the led
void led_init(void)
{
    disable_led_trigger(GREEN_TRIGGER_PATH);
    disable_led_trigger(RED_TRIGGER_PATH);
}

// set green led on or off
void led_set_green(int on)
{
    write_brightness(GREEN_BRIGHTNESS_PATH, on ? 1 : 0);
}

// set red led on or off
void led_set_red(int on)
{
    write_brightness(RED_BRIGHTNESS_PATH, on ? 1 : 0);
}

// flash green led number of times
void led_flash_green(int times, int delayMs)
{
    for (int i = 0; i < times; ++i)
    {
        led_set_green(1);
        led_sleepMs(delayMs);
        led_set_green(0);
        led_sleepMs(delayMs);
    }
}

// flash red led number of times
void led_flash_red(int times, int delayMs)
{
    for (int i = 0; i < times; ++i)
    {
        led_set_red(1);
        led_sleepMs(delayMs);
        led_set_red(0);
        led_sleepMs(delayMs);
    }
}

// cleanup the led
void led_off(void)
{
    led_set_green(0);
    led_set_red(0);
}

//**********helper functions*****************//

// helper funtion to disable the led trigger
static void disable_led_trigger(const char *triggerPath)
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
static void write_brightness(const char *brightnessPath, int value)
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
