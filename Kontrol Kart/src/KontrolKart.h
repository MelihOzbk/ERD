#ifndef KontrolKart_H
#define KontrolKart_H
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

Servo Motor1;
Servo Motor2;
Servo Motor3;
Servo Motor4;

class Kontrol
{
    private:
    
    public:
    
    struct MotorKontrol
    {
        byte Motor1;
        byte Motor2;
        byte Motor3;
        byte Motor4;
    };
    void Setup();
    void Loop();
    void MotorKontrolFonksiyon();
    
};
#endif