

void requestEvent() 
{
  Wire.write(Mess_char); // respond with message of 1 byte
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

  }
  else if (Mode == 2)  ///Nhận dữ liệu ở chế độ Auto
  {
    String str1, str2, str3,str4,str5,str6;
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
          case 6:
          {
            str6+=Str[i];
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
   AdminNext = str4;
  if (AdminCommand == "1")   
  {
   RFIDCommand = str5;
   RFIDAction = str6;
  }
  else if (AdminCommand == "2")  
  {
    RFIDCommand = "";
    RFIDAction = "";
  }  
  

  }
  
}
void I2C_define ()
{
  Wire.begin(8);                // join i2c bus with address #8
  Wire.setClock(200000);
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event 
}
