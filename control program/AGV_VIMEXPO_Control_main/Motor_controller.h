void Motor_Controller ( int Speed_Motor_Left, int Speed_Motor_Right)
{
  Speed_Motor_Left = map(Speed_Motor_Left,0,3000,0,2000) ; 
  Speed_Motor_Right = map(Speed_Motor_Right,0,3000,0,2000) ; 
  Serial3.println (",AGV,AM,R,"+ (String)Speed_Motor_Left+","+(String)Speed_Motor_Right+"#");
  Serial.println (",AGV,AM,R,"+ (String)Speed_Motor_Left+","+(String)Speed_Motor_Right+"#");   
}
void Auto_Controller (bool en, String RFID_CM, String RFID_AC, String CM, int* Speed, String* RFID_Out, String* RFID_Stt,String* Error_Code)
{
  int Maxspeed = 2000;          //Tốc độ tối đa
  static int Current_Maxspeed =0; 
  static int Magnetic_mode = 0;
  static int Lidar_mode = 1;
  int Speed_M1;
  int Speed_M2;
  static int Status =0;
  int Const = 8;       // Hệ số đá
  bool Low_Speed = 0;
  int MagneticValue = Magnetic_Sensor (Magnetic_mode);
  static bool ReadTag_Begin = 0;
  int ABSMagneticValue;  
  ABSMagneticValue = abs(MagneticValue);
  static String RFID_Mode = "0";
  static bool Dung =0;
  static String AB;
  int Safe_Sensor_Value = Safe_Sensor(Lidar_mode);
  int Deccel = 30;
  int Accel;
  int Add_value =0;
  int Add_Speed =0;
  int Minus_Speed =0;
  //Serial.println ("Gia tri cam bien:" + (String)MagneticValue);
  if (en ==1)   ///////Run
  {
    ///////////////Doc tag////////////
    if (ReadTag_Begin ==0)
    {
      if (TimerReadTag(true, 150)==1)
      {
          Read_Tag (&AB);   
          TimerReadTag(false, 1) ;
      }
    }      
    ///////////ErrorCode////////////

////////////////////////////////////////
  if (Status !=1) ///////////Khi khong co tag nao dang duoc thuc thi
  {
    if (AB == "T1" or AB == "T2" or AB == "T3" or AB == "T4" or AB == "T5")
    {
      RFID_Mode = "6"; //Rẽ trái giảm tốc
      MilisTimerLR (false,0,Current_Maxspeed);
    }
    else if ( AB == "P1" or AB == "P2" or AB == "P3" or AB == "P4" or AB == "P5")
    {
      RFID_Mode = "7";  //Rẽ phải giảm tốc
      MilisTimerLR (false,0,Current_Maxspeed);
    }
     else if ( AB == RFID_CM)
    {
      RFID_Mode = RFID_AC;
      Status =1;
      MilisTimerLR (false,0,Current_Maxspeed);
    }
  }
////////////////////Xu li cac chuc nang///////////////////////////////
if ( RFID_Mode == "3")       // Chuc nang re trai
  {
    Magnetic_mode = 1;  // Chức năng rẽ trái của cảm biến
    Low_Speed = 1;
    Lidar_mode =3;
    if (MilisTimerLR(true,7000,Current_Maxspeed) == 1)
    {
      RFID_Mode = "0"; 
      MilisTimerLR (false,0,Current_Maxspeed);    
    }
  }  
else if ( RFID_Mode == "4")     // Chuc nang re phai
  {
    Magnetic_mode = 2;  // Chức năng rẽ phải của cảm biến
    Low_Speed = 1;
    Lidar_mode =4;
    if (MilisTimerLR (true,7000,Current_Maxspeed) == 1)
    {
      RFID_Mode = "0"; 
      MilisTimerLR (false,0,Current_Maxspeed);  
    }
  }
else if (RFID_Mode == "1" or RFID_Mode == "2")   // Chuc nang Stop
  {
      Serial.println ("Dung lai:");
      ReadTag_Begin =1;    ///Dung doc tag
      Dung =1;
    if ( CM == "1")  // Tiếp tục chay
    {
      RFID_Mode = "0";
      Dung =0;
      Serial.println ("Thoat dung:");
    } 
  }
else if (RFID_Mode == "6")  //Rẽ trái giảm tốc
  {
    Low_Speed = 1;
    Lidar_mode =3;
    if (MilisTimerLR (true,7000,Current_Maxspeed) == 1)
    {
      RFID_Mode = "0"; 
      MilisTimerLR (false,0,Current_Maxspeed);  
    }
  }
  else if (RFID_Mode == "7") //Rẽ phải giảm tốc
  {
    Low_Speed = 1;
    Lidar_mode =4;
    if (MilisTimerLR (true,7000,Current_Maxspeed) == 1)
    {
     RFID_Mode = "0";   
     MilisTimerLR (false,0,Current_Maxspeed);
    }
  }
  if (RFID_Mode == "0")    //Chay thang
  {
    ReadTag_Begin =0;
    Lidar_mode =1;
    Magnetic_mode = 0;
    Low_Speed = 0;
    Status = 0;  
    *Error_Code = "0";
    MilisTimerLR (false,0,Current_Maxspeed);
  }

    /////////////////Xu li di chuyen cham toc do///////////////
    if (Safe_Sensor_Value !=0 && Low_Speed != 1 &&Safe_Sensor_Value !=3)
    {
      Maxspeed = Maxspeed - Safe_Sensor_Value*600;
      Deccel =10;
    }
    if (Low_Speed ==1)
    {
      Maxspeed = Maxspeed -1000;
      Maxspeed = Maxspeed - Safe_Sensor_Value*300;
      Deccel =30;
    }    
    if ( Dung ==1 or Safe_Sensor_Value ==3 or RFID_CM.length() <2)
    {
      Maxspeed =0;
      Deccel =10;
      
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
/////////////////////Dieu khien bam line tu///////////////
    if (digitalRead(over_right ) == 0)
    {
        Motor_Controller (Current_Maxspeed+100,Current_Maxspeed-1000);
        Serial.println ("CTHT ben phai");
    }
    else if (digitalRead(over_left) == 0)
    {
        Motor_Controller (Current_Maxspeed-1000,Current_Maxspeed+100);
        Serial.println ("CTHT ben trai");
    }
    else
      {
        if (MagneticValue == 0)
        {
            // Motor_Right_Controller (1,  Current_Maxspeed,Deccel,Accel,1,&Speed_M1);
            // Motor_Left_Controller (1, Current_Maxspeed,Deccel,Accel,1,&Speed_M2);
            Motor_Controller (Current_Maxspeed,Current_Maxspeed);
        }
        else
        {
              Add_value = Const*(ABSMagneticValue+1);

            Add_Speed =  Current_Maxspeed + Add_value*ABSMagneticValue;
            Minus_Speed =  Current_Maxspeed - Add_value*ABSMagneticValue;

            Serial.println ("Gia tri cong them :" + (String)Add_Speed);
            Serial.println ("Gia tri tru di :" + (String)Minus_Speed);
            if (MagneticValue < 0)
            {
                if (Minus_Speed > 0 )
                {
                    // Motor_Right_Controller (1,  Minus_Speed,Deccel,Accel,1,&Speed_M1);
                    // Motor_Left_Controller (1, Add_Speed,Deccel,Accel,1,&Speed_M2);
                    Motor_Controller (Add_Speed,Minus_Speed);                    
                }
                else 
                {
                    // Motor_Left_Controller (1, Add_Speed,Deccel,Accel,1,&Speed_M2);
                    // Motor_Right_Controller (1,  0,Deccel,Accel,1,&Speed_M1);
                    Motor_Controller (Add_Speed,0);                   
                }
            }
            else
            {
                if (Minus_Speed > 0 )
                {
                    // Motor_Right_Controller (1,  Add_Speed,Deccel,Accel,1,&Speed_M1);
                    // Motor_Left_Controller (1,  Minus_Speed,Deccel,Accel,1,&Speed_M2);
                    Motor_Controller (Minus_Speed,Add_Speed);
                }
                else 
                {
                    // Motor_Right_Controller (1,Add_Speed,Deccel,Accel,1,&Speed_M1);
                    // Motor_Left_Controller (1,  0,Deccel,Accel,1,&Speed_M2);
                    Motor_Controller (0,Add_Speed);
                }
            }
          }    
        }



  /////////////////////////BUZZER///////////////////
  
  /////////////////////////Thu thap du lieu////////////////////////
  *Speed = Current_Maxspeed;
  /////////////////Errrorr///////////////////////
  if (Safe_Sensor_Value == 3)
  {
    *Error_Code == "1";
    digitalWrite (buzzer_sound1, LOW);
  }  
  else 
  {
    digitalWrite(buzzer_sound1,HIGH);
  }

    /////////////////////////BUZZER///////////////
  if (RFID_Mode =="3" or RFID_Mode =="4" or RFID_Mode =="6" or RFID_Mode =="7" )  
  {
    digitalWrite (buzzer_sound2, LOW);
  }  
  else 
  {
    digitalWrite(buzzer_sound2,HIGH);
  } 
  //////////////////////////////////////////   
  *RFID_Stt = Status;
  if ( AB != "0")
  {
  *RFID_Out = AB;
  }

  }
  else ///Stop
  {
    Serial3.println (",AGV,AM,S,0,0#");
    *Speed = 0;    
  }
}
