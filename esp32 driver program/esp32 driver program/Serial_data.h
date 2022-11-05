void Serial_Data_DP(String raw_string )
{
  String str1 = "", str2="", str3="",str4="",str5="",str6="",str7="";
  int a = raw_string.length ();
  int dem = 0; 
  for (int i =0; raw_string[i]!= '#'; i++)
    {
      if ( raw_string[i]== ',')
      {
        dem ++;
      }
      else 
      {
        switch (dem)
        {
          case 1:
          {
            str1+=raw_string[i];
            break;
          }
          case 2:
          {
            str2+=raw_string[i];
            break;
          }
          case 3:
          {
            str3+=raw_string[i];
            break;
          }
          case 4:
          {
            str4+=raw_string[i];
            break;
          }
          case 5:
          {
            str5+=raw_string[i];
            break;
          }
          case 6:
          {
            str6+=raw_string[i];
            break;
          }
          case 7:
          {
            str7+=raw_string[i];
            break;
          }
        }
      }
    }
    Serial.println (str1);
    Serial.println (str2);
    Serial.println (str3);
    Serial.println (str4);
    Serial.println (str5);
    if (str2 == "M")  // Manual mode
    {
      Mode_select =1;
    }
    else if (str2 == "A")  //Auto mode
    {
      Mode_select =2; 

    }
    else if (str2 == "AM") //Auto Motor control
    {
      Auto_mode = str3; 
      Auto_motor_right_speed = str5.toInt();
      Auto_motor_left_speed = str4.toInt();
    }
    else if (str2 == "AI") //Auto Information
    {

    }
}



void Serial_Data_Receive()
{
  char c;
  
  while (Serial.available () && c != '#')
  {
      
    c = Serial.read ();
    RAW_String += c;
    //Serial.println (c);

  }
  if (c == '#' && RAW_String != "")
  {
    Serial.println ("Chuoi la" + (String)RAW_String);
    Serial_Data_DP (RAW_String);
    RAW_String = "";
    c = ' ';
  }  
}


