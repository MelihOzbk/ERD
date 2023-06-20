#include <MotorKontrol.h>
MotorKontrol::MotorK Motorlar;
void MotorKontrol::Setup()
{
    Wire.begin(); // join I2C bus (address optional for master)
    Motorlar.motor1 = 0;
    Motorlar.motor2 = 0;
    Motorlar.motor3 = 0;
    Motorlar.motor4 = 0;
    MotorKontrolEt();
}

void MotorKontrol::MotorKontrolEt(){
    Wire.beginTransmission(8); // transmit to device #8
    // motorlari gönder
    Wire.write(Motorlar.motor1);              // sends one byte
    Wire.write(Motorlar.motor2);              // sends one byte
    Wire.write(Motorlar.motor3);              // sends one byte
    Wire.write(Motorlar.motor4);              // sends one byte
    Wire.endTransmission();    // stop transmitting

}

void MotorKontrol::SetMotorlar(byte motor1,byte motor2,byte motor3,byte motor4){
    Motorlar.motor1 = motor1;
    Motorlar.motor2 = motor2;
    Motorlar.motor3 = motor3;
    Motorlar.motor4 = motor4;
}