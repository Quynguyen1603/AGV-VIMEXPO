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
 return 0;
 }
}

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
int Safe_Sensor(int lidar_mode)
{
  int i;
  bool val1=0,val2=0,val3=0;
  val1=digitalRead(out3_safe_sensor);
  val2=digitalRead(out2_safe_sensor);
  val3=digitalRead(out1_safe_sensor);
  if(lidar_mode==1)
    {
      digitalWrite(lidar_select_1,HIGH);
      digitalWrite(lidar_select_2,HIGH);
    }
  if(lidar_mode==2)  /////DI cham
    {
      digitalWrite(lidar_select_1,LOW);
      digitalWrite(lidar_select_2,HIGH);
    }
  if(lidar_mode==3)  //////Re Trai
    {
      digitalWrite(lidar_select_1,HIGH);
      digitalWrite(lidar_select_2,LOW);
    }
  if(lidar_mode==4)  ///Re Phai
    {
      digitalWrite(lidar_select_1,LOW);
      digitalWrite(lidar_select_2,LOW);
    }
    
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
  return 0; 
}
