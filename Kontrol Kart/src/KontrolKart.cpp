#include <KontrolKart.h>

bool state=false;

Kontrol::MotorKontrol motor;
void Kontrol::Setup(){
    Wire.begin(8);
    Motor1.attach(3);
    Motor2.attach(5);
    Motor3.attach(6);
    Motor4.attach(9);
    Wire.onReceive(ReceiveEvent);
}

void ReceiveEvent(int howMany){
    while(Wire.available() >= sizeof(motor)) { 
    Wire.readBytes((char*)&motor, sizeof(motor));
 }
 state=true;
}

void Kontrol::Loop(){
    if(state){
        MotorKontrolFonksiyon();
        state=false;
    }
}

void Kontrol::MotorKontrolFonksiyon(){
    Motor1.write(motor.Motor1);
    Motor2.write(motor.Motor2);
    Motor3.write(motor.Motor3);
    Motor4.write(motor.Motor4);
}
