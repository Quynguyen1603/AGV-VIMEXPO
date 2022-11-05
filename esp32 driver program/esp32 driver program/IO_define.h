#include "esp32-hal-gpio.h"

#define motor_left_start 25
#define motor_left_dir 33
#define motor_right_start 32
#define motor_right_dir 13
#define motor_brake 12

int motor_left_speed, motor_right_speed;
void IO_mode()
{
  pinMode (motor_left_start,OUTPUT);
  pinMode(motor_left_dir, OUTPUT);
  pinMode(motor_right_dir, OUTPUT);
  pinMode(motor_right_start, OUTPUT);
  pinMode(motor_brake, OUTPUT); 

}
