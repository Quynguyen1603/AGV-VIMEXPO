#include <Wire.h>
#include <Arduino.h>
#include <cstring>


/////////////////Data Reveive AGV/////////////
String I2CRec_Str;
String AGVID ;
String AGVMode = "0";
String AGVStatus;
String AGVErrorCode ;
String AGVPacStatus;
String AGVBattery;
String AGVNextRFID;
String AGVSpeed;
String AGVRFIDRead;
String AGVStepStatus;
int CurrentStep = 1;
bool RunOneBit1 = 1;
int AdminCommand_Mode =0;
#include "ESP_NOW_define.h"
#include "I2C_define.h"
#include "Toggle_Signal.h"
#include "Timer.h"
#include "Data_processing.h"




  //Bien luu mode cua AdminCommand

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println ("Begin");
  ESP_NOW_define();
  Wire.begin();
  Wire.setClock(200000);
}

void loop() 
{
  // // put your main code here, to run repeatedly:
  // ///////////////Cap nhat du lieu tu AGV///////////
  if (Timer1(true,500) == 1 )
  {
    //Serial.println ("get");
    I2CReceive(&I2CRec_Str);
    if ( Is_True_Data (I2CRec_Str) ==1 ) /// Nếu k nhận được dữ liệu bỏ qua (them khiem tra cuoi du lieu)
    {
   
      I2C_DP (I2CRec_Str,&AGVID,&AGVMode,&AGVStatus,&AGVErrorCode,&AGVPacStatus,&AGVBattery,&AGVSpeed,&AGVRFIDRead,&AGVStepStatus);
      //Send_to_Center_Control();
      // Serial.println (AGVID);
      // Serial.println (AGVMode);
      // Serial.println (AGVStatus);
      // Serial.println (AGVErrorCode);
      // Serial.println (AGVPacStatus);
      // Serial.println (AGVBattery);
      // Serial.println (AGVSpeed);
      // Serial.println (AGVRFIDRead);
      // Serial.println (AGVStepStatus);

      Send_to_Center_Control();      
      
    }
    Timer1(false,0);
  }   
  ////////////////////////////////////////////////////


  if (ToggleSignal_int(AdminCommand)==1)    //// Co thay doi lenh gui xuong
  {
      Serial.println ("Co lenh duoc gui");
      if (AdminCommand ==2)     //Dung AGV xoa du lieu trong bo nho
      {
        I2CSend (",1,1,2,0,,#");
        Serial.println (",1,1,2,0,,#");
        // AdminCommand_Mode = 3;
      }  
      else if (AdminCommand == 1 or AdminCommand == 3)     //Cap nhat du lieu vao bo nho, bat dau chay
      {
        AdminCommand_Mode = 1;
      }             
  } 

  //////////////////////////////////////////////
  // if (AdminCommand_Mode == 3)  ////Kiem tra AGV da nhan duoc chua
  // {
  //   if (Timer2 (true, 400) ==1)
  //   {
  //     if  (AGVStatus == "1")   //Neu AGV da chay
  //     {
  //        AdminCommand_Mode =0;
  //        Timer2 (false,0);     
  //     }
  //     else if (AGVStatus == "0")
  //     {
  //       I2CSend (",1,1,1,0,,#");
  //       Serial.println (",1,1,1,0,,#");
  //       Timer2 (false,0);
  //     }
  //   }    
  // } 
//////////////////////////////////////////////////
  if (AdminCommand_Mode == 2)   ////////////////Kiem tra AGV da nhan duoc
  {
    if (Timer2 (true, 400) ==1)
    {
      if  (AGVStatus == "0")     //Neu AGV da dung
      {
         AdminCommand =0;
         Timer2 (false,0); 
         AdminCommand_Mode = 0;    
      }
      else if (AGVStatus == "1")
      {
        I2CSend (",1,1,2,0,,#");
        Serial.println(",1,1,2,0,,#");
        Timer2 (false,0);
      }
    }
  }
  ///////////////////////////////////////
  if (AdminCommand_Mode == 1)
  {
    // Serial.println ("Current Step:"+(String)CurrentStep);
    // Serial.println ("Next Command:"+(String)NextCommand);
      if (CurrentStep <= StepNum)         
      {
        
        if (RunOneBit1 == 1)
        {        
            String Lenh;
            ///////////////Phân tích lệnh được gửi xuống///////////////
            switch (CurrentStep)
            {
              case 1:
              {
                Lenh = Step1;
                break;
              }
              case 2:
              {
                Lenh = Step2;
                break;
              }
            }
            int Pointer = Lenh.indexOf('>');
            String RFIDCommand = Lenh.substring(0,Pointer);
            String RFIDAction = Lenh.substring(Pointer+1,Pointer+2);        
            I2CSend (",1,1,1,0," + (String)RFIDCommand+","+ (String)RFIDAction+ "#"); /// Gui lenh sang    ?Kiem tra xem co nhan duoc lenh khong
            Serial.println (",1,1,1,0," + (String)RFIDCommand+","+ (String)RFIDAction+ "#");
            RunOneBit1 =0;
            NextCommand =0;
        }

      ///////////////Neu lenh duoc hoan thanh chuyen sang lenh ke tiep  
       if (ToggleSignalPositive_int(NextCommand) == 1)    
        {
            
            I2CSend (",1,1,1,1,,,#");
            Serial.println (",1,1,1,1,,,#");
            delay (10);
            CurrentStep ++;          
            RunOneBit1 = 1;
        } 
      } 

      if (CurrentStep > StepNum) ////Neu het lenh thi quay ve che do cho
      {
        delay (5);
        AdminCommand_Mode = 0;
        AdminCommand = 0;
        RunOneBit1 =1;
        Serial.println ("Dung AGV Xoa bo nho");
        I2CSend (",1,1,2,0,,#");
        Serial.println (",1,1,2,0,,#");
        CurrentStep =1;
      }
  }


}
