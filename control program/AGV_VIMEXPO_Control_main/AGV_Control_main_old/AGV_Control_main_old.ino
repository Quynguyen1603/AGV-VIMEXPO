
#include <Wire.h>
#include <ModbusRtu.h>

#include "IO_define.h"
#include "Magnetic_Sensor.h"
//#include "Timer_millis.h"
#include "ToggleSignal.h"
//#include "MotorController.h"

#define ID   1
Modbus slave(ID, Serial1);


int8_t state = 0;
uint16_t MODBUS_HMI[16];
int Mode = 0;
int Funtion =0;
int Magnetic_value;
int AGVBattery = 10;
bool BeginAuto;
String Mess ;
bool LineDetect = 0;
int SpeedM1 =0;
int SpeedM2 =0;
int Speed = 0;
String RFIDCommand ="";
String RFIDAction = "" ;
int RFIDStatus = 0; 
int Cmt = 0;   //Nút Next
int RunBit = 0;
String RFIDRead;
String RFIDRead_sub = "00";
int AGVPacStatus;
int MessLen = 0;
char MessC[30];

String BLE_EN = "";
String Wifi_EN = "";
String Connected ="";
String AdminCommand ="0";

String ErrorCode = "0";

void setup() 
{
  IO_config();
  Serial.begin (115200);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.setClock(200000);
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event 
  Serial2.begin (38400);
  Serial1.begin(115200,SERIAL_8N1);
  Serial3.begin(115200);
  slave.start();
  delay (500);
  Serial3.println (",AGV,AM,S,0,0#");

}

void loop() 
{
  Cmt = 0;
  Update_data ();
  MessLen = Mess.length ();
  MessC[MessLen];
  Mess.toCharArray ( MessC, MessLen+1);
  HMI_Data ();
  state = slave.poll( MODBUS_HMI, 16);
  ////////////////////Lựa chọn AUTO/MANUAL/////////////
  LineDetect = !digitalRead (out_guide_sensor);
  if ( Mode == 1)
  {
  //   Serial.println ("Manual");
  ////Manual_Mode
    //Auto_Controller (0,RFIDCommand,RFIDAction,Cmt,&Speed,&RFIDRead,&RFIDStatus,&ErrorCode);
  }
  else 
  if (Mode == 2)
  {
    if ((BeginAuto == 1 or AdminCommand == "1") && LineDetect ==1)
    {
       //     Serial.println ("Auto");
      //Auto_Controller (1,RFIDCommand,RFIDAction,Cmt,&Speed,&RFIDRead,&RFIDStatus,&ErrorCode);
      //Serial.println ("Tag la:"+ (String)RFIDRead + "Status:"+ (String)RFIDStatus);
    }
    else 
    {
      //Auto_Controller (0,RFIDCommand,RFIDAction,Cmt,&Speed,&RFIDRead,&RFIDStatus,&ErrorCode);
    }
  }
      if (LineDetect ==0)
      {
        ErrorCode = "3";
      }     
    
}
void receiveEvent()     //Nhận dữ liệu thông qua I2C
{
  String Str ="";
  int Str_size =0;;
  char c;
  int dem;
  RFIDCommand = "";
  RFIDAction = "";
  while (Wire.available())
  {
    c = Wire.read();
    //Serial.println (c);
    Str_size ++;
    Str +=c    ; 
  }
  Serial.println ("Du lieu la:" + (String)Str);
  Serial.println ("Do dai du lieu la:" + (String)Str_size);
  
   
   if (Mode ==1) //Ở chế độ Manual sẽ nhận dữ liệu khác
  {
//    String str1, str2, str3;
//    int a = Str.length ();
//    int dem =1;
//    for (int i =0; Str[i]!= '#'; i++)
//    {
//      if ( Str[i]== ',')
//      {
//        dem ++;
//      }
//      else 
//      {
//        switch (dem)
//        {
//          case 1:
//          {
//            str1+=Str[i];
//            break;
//          }
//          case 2:
//          {
//            str2+=Str[i];
//            break;
//          }
//          case 3:
//          {
//            str3+=Str[i];
//            break;
//          }
//        }
//      }
//    }
//   Serial.println ("Str1:"+ (String) str1);
//   Serial.println ("Str2:"+ (String) str2);
//   Serial.println ("Str3:"+ (String) str3); 
  }
  if (Mode == 2)  ///Nhận dữ liệu ở chế độ Auto
  {
    String str1, str2, str3,str4,str5;
    int a = Str.length ();
    int dem =0;
    for (int i =0; Str[i]!= '#'; i++)
    {
      if ( Str[i]== ',')
      {
        dem ++;
      }
      else 
      {
        switch (dem)
        {
          case 1:
          {
            str1+=Str[i];
            break;
          }
          case 2:
          {
            str2+=Str[i];
            break;
          }
          case 3:
          {
            str3+=Str[i];
            break;
          }
          case 4:
          {
            str4+=Str[i];
            break;
          }
          case 5:
          {
            str5+=Str[i];
            break;
          }
      }
    }
  }
   Serial.println ("Str1:"+ (String) str1);
   Serial.println ("Str2:"+ (String) str2);
   Serial.println ("Str3:"+ (String) str3); 
   Serial.println ("Str4:"+ (String) str4); 
   Serial.println ("Str5:"+ (String) str5);
   Wifi_EN =  str1;
   Connected = str2;
   AdminCommand = str3;
   RFIDCommand = str4;
   RFIDAction = str5;
  }
  
}

void requestEvent() 
{
  Wire.write(MessC); // respond with message of 1 byte
}

void Update_data()  /// Hàm Cap nhat du lieu
{
    /// Nếu thay đổi Tag mới thay đổi Tag gửi
  
  Mess = ",";
  Mess += "AGV1";  ///ID
  Mess += ",";
//  Mess += (String)Mode;  ///Status
  Mess += (String)2;
  Mess += ",";
  ///Status
//  Mess += (String)RunBit;
  Mess += (String)3;
  Mess += ",";
  ///Error code
//  Mess += ErrorCode;
  Mess += (String)4;
  Mess += ",";
  /////Páctatus
//  Mess += (String)AGVPacStatus;
   Mess += (String)0;
  Mess += ",";
  ///Battery
//  Mess += (String)AGVBattery;
   Mess += (String)100;
  Mess += ",";
  ///Speed
  int Speed_Pint = map (Speed,0,2900,0,100);
//  Mess += (String)Speed_Pint ;
  Mess += (String)90 ;
  Mess += ",";
  
  ///RFID read code
  if (RFIDRead_sub != RFIDRead && RFIDRead.length() >=2)
  {
    RFIDRead_sub = RFIDRead;                                                        
  }
//  Mess += (String)RFIDRead_sub[0];
//  Mess += (String)RFIDRead_sub[1];
  Mess += (String)"AB";
  Mess += ",";
  ///RFID status
//  Mess += (String)RFIDStatus;
  Mess += (String)9;
  Mess += "#";
//  Serial.println (Mess);
}
void HMI_Data ()
{
  //////////Line detect//////////
  if (LineDetect == 1)
  {
    bitWrite (MODBUS_HMI[0],3,1);
  }
  else
  {
    bitWrite (MODBUS_HMI[0],3,0);
  }
  ////////////Auto/Manual////////////
  //Serial.println ("Auto/Manual:" + (String)bitRead (MODBUS_HMI[0],9));
  if (bitRead (MODBUS_HMI[0],9) == 0)
  {
    Mode = 1;  //Manual
  }
  else
  {
    Mode = 2;    //Auto
  }
  if ( RFIDRead.length() >= 2)  // Nếu đọc được tag thì show ra màn hình
  {
    char A = RFIDRead [0];
    char B = RFIDRead [1];
    MODBUS_HMI[10] = A;
    MODBUS_HMI[11] = B;
  }
  else 
  {
    MODBUS_HMI[10] = '0';
    MODBUS_HMI[11] = '0';
  }
  if ( RFIDCommand.length() >= 2)  // Nếu có RFID tag lệnh được gửi show ra màn hình
  {
    bitWrite (MODBUS_HMI[0],13,1);   // Nút ready sáng
    char A = RFIDCommand [0];
    char B = RFIDCommand [1];
    char C = RFIDAction [0];
    //Serial.println ("RFIDAction" + (String)RFIDAction [0]);
    MODBUS_HMI[12] = A;
    MODBUS_HMI[13] = B;
    MODBUS_HMI[14] = C;
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],13,0);  // Nút ready tắt
    MODBUS_HMI[12] = '0';
    MODBUS_HMI[13] = '0';
    MODBUS_HMI[14] = '0';
  }

  if (TogglePositive_bool(bitRead (MODBUS_HMI[0],14)) ==1 && BeginAuto == 0)
  {
    BeginAuto =1;  
  }
  else if (TogglePositive_bool(bitRead (MODBUS_HMI[0],14)) ==1 && BeginAuto == 1)
  {
    BeginAuto =0;
  }
  
  //////////////Stop/ Runiing////////////
  if (SpeedM2 == 0)
  {
    bitWrite (MODBUS_HMI[0],7,1);  ///Stop
    bitWrite (MODBUS_HMI[0],6,0);  ///Running
    RunBit = 0;
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],7,0);  ///Stop
    bitWrite (MODBUS_HMI[0],6,1);  ///Running
    RunBit = 1;
  }

  ///////////////////Next///////////////
  if (bitRead (MODBUS_HMI[0],12) == 1)
  {
    
    Cmt = 1 ;
  }
  else if (bitRead (MODBUS_HMI[0],12) == 0)
  {
    
    Cmt = 0 ;
  }
  ///////////////Wifi/BLE Connected////////////
  if ( Wifi_EN  == "1")
  {
     bitWrite (MODBUS_HMI[0],1,1);
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],1,0);
  }
  if ( Connected == "1")
  {
    bitWrite (MODBUS_HMI[0],2,1);
  }
  else 
  {
    bitWrite (MODBUS_HMI[0],2,0);
  }
  
}
