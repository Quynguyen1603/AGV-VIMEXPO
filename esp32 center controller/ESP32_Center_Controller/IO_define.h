#include "esp32-hal-gpio.h"
#define Xilanh 4
#define Conveyor_Stop 12
#define IR_Sensor_PD   36     /// (PD = package detect)
#define Metal_Sensor_PD 35
#define Metal_Sensor_Safe 39

void IO_define ()
{
  pinMode (Xilanh,OUTPUT);
  pinMode (Conveyor_Stop,OUTPUT);
  pinMode(IR_Sensor_PD, INPUT)  ;
  pinMode(Metal_Sensor_PD, INPUT);
  pinMode(Metal_Sensor_Safe, INPUT);
}