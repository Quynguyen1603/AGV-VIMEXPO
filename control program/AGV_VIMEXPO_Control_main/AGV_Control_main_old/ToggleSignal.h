///// Cac ham bat suon cua cac chan digital////////////

bool TogglePositive1 (int pin)
{
    static bool CurrentValue ;
    static bool PreValue ;
    static bool value ;
    CurrentValue = digitalRead (pin);
    if (CurrentValue == HIGH && PreValue == LOW )
    {
        value = 1;
    }
    else 
    {
        value = 0;
    }
    PreValue = CurrentValue;
    return value ;
}
bool ToggleNegative1 (int pin)
{
    static bool CurrentValue ;
    static bool PreValue ;
    static bool value ;
    CurrentValue = digitalRead (pin);
    if (CurrentValue == LOW && PreValue == HIGH )
    {
        value = 1;
    }
    else 
    {
        value = 0;
    }
    PreValue = CurrentValue;
    return value ;
}
bool Toggle2Site1 (int pin)
{
    static bool CurrentValue ;
    static bool PreValue ;
    static bool value ;
    CurrentValue = digitalRead (pin);
    if ((CurrentValue == LOW && PreValue == HIGH) or (CurrentValue == HIGH && PreValue == LOW ))
    {
        value = 1;
    }
    else 
    {
        value = 0;
    }
    PreValue = CurrentValue;
    return value ;
}
//bool TogglePositive1 (int pin)
//{
//    static bool CurrentValue ;
//    static bool PreValue ;
//    static bool value ;
//    CurrentValue = digitalRead (pin);
//    if (CurrentValue == HIGH && PreValue == LOW )
//    {
//        value = 1;
//    }
//    else 
//    {
//        value = 0;
//    }
//    PreValue = CurrentValue;
//    return value ;
//}
bool TogglePositive_bool (bool pin)
{
    static bool CurrentValue ;
    static bool PreValue ;
    static bool value ;
    CurrentValue = pin;
    if (CurrentValue == 1 && PreValue == 0 )
    {
        value = 1;
    }
    else 
    {
        value = 0;
    }
    PreValue = CurrentValue;
    return value ;
}
