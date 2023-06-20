#include <KumandaKontrol.h>
#include <MotorKontrol.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <OtonomGorev.h>
#include <OTA.h>
OtonomGorev Otonom;
OTA ota;
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void KumandaKontrol::MotorKontrol(int x, int y, int z) {
    byte throttle = map(x, 0, 1023, 0, 255);
    byte pitch = map(y, 0, 1023, 0, 255);
    byte roll = map(z, 0, 1023, 0, 255);
    byte Motor1= throttle + pitch + roll;
    byte Motor2= throttle - pitch - roll;
    byte Motor3= throttle - pitch - roll;
    byte Motor4= throttle + pitch + roll;
    Motorlar.SetMotorlar(Motor1,Motor2,Motor3,Motor4);
    Motorlar.MotorKontrolEt();
    Update.begin(115200);
}

MotorKontrol Motorlar;
AsyncWebServer server(80);

void KumandaKontrol::KumandaSetup() {
    Motorlar.Setup();
    IMU.begin();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    JoystickS();
    ArmS();
    DisarmS();
    OtonomS();
    GuncelleS();

    server.begin();
}

void KumandaKontrol::JoystickS(){
    server.on("/joystick", HTTP_GET, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("x") && request->hasParam("y") && request->hasParam("z")) {
            if(armstate)
            {int x = request->getParam("x")->value().toInt();
            int y = request->getParam("y")->value().toInt();
            int z = request->getParam("z")->value().toInt();
            MotorKontrol(x, y, z);}
        }
        request->send(200);
    });
};

void KumandaKontrol::ArmS(){
    server.on("/arm", HTTP_GET, [this](AsyncWebServerRequest* request) {
        armstate = true;
        Otonom.SetARMState(true);
        request->send(200);
    });
};

void KumandaKontrol::DisarmS(){
    server.on("/disarm", HTTP_GET, [this](AsyncWebServerRequest* request) {
        armstate = false;
        Otonom.SetARMState(false);
        request->send(200);
    });
};

void KumandaKontrol::OtonomS(){
    server.on("/otonom", HTTP_GET, [this](AsyncWebServerRequest* request) {
        Otonom.IlkGorev();
        request->send(200);
    });
    
};

void KumandaKontrol::GuncelleS(){
    server.on("/guncelle", HTTP_GET, [this](AsyncWebServerRequest* request) {
        if(ota.FirmwareCheck()){
            ota.FirmwareUpdate();
        }
        request->send(200);
    });
};

void KumandaKontrol::ArmCheck(){
    
    if(armtime+300<millis()){if(armstate)
    {
        if(pAState){
            if(IMU.readFloatAccelZ() > 0.9)
        {
            pAState = true;
            pATime = millis();
        }}
        if(pATime + 3000 < millis())
        {
            armstate = false;
            Otonom.SetARMState(false);
            pAState = false;
            pATime = 0;
            Motorlar.SetMotorlar(0,0,0,0);
            Motorlar.MotorKontrolEt();
        }
    }
    armtime = millis();
    }
}