//lenght counter for long
int valueLenghtLG(long value)
{
    int count = 0;
    long modVal = value;
    if(value != 0)
    {
        while(modVal > 0)
        {
            modVal = modVal / 10;
            count++;
        }
    } 
    else count = 1;

    return count;
    
}