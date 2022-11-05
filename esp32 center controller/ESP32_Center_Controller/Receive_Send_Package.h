
void Receive_Package (bool en)
{
  if ( en == 1)
  {
    ///////////STEP0/////////
    if (Receive_Step == 0)    
    {
      if (DATAStatus == 2)
      {
        if(Timer1_RStep0(true, 2000) == 1)     
        {
          Receive_Step ++;
          Timer1_RStep0(false, 0);
        }   
      }
      else 
      {
        if (Timer2(true, 200) == 1)
        {
          Send_to_AGV (2,0,0, "    ", "    ");
          Timer2 (false,0);
        }
      }
    }
    ///////////STEP1////////////
    if (Receive_Step == 1)    
    {
      if ( Timer3 (true,500) ==1 )
      {
        if (DATAStatus == 1)
        {
          Timer3(false,0);
          Receive_Step ++;          
        }
        else 
        {
        Send_to_AGV(1,1, "S1>1", "    ");
        }
      }
    }
/////////////STEP2/////////////
  if (Receive_Step == 2)
  {
    Package_Check_en =1;
    if (Hook_have_package == 1)
    {
      Hold_bit1 = 1;
      Package_Check_en =0;
    }
    if (Hold_bit1 ==1)
    {
      if (Timer4 (true, 6000)  == 1 )          //////Thoi gian tu luc phat hien moc den luc kep xi lanh lai
      {
        digitalWrite(Xilanh, HIGH);
        Timer4 (false,0);    
        Hold_bit1 =0;    
      }  
    }
  }
  }
  else 
  {
    Receive_Step = 0;
  }

}
////////////////////////////////////////////////////////////////////////////
void Send_Package(bool en)
{
  if( en ==1)
  {
    /////////////////////STEP0///////////////////
    if (Send_Step == 0)
    {
      digitalWrite(Xilanh, LOW);
      if (DATAStatus == 2)
      {
        if(Timer5(true, 2000) == 1)     
        {
          Send_Step ++;
          Timer5(false, 0);
        }   
      }
      else 
      {
        if (Timer2(true, 200) == 1)
        {
          Send_to_AGV (2,0,0, "    ","    ");
          Timer2 (false,0);
        }
      }
    }
    ///////////////////STEP1///////////////////
    if (Send_Step ==1)
    {
      if ( Timer3 (true,500) ==1 )
      {
        if (DATAStatus== 1)
        {
          Timer3(false,0);
          Send_Step ++;          
        }
        else 
        {
          Send_to_AGV(1,2,0, "S3>1","S2>1");
        }
      }      
    }
    ///////////////////////STEP2//////////////
    if  (Send_Step == 2)  
    {
      Package_Check_en =1;    /// Bat cam bien phat hien co hang 
      if (Hook_have_package == 0)   /// Co moc khong co hang
      {
        Hold_bit2 = 1;
        Package_Check_en =0;
      }
      if (Hold_bit2 ==1)
      {
        if (Timer6 (true, 2000)  == 1 )          //////Thoi gian tu luc phat hien moc den luc phat lenh AGV di chuyen
        {
          if (Timer7 (true, 200) ==1)             /////Gửi cho đến khi AGV nhận được
          {
              if (DATAStatus != 1)
              {
                Send_to_AGV(3,0, "    ","    ");
                Timer7 (false,0);
              }
              else
              {
                Timer6(false,0);
                Send_Step ++;
                Hold_bit2 =0;
              }
          }
        }  
      }      
    }
    /////////////////////STEP3//////////////
    if (Send_Step == 3)
    {
      if (DATAStatus == 3)
      {
        digitalWrite(Conveyor_Stop,HIGH);
      } 
      else
      {
        digitalWrite(Conveyor_Stop,LOW);        
      }
    }
  }
  else {
    Send_Step = 0;
  }
}