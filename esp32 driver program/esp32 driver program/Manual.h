#include "esp32-hal-gpio.h"
void Manual_control(bool En, int Angle)
{
  int Maxspeed = 1200;
  static int Current_Maxspeed = 0;
  int Deccel =10;
  int Accel = 20;
  int Speed_M1;
  int Speed_M2;
  int  Add_Speed;
  int Minus_Speed;
  int Const = 10;
  int ABS_Angle = abs(Angle);
  // DAC.Set(1950,500);   //Motor right, motor left
  // Serial.println ("Manual");
  digitalWrite(motor_brake, HIGH);
  if ( En == 0)
  {
    Maxspeed =0;
  }
  else 
  {
    Maxspeed =1200;
  }
   ////////////Tăng tốc độ tối đa/////////
  if ( Current_Maxspeed < Maxspeed)
  {
    if (MilisTimerMM1( true,Accel) == true)
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

////////////Start/ Stop/////////
if (Current_Maxspeed != 0)
{
  digitalWrite (motor_left_start,HIGH);
  digitalWrite (motor_right_start,HIGH);
}
else 
{
  digitalWrite (motor_left_start,LOW);
  digitalWrite (motor_right_start,LOW);
}

/////////////Angle control///////////////
if (Angle ==0)
{
  digitalWrite (motor_left_dir, HIGH);
  digitalWrite (motor_right_dir, LOW);
  DAC.Set (Current_Maxspeed, Current_Maxspeed);
}
else if (Angle == 180)
{
  digitalWrite (motor_left_dir, LOW);
  digitalWrite (motor_right_dir, HIGH);
  DAC.Set (Current_Maxspeed, Current_Maxspeed);
}

else if (ABS_Angle >=10 && ABS_Angle <= 90)
{
  
  Add_Speed = Current_Maxspeed + Const*ABS_Angle;
  Minus_Speed = Current_Maxspeed - Const*ABS_Angle;
  Serial.println ("Add speed"+ (String)Add_Speed);
  Serial.println ("Minus_Speed"+ (String)Minus_Speed);
  if (Minus_Speed <0)
  {
    Minus_Speed =0;
  }
  if ( Angle >= 10 && Angle <=90)  // Turn Left Straight
  {
    digitalWrite (motor_left_dir, HIGH);
    digitalWrite (motor_right_dir, LOW);
    DAC.Set (Add_Speed, Minus_Speed);  
  }
  else if ( Angle >= -90 && Angle <=-10) // Turn Right Straight
  {
    digitalWrite (motor_left_dir, HIGH);
    digitalWrite (motor_right_dir, LOW);
    DAC.Set (Minus_Speed, Add_Speed);  
  }

}


else if (ABS_Angle>=100 && ABS_Angle <=170)
{
  Add_Speed = Current_Maxspeed + Const*(180-ABS_Angle);
  Minus_Speed = Current_Maxspeed - Const*(180-ABS_Angle);
  Serial.println ("Add speed"+ (String)Add_Speed);
  Serial.println ("Minus_Speed"+ (String)Minus_Speed);
  
  if (Minus_Speed <0)
  {
    Minus_Speed =0;
  }
  if ( Angle >= 100 && Angle <=170) // Turn Right Straight
  {
    digitalWrite (motor_left_dir, LOW);
    digitalWrite (motor_right_dir, HIGH);
    DAC.Set (Minus_Speed, Add_Speed);  
  }  

  else if ( Angle >= -170 && Angle <=-100) // Turn Right Straight
  {
    digitalWrite (motor_left_dir, LOW);
    digitalWrite (motor_right_dir, HIGH);
    DAC.Set (Add_Speed, Minus_Speed);  
  }
}

}