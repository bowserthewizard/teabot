#include <avr/io.h>
#ifndef SERVO_H
#define SERVO_H
void servo_init(void);
void servo_set_angle(uint8_t angle);
#endif
