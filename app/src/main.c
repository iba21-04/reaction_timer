// // Main program to build the application
// // Has main(); does initialization and cleanup and perhaps some basic logic.
// #include "reaction_timer.h"
// #include "led.h"
// #include "read_channel.h"
// #include <stdio.h>
// #include "led.h"
// #include "joystick.h"

// #include <fcntl.h>
// #include <sys/ioctl.h>
// #include <linux/spi/spidev.h>
// #include <unistd.h>
// #include <stdint.h>
// #include <stdlib.h>

// int main()
// {
//     printf("Hello embedded world, from ira!\n");
//     reaction_timer_run();

//     const char *dev = "/dev/spidev0.0"; // SPI device
//     uint8_t mode = 0;                   // SPI mode 0
//     uint8_t bits = 8;                   // 8 bits per word
//     uint32_t speed = 250000;            // SPI clock speed

//     int fd = open(dev, O_RDWR); // open SPI device
//     if (fd < 0)
//     {
//         perror("open");
//         return 1;
//     }

//     // Configure SPI
//     if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1)
//     {
//         perror("mode");
//         return 1;
//     }
//     if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1)
//     {
//         perror("bpw");
//         return 1;
//     }
//     if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
//     {
//         perror("speed");
//         return 1;
//     }

//     // Read ADC channels 0 and 1
//     int ch0 = read_channel(fd, 0, speed);
//     int ch1 = read_channel(fd, 1, speed);

//     // Print results
//     printf("CH0=%d CH1=%d\n", ch0, ch1);

//     close(fd);
//     // int ch0 = read_channel(fd, 0, speed);
//     // int ch1 = read_channel(fd, 1, speed);

//     JoystickDirection dir = joystick_get_direction(ch0, ch1);

//     switch (dir)
//     {
//     case JOY_UP:
//         printf("UP\n");
//         break;
//     case JOY_DOWN:
//         printf("DOWN\n");
//         break;
//     case JOY_LEFT:
//         printf("LEFT\n");
//         break;
//     case JOY_RIGHT:
//         printf("RIGHT\n");
//         break;
//     default:
//         printf("CENTER\n");
//         break;
//     }

//     return 0;
// }

/// till here

#include <stdio.h>
#include "reaction_timer.h"
#include "led.h"

int main()
{
    printf("Hello embedded world, from Ira!\n");
    led_init();
    reaction_timer_run();
    led_off(); // turn off LEDs on exit
    return 0;
}

// void foo() {
//     int data[3];ls
//     for (int i = 0; i <= 3; i++) {
//         data[i] = 10;
//         printf("Value: %d\n", data[i]);
//     }
// }

// int main()
// {
//     printf("Hello world!\n");

//     // Initialize all modules; HAL modules first
//     button_init();
//     badmath_init();

//     // Main program logic:
//     for (int i = 0; i < 10; i++) {
//         printf("  -> Reading button time %d = %d\n", i, button_is_button_pressed());
//     }

//     for (int i = 0; i <= 35; i++) {
//         int ans = badmath_factorial(i);
//         printf("%4d! = %6d\n", i, ans);
//     }

//     // Cleanup all modules (HAL modules last)
//     badmath_cleanup();
//     button_cleanup();

//     printf("!!! DONE !!!\n");

//     // Some bad code to try out and see what shows up.
//     #if 0
//         // Test your linting setup
//         //   - You should see a warning underline in VS Code
//         //   - You should see compile-time errors when building (-Wall -Werror)
//         // (Linting using clang-tidy; see )
//         int x = 0;
//         if (x = 10) {
//         }
//     #endif
//     #if 1
//         // Demonstrate -fsanitize=address (enabled in the root CMakeFiles.txt)
//         // Compile and run this code. Should see warning at compile time; error at runtime.
//         foo();

//     #endif
// }