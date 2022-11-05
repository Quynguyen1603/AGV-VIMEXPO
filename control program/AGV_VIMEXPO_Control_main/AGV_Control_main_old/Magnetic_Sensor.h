//int Magnetic_Sensor (int mode) /// mode 0 == straight, mode 1 = right brach, mode 2 = left brand, mode 3 = no select
//{
// int magnetic_sensor_sample[30] = {755,710,695,680,660,645,625,610,590,575,555,540,520,505,490,470,455,435,420,400,385,370,350,335,315,300,280,265};
// int value;
// int Position =0;
// int a;
// ////////////Chọn chế độ cho Cảm biến line///////
// if (mode == 0)
// {
//    digitalWrite (guide_sensor_sil1, LOW);
//    digitalWrite (guide_sensor_sil2, LOW);
// }
// else if (mode == 1)
//  {
//    digitalWrite (guide_sensor_sil1, HIGH);
//    digitalWrite (guide_sensor_sil2, LOW);
// }
//  else if (mode == 2)
//  {
//    digitalWrite (guide_sensor_sil1, LOW);
//    digitalWrite (guide_sensor_sil2, HIGH);
// }
//  else 
//  {
//    digitalWrite (guide_sensor_sil1, HIGH);
//    digitalWrite (guide_sensor_sil2, HIGH);
// }
//
// ////////////////////////Kiễm tra xem có line hay không///////
// 
// if (digitalRead (out_guide_sensor) == 1)
// {
//   a = 69;
// }
// ///////////Giá trị cảm biến line từ đưa về từ -15 đến 15
// else 
// {
// value = analogRead (analog_magnetic);
// //Serial.println (value);
// for (int i = 0; i < 30 ;i ++)
// {
//   if (magnetic_sensor_sample [i] >= value && value >= magnetic_sensor_sample [i+1])
//   {
//     Position = i +1;
//   }
// }
// a = Position -15; 
// }
// return a;
// 
//}
