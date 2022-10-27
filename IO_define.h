#define guide_sensor_sil1  43
#define guide_sensor_sil2 42

#define analog_magnetic A1
#define out1_safe_sensor  A15
#define out2_safe_sensor  A14
#define out3_safe_sensor  A13

#define over_left A10
#define over_right A9

#define out_guide_sensor A4


#define 

void IO_config()
{
  // đã khai báo đặt tên trong read_input.h
  pinMode(out1_safe_sensor, INPUT_PULLUP); // cam bien sink gần nhất
  pinMode(out2_safe_sensor, INPUT_PULLUP); // cảm biến sink trung bình
  pinMode(out3_safe_sensor, INPUT_PULLUP); // cảm biến sink xa nhất 
//  pinMode(alarm_left, INPUT_PULLUP); //canh bao trai
//  pinMode(alarm_right, INPUT_PULLUP); //canh bao phai
  pinMode(over_left, INPUT_PULLUP);   //CTHT trái
  pinMode(over_right, INPUT_PULLUP);  //CTHT phải
//  pinMode(sensor_charge, INPUT_PULLUP);   //CB sạc
//  pinMode(pb_start_auto, INPUT_PULLUP);   //?
//  pinMode(pb_alarm_reset, INPUT_PULLUP);  //?
//  pinMode(switch_auto_manual, INPUT_PULLUP);  //chuyen doi auto manual
  pinMode(out_guide_sensor, INPUT_PULLUP);    //kiem tra xem co line khong
  pinMode(led_left, OUTPUT);
  pinMode(led_right, OUTPUT);
//  pinMode(target_low_position, INPUT_PULLUP);
//  pinMode(target_high_position, INPUT_PULLUP);
//  pinMode(target_home_position, INPUT_PULLUP);
//  pinMode(cylinder_error, INPUT_PULLUP);
//  pinMode(emergency_stop, INPUT_PULLUP);
//  pinMode(remote_straight, INPUT_PULLUP);
//  pinMode(remote_back, INPUT_PULLUP);
//  pinMode(remote_left, INPUT_PULLUP);
//  pinMode(remote_right, INPUT_PULLUP);
  ////////////////////////////////////////
  // pinMode(buzzer_auto, OUTPUT);     //còi auto
  // pinMode(buzzer_alarm, OUTPUT);    //còi canh bao
  pinMode(motor_left_start, OUTPUT);  
  pinMode(motor_left_dir, OUTPUT);
  
//  pinMode(motor_left_reset, OUTPUT);
  pinMode(motor_right_start, OUTPUT);
  pinMode(motor_right_dir, OUTPUT);
//  pinMode(motor_right_reset, OUTPUT);
//  pinMode(sensor_charge_light, OUTPUT);
//  pinMode(error_lamp, OUTPUT);
//  pinMode(low_position_cylinder, OUTPUT);
//  pinMode(high_position_cylinder, OUTPUT);
//  pinMode(contactor, OUTPUT);
//  pinMode(homing, OUTPUT);
//  pinMode(enable, OUTPUT);
//  pinMode(reset, OUTPUT);
//  pinMode(home_lamp, OUTPUT);
  pinMode(guide_sensor_sil1, OUTPUT);
  pinMode(guide_sensor_sil2, OUTPUT);

}
