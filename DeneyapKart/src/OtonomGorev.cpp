#include <OtonomGorev.h>

void OtonomGorev::IlkGorev()
{
    if(armstate)
    {
        //MotorKontrol::SetMotorlar(0,0,0,0);
    }
    else
    {
        //MotorKontrol::SetMotorlar(0,0,0,0);
    }
}

void OtonomGorev::SetARMState(bool state)
{
    armstate=state;
}