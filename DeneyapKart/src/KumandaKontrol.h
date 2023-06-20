#ifndef KUMANDAKONTROL_H
#define KUMANDAKONTROL_H

#include <lsm6dsm.h>

LSM6DSM IMU;

class KumandaKontrol
{
private:
    bool pAState=false;
    unsigned long pATime=0;
    bool armstate=false;
    unsigned long armtime=0;
    /* data */
public:
    void KumandaSetup();
    void MotorKontrol(int x,int y,int z);
    void ArmCheck();
    void JoystickS();
    void ArmS();
    void DisarmS();
    void OtonomS();
    void GuncelleS();
};


#endif