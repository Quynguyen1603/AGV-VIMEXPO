void I2C_DP (String I2CReceive,String* Data1, String* Data2, String* Data3, String* Data4, String* Data5, String* Data6, String* Data7, String* Data8, String* Data9)
{
    String str1, str2, str3,str4,str5,str6,str7,str8,str9;
    int a = I2CReceive.length ();
    int dem =0;
    for (int i =0; I2CReceive[i]!= '#'; i++)
    {
      if ( I2CReceive[i]== ',')
      {
        dem ++;
      }
      else 
      {
        switch (dem)
        {
          case 1:
          {
            str1+=I2CReceive[i];
            break;
          }
          case 2:
          {
            str2+=I2CReceive[i];
            break;
          }
          case 3:
          {
            str3+=I2CReceive[i];
            break;
          }
          case 4:
          {
            str4+=I2CReceive[i];
            break;
          }
          case 5:
          {
            str5+=I2CReceive[i];
            break;
          }
          case 6:
          {
            str6+=I2CReceive[i];
            break;
          }
          case 7:
          {
            str7+=I2CReceive[i];
            break;
          }
          case 8:
          {
            str8+=I2CReceive[i];
            break;
          }
          case 9:
          {
            str9+=I2CReceive[i];
            break;
          }
        }
      }
    }
*Data1 =str1;
*Data2 =str2;
*Data3 =str3;
*Data4 =str4;
*Data5 =str5;
*Data6 =str6;
*Data7 =str7;
*Data8 =str8;
*Data9 =str9;
}
bool Is_True_Data(String Str)
{
  String Sub;
  int Len = Str.length();
  Sub = Str.substring (Len-1,Len);
  if (Sub =="#")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}