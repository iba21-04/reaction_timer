#ifndef READ_CHANNEL_H_
#define READ_CHANNEL_H_

#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int read_channel(int fd, int channel, uint32_t speed_hz);
#endif
