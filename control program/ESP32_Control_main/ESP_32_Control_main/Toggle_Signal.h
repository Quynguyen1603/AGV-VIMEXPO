bool ToggleNegative1_String (String pin)
{
    static String CurrentValue ;
    static String PreValue ;
    static bool value ;
    CurrentValue = pin;
    if (CurrentValue == "0" && PreValue == "1")
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

bool ToggleSignal_int (int Variable)
{
    static int CurrentValue ;
    static int PreValue ;
    static bool value ;
    CurrentValue = Variable;
    if (CurrentValue != PreValue )
    {
        value = 1;
        PreValue = CurrentValue;
    }
    else 
    {
        value = 0;
    }
    
    return value ;
}
bool ToggleSignalPositive_int (int Variable)
{
    static int CurrentValue ;
    static int PreValue ;
    static bool value ;
    CurrentValue = Variable;
    if (CurrentValue == 1 && PreValue == 0)
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