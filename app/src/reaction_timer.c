#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>

#include "led.h"
#include "joystick.h"
#include "read_channel.h"
#include "reaction_timer.h"

#define SPI_DEVICE "/dev/spidev0.0"
#define _POSIX_C_SOURCE 200809L
#define SPI_SPEED 250000

// Helper to get current time in ms
// static long long getTimeInMs(void)
// {
//     struct timespec spec;
//     clock_gettime(CLOCK_REALTIME, &spec);
//     return (long long)spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
// }

static long long getTimeInMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

void reaction_timer_run(void)
{
    printf("Welcome to Reaction Timer Game!\n");
    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit)\n");

    // --- Setup SPI ---
    int fd = open(SPI_DEVICE, O_RDWR);
    if (fd < 0)
    {
        perror("Error opening SPI device");
        return;
    }

    uint8_t mode = 0;
    uint8_t bits = 8;
    uint32_t speed = SPI_SPEED;

    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1 ||
        ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1 ||
        ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
    {
        perror("SPI setup failed");
        close(fd);
        return;
    }

    srand(time(NULL));
    long long bestTime = -1; // track fastest correct reaction

    while (1)
    {
        printf("\nGet ready...\n");

        // Step 1: Flash LEDs 4 times
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

        // Step 2: Wait for joystick release
        int warned = 0;
        JoystickDirection dir;
        int ch0, ch1;

        do
        {
            ch0 = read_channel(fd, 0, speed);
            ch1 = read_channel(fd, 1, speed);
            dir = joystick_get_direction(ch0, ch1);
            if ((dir == JOY_UP || dir == JOY_DOWN) && !warned)
            {
                printf("Please let go of joystick.\n");
                warned = 1;
            }
            led_sleepMs(100);
        } while (dir == JOY_UP || dir == JOY_DOWN);

        // Step 3: Random delay 0.5–3.0 s
        int delay = 500 + (rand() % 2500);
        led_sleepMs(delay);

        // Step 4: Too soon check
        ch0 = read_channel(fd, 0, speed);
        ch1 = read_channel(fd, 1, speed);
        dir = joystick_get_direction(ch0, ch1);
        if (dir == JOY_UP || dir == JOY_DOWN)
        {
            printf("Too soon!\n");
            continue;
        }

        // Step 5: Randomly choose Up or Down
        int choice = rand() % 2; // 0=UP, 1=DOWN
        JoystickDirection target = (choice == 0) ? JOY_UP : JOY_DOWN;

        if (target == JOY_UP)
        {
            printf("Press UP now!\n");
            led_setGreen(1);
        }
        else
        {
            printf("Press DOWN now!\n");
            led_setRed(1);
        }

        // === Step 6: Time reaction ===
        long long startTime = getTimeInMs();
        long long now = startTime;
        JoystickDirection userDir = JOY_CENTER;

        while ((now - startTime) < 5000)
        { // 5 s timeout
            ch0 = read_channel(fd, 0, speed);
            ch1 = read_channel(fd, 1, speed);
            userDir = joystick_get_direction(ch0, ch1);
            if (userDir != JOY_CENTER)
                break;
            led_sleepMs(50);
            now = getTimeInMs();
        }

        led_off(); // turn off LEDs

        if ((now - startTime) >= 5000)
        {
            printf("No input within 5000 ms; quitting!\n");
            break;
        }

        long long reactionTime = now - startTime;

        // === Step 7: Evaluate result ===
        if (userDir == JOY_LEFT || userDir == JOY_RIGHT)
        {
            printf("User selected to quit.\n");
            break;
        }
        else if (userDir == target)
        {
            printf("Correct!\n");
            if (bestTime < 0 || reactionTime < bestTime)
            {
                bestTime = reactionTime;
                printf("New best time!\n");
            }
            printf("Your reaction time was %lld ms; best so far is %lld ms.\n",
                   reactionTime, bestTime);
            led_flashGreen(5, 100); // flash 5× in 1 s
        }
        else
        {
            printf("Incorrect.\n");
            led_flashRed(5, 100);
        }
    }

    led_off();
    close(fd);
}
