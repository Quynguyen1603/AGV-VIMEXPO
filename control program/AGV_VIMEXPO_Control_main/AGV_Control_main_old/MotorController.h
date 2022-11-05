#include "Timer_millis.h"
void Read_Tag (String* AB)        // Đọc tag
{
  char c = ' ';
  String Tag = "";
  Serial2.println ("SR000002#");
  int i = 1;
  while (Serial2.available() ) 
  {
    c = Serial2.read();
  if (c != ' ')
  {
    Tag +=c;
  }
  }
  if (Tag.length() >= 3)
  {
    *AB = Tag[3];
    *AB += Tag[2];
  }
  else 
  {
    *AB = "0";
  }
//  Serial.print("Tag la:");
//  Serial.print (Tag[2]);
//  Serial.println (Tag[3]);
}

int Safe_Sensor()
{
  int i;
  bool val1=0,val2=0,val3=0;
  val1=digitalRead(out3_safe_sensor);
  val2=digitalRead(out2_safe_sensor);
  val3=digitalRead(out1_safe_sensor);
  if((val1 == 0) && (val2 == 0) && (val3 == 0))
  {
    i=0;//Không có vật cản
  }
  if((val1 == 1) && (val2 == 0) && (val3 == 0))
  {
    i=1;//Phát hiện vật cản
  }
  if((val1 == 1) && (val2 == 1) && (val3 == 0))
  {
    i=2;//Sắp đụng vật cản
  }
    if((val1 == 1) && (val2 == 1) && (val3 == 1))
  {
    i=3;//Nguy hiểm !!!
  }
  return i;
}

int Magnetic_Sensor (int mode) /// mode 0 == straight, mode 1 = right brach, mode 2 = left brand, mode 3 = no select
{
 int magnetic_sensor_sample[30] = {755,710,695,680,660,645,625,610,590,575,555,540,520,505,490,470,455,435,420,400,385,370,350,335,315,300,280,265};
 int value;
 int Position =0;
 int a;
 ////////////Chọn chế độ cho Cảm biến line///////
 if (mode == 0)
 {
    digitalWrite (guide_sensor_sil1, LOW);
    digitalWrite (guide_sensor_sil2, LOW);
 }
 else if (mode == 1)
  {
    digitalWrite (guide_sensor_sil1, LOW);
    digitalWrite (guide_sensor_sil2, HIGH);
 }
  else if (mode == 2)
  {
    digitalWrite (guide_sensor_sil1, HIGH);
    digitalWrite (guide_sensor_sil2, LOW);
 }
  else 
  {
    digitalWrite (guide_sensor_sil1, HIGH);
    digitalWrite (guide_sensor_sil2, HIGH);
 }

 ////////////////////////Kiễm tra xem có line hay không///////
 
 if (digitalRead (out_guide_sensor) == 1)
 {
   a = 96;
 }
 ///////////Giá trị cảm biến line từ đưa về từ -15 đến 15
 else 
 {
 value = analogRead (analog_magnetic);
 //Serial.println (value);
 for (int i = 0; i < 30 ;i ++)
 {
   if (magnetic_sensor_sample [i] >= value && value >= magnetic_sensor_sample [i+1])
   {
     Position = i +1;
   }
 }
 a = Position -14; 
 }
 if (a != 69)
 {
 return a;
 }
}

void Blink ( int Pin) // Hàm nhấp nháy led
{
  if ( MilisBlink ( true,500) == 1)
  {
    if (digitalRead( Pin) == LOW)
      digitalWrite(Pin,HIGH);
    else 
      digitalWrite (Pin, LOW);
   MilisBlink (false,0);  
  }
}
void DACMotor1 (int DACValue)
{
  Serial3.println(",1,"+(String)DACValue+"#");
}
void DACMotor2 (int DACValue)
{
  Serial3.println(",2,"+(String)DACValue+"#");
}
void Motor_Right_Controller (bool Start, int Speed,int Deccel,int Accel, bool Dir_B , int* Speed_M1)
{
  static int Current_Speed=0;  /// Tốc độ đệm tăng/ giảm tốc
  static bool Dir;
  Dir = Dir_B;
  int AddValue = 25;
  int MinusValue = 25;
  static bool Restart = 0;
  ////////////Tăng tốc///////
  *Speed_M1 = Speed;

  //////////Gửi dữ liệu ra các IO
  Serial.println ("Dong co 1:" +(String)Dir+ "," + (String)Speed);
  digitalWrite(motor_right_start, LOW);
  digitalWrite(motor_right_dir,Dir);
  if (Speed <= 500)
  {
    digitalWrite(motor_right_start, HIGH);
  }
  DACMotor1(Speed);
  
}
void Motor_Left_Controller (bool Start, int Speed, int Deccel, int Accel,bool Dir_B,int* Speed_M2)
{
  static int Current_Speed=0;
  static bool Dir;
  int AddValue = 25;
  int MinusValue = 25;
  static bool Restart =0;

  Dir = !Dir_B;
  ////Khi dừng không thay đổi hướng
  ////////////Tăng tốc///////
  
  *Speed_M2 =Speed;
  
  Serial.println ("Dong co 2:" +(String)Dir+ "," + (String)Speed);
  digitalWrite(motor_left_start, LOW);
  digitalWrite(motor_left_dir, Dir);
  if (Speed <= 500)
  {
    digitalWrite(motor_left_start,HIGH);
  }
  DACMotor2(Speed);
  
}
void Manual_Controller (bool Begin, int Funtion, int* Speed)  ///Điều khiển động cơ thủ công 
{

}

/////////Hàm điều khiển động cơ tự động
void Auto_Controller ( bool Begin, String AB_in, String Action,int Command, int* Speed, String* AB_r, int* RFIDStatus,String* ErrorCode) 
{
  int Maxspeed;          //Tốc độ tối đa
  static int Current_Maxspeed =0; 
  int Const = 8;       // Hệ số đá
  int ABSMagneticValue = 0;
  int Minus;
  static bool Restart = 0;
  bool Low_Speed = 0;
  static int Mode;
  int SpeedMinus;
  int Speed_M1;
  int Speed_M2;
  int Deccel = 30;
  int Accel;
  static  String AB;
  bool Stop = 0;
  int Add_value =0;
  int Add_Speed =0;
  static int Status =0;
  int Minus_Speed =0;
  int count= 0;
  static bool ReadTag_Begin = 0;
  static int Magnetic_mode = 0;
  int Safe_Sensor_Value = Safe_Sensor();
  static String RFID_Mode = "0";
  static bool Dung =0;
  //////////////////
  int MagneticValue = Magnetic_Sensor (Magnetic_mode);
  ///////////////////
  ABSMagneticValue = abs (MagneticValue);
  //Serial.println ("Cam bien line tu:" + (String)MagneticValue); 
//////////////Cảm biến RFID////////////////
  if (ReadTag_Begin == 0)
  { 
    if (MilisTimerRead( true, 150) == true)
    {
      Read_Tag (&AB);
      MilisTimerRead ( false,1);
    }
  }
  ////////////ErrorCode//////////////
  if (Safe_Sensor_Value == 3)
  {
    *ErrorCode = "1";
  }
  /////////////Xử lí các chế độ khi có tag//////////////
if (Status !=1)  //////////Khi không có tag nào đang được thực thi///////
{
    if (AB == "T1" or AB == "T2" or AB == "T3" or AB == "T4" or AB == "T5")
    {
      RFID_Mode = "6"; //Rẽ trái giảm tốc
      //Status =1;
      MilisTimerLR (false,0,Current_Maxspeed);
    }
    else if ( AB == "P1" or AB == "P2" or AB == "P3" or AB == "P4" or AB == "P5")
    {
      RFID_Mode = "7";  //Rẽ phải giảm tốc
      //Status =1;
      MilisTimerLR (false,0,Current_Maxspeed);
    }
     else if ( AB == AB_in)
    {
      RFID_Mode = Action ;
      Status =1;
      MilisTimerLR (false,0,Current_Maxspeed);
    }
}
////////////////////////Xử lí các chức năng/////////////////
if ( RFID_Mode == "3")       // Chuc nang re trai
  {
    Magnetic_mode = 1;  // Chức năng rẽ trái của cảm biến
    //ReadTag_Begin =1;  // Tam ngưng đọc tag
    digitalWrite (led_right, LOW);
    Blink(led_left);
    Low_Speed = 1;
    if (MilisTimerLR(true,8000,Current_Maxspeed) == 1)
    {
      RFID_Mode = "0"; 
      MilisTimerLR (false,0,Current_Maxspeed);    
    }
  }
else if ( RFID_Mode == "4")     // Chuc nang re phai
  {
    Magnetic_mode = 2;  // Chức năng rẽ phải của cảm biến
    //ReadTag_Begin = 1;  // Tam ngưng đọc tag
    digitalWrite (led_left, LOW);
    Low_Speed = 1;
    Blink(led_right);
    if (MilisTimerLR (true,8000,Current_Maxspeed) == 1)
    {
      RFID_Mode = "0"; 
      MilisTimerLR (false,0,Current_Maxspeed);  
    }
  }
  else if (RFID_Mode == "1" or RFID_Mode == "2")   // Chuc nang Stop
  {
    
      ReadTag_Begin = 1;  // Tạm ngưng đọc tag
      Serial.println ("Dung lai:");
      ReadTag_Begin =1;
      Dung =1;
    if ( Command == 1)  // Tiếp tục chay
    {
      RFID_Mode = "0";
      Dung =0;
    } 
  }
  else if (RFID_Mode == "6")  //Rẽ trái giảm tốc
  {
    digitalWrite (led_right, LOW);
    Blink(led_left);
    Low_Speed = 1;
    if (MilisTimerLR (true,8000,Current_Maxspeed) == 1)
    {
      RFID_Mode = "0"; 
      MilisTimerLR (false,0,Current_Maxspeed);  
    }
  }
  else if (RFID_Mode == "7") //Rẽ phải giảm tốc
  {
    digitalWrite (led_left, LOW);
    Blink(led_right);
    Low_Speed = 1;
    if (MilisTimerLR (true,8000,Current_Maxspeed) == 1)
    {
     RFID_Mode = "0";   
     MilisTimerLR (false,0,Current_Maxspeed);
    }
  }
  if (RFID_Mode == "0")    //Chay thang
  {
    ReadTag_Begin =0;
    Magnetic_mode = 0;
    Low_Speed = 0;
    Status = 0;  
    *ErrorCode = "0";
    digitalWrite (led_left, LOW);
    digitalWrite (led_right,LOW);
    MilisTimerLR (false,0,Current_Maxspeed);
  }
////////////////////////////
//Serial.println ("Begin la:" + (String)Begin + "RFID_in:" +(String)AB_in+ "Action:"+ (String)Action + "RFIDMode:" + (String)RFID_Mode);
if (Begin ==1)
{
  Maxspeed = 2900;
}
if (Safe_Sensor_Value !=0 && Low_Speed != 1 &&Safe_Sensor_Value !=3)
{
  Maxspeed = Maxspeed - Safe_Sensor_Value*1000;
  Deccel =10;
}
if (Low_Speed ==1)
{
  Maxspeed = Maxspeed -1600;
  Maxspeed = Maxspeed - Safe_Sensor_Value*300;
  Deccel =30;
}
///////////////////
if ( Dung ==1 or Safe_Sensor_Value ==3)
{
  Maxspeed =0;
  Deccel =10;
  
}
if (Begin ==0 )
{
  Maxspeed =0;
  Const =0;
}
if ( Maxspeed <0)
{
  Maxspeed =0;
}
  ////////////Tăng tốc độ tối đa/////////
  if ( Current_Maxspeed < Maxspeed)
  {
    if (MilisTimerMM1( true, 70) == true)
    {
      Current_Maxspeed += 50;
      MilisTimerMM1 (false,0);
    }
  }
  
  //////////////Giảm tốc độ tối đa/////////////
  else  if (Current_Maxspeed > Maxspeed)
  {
    if (MilisTimerMM2( true, Deccel) == true)
    {
        Current_Maxspeed -= 50;
        MilisTimerMM2 (false,0);
    }
  }
  //Serial.println ("Toc do toi da la:"+ (String)Current_Maxspeed);
  ///Điều khiển bám line từ
        if  (Begin != 0)      
        {
          if (digitalRead(over_right )== 0)
          {
              Motor_Right_Controller (1, Current_Maxspeed-500,Deccel,Accel,1,&Speed_M1);
              Motor_Left_Controller (1,Current_Maxspeed+100,Deccel,Accel,1,&Speed_M2);
          }
          else if (digitalRead(over_left) == 0)
          {
              Motor_Right_Controller (1,Current_Maxspeed+100,Deccel,Accel,1,&Speed_M1);
              Motor_Left_Controller (1, Current_Maxspeed-500,Deccel,Accel,1,&Speed_M2);
          }
        }
        if (1)
        {
            if (MagneticValue == 0)
            {
                Motor_Right_Controller (1,  Current_Maxspeed,Deccel,Accel,1,&Speed_M1);
                Motor_Left_Controller (1, Current_Maxspeed,Deccel,Accel,1,&Speed_M2);
            }
            else
            {
                 Add_value = Const*(ABSMagneticValue+1);

                Add_Speed =  Current_Maxspeed + Add_value*ABSMagneticValue;
                Minus_Speed =  Current_Maxspeed - Add_value*ABSMagneticValue;

                //Serial.println ("Gia tri cong them :" + (String)Minus_Speed);
                if (MagneticValue < 0)
                {
                    if (Minus_Speed > 0 )
                    {
                        Motor_Right_Controller (1,  Minus_Speed,Deccel,Accel,1,&Speed_M1);
                        Motor_Left_Controller (1, Add_Speed,Deccel,Accel,1,&Speed_M2);
                    }
                    else 
                    {
                        Motor_Left_Controller (1, Add_Speed,Deccel,Accel,1,&Speed_M2);
                        Motor_Right_Controller (1,  0,Deccel,Accel,1,&Speed_M1);
                    }
                }
                else
                {
                    if (Minus_Speed > 0 )
                    {
                        Motor_Right_Controller (1,  Add_Speed,Deccel,Accel,1,&Speed_M1);
                        Motor_Left_Controller (1,  Minus_Speed,Deccel,Accel,1,&Speed_M2);
                    }
                    else 
                    {
                        Motor_Right_Controller (1,Add_Speed,Deccel,Accel,1,&Speed_M1);
                        Motor_Left_Controller (1,  0,Deccel,Accel,1,&Speed_M2);
                    }
                }
            }    
        }

if (Begin ==1)
{
  *Speed = Current_Maxspeed;
}
else
{
  *Speed = 0;
}
*RFIDStatus = Status;
if ( AB != "0")
{
*AB_r = AB;
}

}
