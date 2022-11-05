bool TimerOut(bool state, int time_delay)
{
  static long dtime; 
  static bool value;
  if((state == true))
  {
    if((millis() - dtime)>=time_delay)
    {
    value =1;
    dtime = millis();
    }
  }
  else
  {
    if ( time_delay != 0)
    {
      value = 1;
      if((millis() - dtime)>=time_delay)
      value =0;
    }
    else 
    {
      dtime = millis();
      value = 0;
      state = 0;
    }
  }
 return value;
}

void I2CReceive (String* I2CRec_Str)
{
  String str1 = "";
  char c;
  Wire.requestFrom(8, 60);
  TimerOut(false,0);
  while (Wire.available() && c != '#') 
  {
    
        
    c = Wire.read(); // receive a byte as character
    str1 +=c    ;     // print the character
    // if (TimerOut(true,50) == 1 )
    // {
    //         c= '#';
    //         TimerOut(false, 0);
    // }
  }
  
  //Serial.println ("Chuoi la:" + (String)str1);
 *I2CRec_Str = str1;
}



void I2CSend (String I2CSend_Str)
{
  Serial.println ("Lenh gui sang AGV:" + (String) I2CSend_Str);
  int a = I2CSend_Str.length ();
  char I2CSend_Char [a];
  I2CSend_Str.toCharArray(I2CSend_Char,a+1);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(I2CSend_Char);              // sends one byte
  Wire.endTransmission();
}