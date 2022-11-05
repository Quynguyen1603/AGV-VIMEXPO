void Auto_motor_control (String auto_mode)
{
  if (auto_mode == "S")
  {
    digitalWrite (motor_brake, HIGH);
    digitalWrite (motor_left_start, LOW);
    digitalWrite (motor_right_start, LOW);
  }
  else if (auto_mode == "E")
  {
    digitalWrite (motor_brake, LOW);
  }  
  else if (auto_mode == "R")
  {
    digitalWrite (motor_brake, HIGH);
    digitalWrite (motor_left_start, HIGH);
    digitalWrite (motor_right_start, HIGH);
    digitalWrite (motor_left_dir, HIGH);
    digitalWrite (motor_right_dir, LOW);   
    // Auto_motor_right_speed = map(Auto_motor_right_speed,0,3000,0,3000) ;  
    // Auto_motor_left_speed = map(Auto_motor_left_speed,0,3000,0,3000) ;  
    DAC.Set(Auto_motor_right_speed, Auto_motor_left_speed);
  } 

}