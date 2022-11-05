int Receive_Step =0;
int Send_Step = 0;
bool Package_Check_en =0;
int Hook_have_package = 3;
int Sen_Rec_mode = 0;
bool Hold_bit1 = 0;
bool Hold_bit2 = 0;
#include "ESP_NOW_define.h"
#include "IO_define.h"
#include "Timer.h"
//#include "Receive_Send_Package.h"
#include "Toggle_Signal.h"
bool Cylinder_detect = 0;



void setup() 
{
  Serial.begin (115200);
  ESP_NOW_define() ;  /// Khoi tao ESP NOW
  IO_define();
  // attachInterrupt (Metal_Sensor_PD,Package_Check,RISING);
  // attachInterrupt (Metal_Sensor_Safe,Safe_cylinder,RISING);
}
void Package_Check()
{
  if (Package_Check_en == 1)
  {
    if (digitalRead (IR_Sensor_PD)== LOW)
    {
      Serial.println ("Hook have package");
      Hook_have_package =1;
    }
    else
    {
      Serial.println ("Hook dont have package");
      Hook_have_package =0;
    }
  }
  else
  {
    Hook_have_package =3;
  }
}
void Safe_cylinder()
{
  Cylinder_detect = 1;
}
void loop() 
{
// if (Timer8(true,1000) ==1)
//   {
//     Send_to_AGV(1,2,"S1>1", "S3>2") ;
//     Timer8(false,0); 
//   }

/////////////////TEST//////////////
  if(Serial.available())
  {
    char c = Serial.read ();
    if (c == '1')
    {
      Serial.println ("Luu du lieu");
      Send_to_AGV(1,2,0, "S3>1","S2>1");
    }
    else if (c == '2')
    {
      Serial.println ("Tiep tuc chay");
      Send_to_AGV(1,0,1, "    ","    ");
    }
    else if (c == '3')
    {
      Serial.println ("Dung lai");
      Send_to_AGV (2,0,0, "    ", "    ");
    }
    else if (c == '4')
    {
      Serial.println ("Luu du lieu");
      Send_to_AGV(1,1,0, "S2>1","    ");
    }
  }
//////////////////////////////////////////
  ///////Safe when turn on cylinder//////////
  if ( Cylinder_detect == 1)
  {
    if (Timer1 (true, 4000)== 1)
    {
      Cylinder_detect = 0;
      Timer1 (false,0);   
    }
  }
//////////////////////////////////////////////
// if  (DATAMode == 2) ///Neu nhu AGV dang o che do Auto
// {
//   if (ToggleSignal_int(DATAPacStatus) == 1)
//   {
//     if (DATAPacStatus == 1)
//     {
//         Sen_Rec_mode = 1;
//     }
//     else if (DATAPacStatus == 0)
//     {
//         Sen_Rec_mode =2;
//     }
//   }
//   if (Sen_Rec_mode ==1)
//   {
//     Send_Package(1);
//     Receive_Package(0);
//   }
//   else if (Sen_Rec_mode ==2)
//   {
//     Receive_Package(1);
//     Send_Package(0);
//   }
// }
}
