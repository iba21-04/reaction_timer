#pragma once

void led_init(void);
void led_set_green(int on);
void led_set_red(int on);
void led_flash_green(int times, int delayMs);
void led_flash_red(int times, int delayMs);
void led_off(void);
void led_sleepMs(long long ms);
