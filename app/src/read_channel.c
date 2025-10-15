#include "read_channel.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int read_channel(int fd, int channel, uint32_t speed_hz)
{
    // Check channel validity
    uint8_t tx[3] = {
        (uint8_t)(0x06 | ((channel & 0x04) >> 2)),
        (uint8_t)((channel & 0x03) << 6),
        0x00};

    uint8_t rx[3] = {0}; // buffer for received data

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 3,
        .speed_hz = speed_hz,
        .bits_per_word = 8,
        .cs_change = 0};

    // Send SPI message
    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 1)
        return -1;

    // Convert the two received bytes into 12-bit ADC value
    return ((rx[1] & 0x0F) << 8) | rx[2];
}