
bool pressed = false;

while(true)
{
    if(joy2Btn(2))
    {
        if(!pressed)
        {
            if(motor[intake] == 100)
            {
                motor[intake] = 0;
            }
            else
            {
                motor[intake] = 100;
            }
        }
        pressed = true;
    }
    else
    {
        pressed = false;
    }
}
