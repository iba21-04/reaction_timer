#pragma once

void led_init(void);
void led_setGreen(int on);
void led_setRed(int on);
void led_flashGreen(int times, int delayMs);
void led_flashRed(int times, int delayMs);
void led_off(void);
void led_sleepMs(long long ms);
