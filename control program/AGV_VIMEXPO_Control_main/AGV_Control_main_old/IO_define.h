
#define guide_sensor_sil1  23
#define guide_sensor_sil2 22

#define analog_magnetic A1
#define out1_safe_sensor  A15
#define out2_safe_sensor  A14
#define out3_safe_sensor  A13

#define over_left A10
#define over_right A9

#define out_guide_sensor A4
#define lidar_select1 42
#define lidar_select2 43

#define sensor_charge_in A8
#define sensor_charge_out 39

#define package_detect A7


void IO_config()
{
  // đã khai báo đặt tên trong read_input.h
  pinMode(out1_safe_sensor, INPUT_PULLUP); // cam bien sink gần nhất
  pinMode(out2_safe_sensor, INPUT_PULLUP); // cảm biến sink trung bình
  pinMode(out3_safe_sensor, INPUT_PULLUP); // cảm biến sink xa nhất 

  pinMode(over_left, INPUT_PULLUP);   //CTHT trái
  pinMode(over_right, INPUT_PULLUP);  //CTHT phải

  pinMode(out_guide_sensor, INPUT_PULLUP);    //kiem tra xem co line khong
  pinMode(sensor_charge_in,INPUT_PULLUP);
  pinMode(package_detect,INPUT_PULLUP);

  pinMode(sensor_charge_out, OUTPUT);
  
  pinMode(lidar_select1, OUTPUT);
  pinMode(lidar_select2, OUTPUT);
  
  pinMode(guide_sensor_sil1, OUTPUT);
  pinMode(guide_sensor_sil2, OUTPUT);

}
