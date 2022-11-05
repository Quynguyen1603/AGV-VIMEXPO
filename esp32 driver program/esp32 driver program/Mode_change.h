void Mode_change (int Mode)
{
  static int Mode_sub =0;
  if (Mode != Mode_sub)
  {
    digitalWrite (motor_left_start, LOW);
    digitalWrite (motor_right_start, LOW);
    DAC.Set (0,0);
    Mode_sub = Mode;
  }
}