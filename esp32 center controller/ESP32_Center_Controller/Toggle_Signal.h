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