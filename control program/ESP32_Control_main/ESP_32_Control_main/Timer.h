bool Timer1(bool state, int time_delay)
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
bool Timer2(bool state, int time_delay)
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
bool Timer3(bool state, int time_delay)
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