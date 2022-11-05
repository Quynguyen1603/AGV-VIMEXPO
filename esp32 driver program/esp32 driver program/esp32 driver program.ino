
int angle_int = 200;
unsigned long time_receive = 0;
int Mode_select = 0;  //1:Manual, 2: Auto
String RAW_String ; ///Serial receive string


int Auto_motor_left_speed;
int Auto_motor_right_speed;
String Auto_mode = "S" ;

#include "Timer.h"
#include "IO_define.h"
#include "BLE_define.h"
#include "MCP4922_define.h"
#include "Manual.h"
#include "Mode_change.h"
#include "Auto_motor_control.h"
#include "Serial_data.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  IO_mode();
  BLE_setup();
  SPI.begin();
  DAC.Set (0,0);
}

void loop() 
{
  Serial_Data_Receive ();
  Mode_change (Mode_select);  /// Stop AGV when chage mode

  //DAC.Set(1950,1900);
  if (Mode_select==1 && deviceConnected == true)   // Manual mode
  {
    if (millis() - time_receive > 300)  // Time out of BLE Manual command
    {
      angle_int = 200;
    }

    if (angle_int != 200) // Manual motor control
    // Manual_control(angle_int);
    {
      // Serial.println("Run");
      Manual_control(1, angle_int);
    }
    else
    {
      Manual_control (0,0);
      // Serial.println("Stop");    
    }
  }
  else if (Mode_select==2)
  {
    Serial.println ("Auto Mode");
    
    Auto_motor_control (Auto_mode);   
  }
}
