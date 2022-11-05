#include <Wire.h>
#include <ModbusRtu.h>
#include "Variable_define.h"
#include "IO_define.h"
#include "Sensor.h"

#include "Timer.h"
#include "Toggle_signal.h"
#include "I2C_define.h"
#include "MODBUS.h"
#include "Update_data.h"
#include "Motor_controller.h"



void setup() {
  // put your setup code here, to run once:
  IO_config();
  I2C_define();
  Serial.begin (115200);
  Serial2.begin (38400);
  Serial1.begin(115200,SERIAL_8N1);
  Serial3.begin(115200);
  slave.start();
  delay (500);
  Serial3.println (",AGV,AM,S,0,0#");  
  delay (100);
  Serial3.println(",AGV1,M#");
  
}

void loop() 
{
  Update_data();
  HMI_Data();
  state = slave.poll( MODBUS_HMI, 16);   ///Cap nhat du lieu qua HMI
  // put your main code here, to run repeatedly:

//////////////////////AUTO/MANUAL/////////////////////
  if (ToggleSignal_int(Mode))
  {
    if (Mode ==1) 
    {
      Serial3.println(",AGV1,M#")    ;     
    }  
    if (Mode ==2) 
    {
      Serial3.println(",AGV1,A#")    ;     
    }         
  }

  /////////////////////////////////////////////
  if (Mode ==1)
  {
    AdminCommand = "0";    
  }
  else if ( Mode ==2)
  {
//    if (AdminCommand == "1" && LineDetect ==1)
//    if (LineDetect ==1)
    if (AdminCommand == "1")
      {
//          if (AdminNext == "1")
//        {
//            Serial.println ("***************************************");
//            Cmt =1;
//          }
//        else if (AdminNext == "0")
//        {
//        Serial.println ("@@@@@@@@@@@@");
//        Cmt = 0;
//      }
      Auto_Controller (1,RFIDCommand,RFIDAction,AdminNext,&AGVSpeed,&RFIDRead,&RFIDStatus,&ErrorCode);
      Serial.println ((String)RFIDCommand +"/"+(String)RFIDAction +"/"+(String)AdminNext +"/"+(String)AGVSpeed +"/"+(String)RFIDRead +"/"+(String)RFIDStatus +"/"+(String)ErrorCode);
    }
    else 
    {
      Auto_Controller (0,RFIDCommand,RFIDAction,AdminNext,&AGVSpeed,&RFIDRead,&RFIDStatus,&ErrorCode);
    }
  }
  if (digitalRead(package_detect) == 0)
  {
    AGVPacStatus = 1;
  }
  else {
  {
    AGVPacStatus = 0;
  }
  }
/////////////////////////////////////////////////////////

}
