#ifndef MotorKontrol_h  
#define MotorKontrol_h  

#include <Wire.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>


class MotorKontrol
{
    public:
    struct MotorK
    {
        byte motor1;
        byte motor2;
        byte motor3;
        byte motor4;
        
    };
    void Setup();
    void MotorKontrolEt();
    void SetMotorlar(byte motor1,byte motor2,byte motor3,byte motor4);
    private:

};

#endif