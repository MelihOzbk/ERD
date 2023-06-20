#include <OTA.h>


void OTA::OTASetup()
{
    // ArduinoOTA.setHostname("ESP32");
    // ArduinoOTA.setPassword("1234");
    // ArduinoOTA.begin();
}

void OTA::OTALoop()
{
    // ArduinoOTA.handle();
}

void OTA::FirmwareUpdate(){
    WiFiClientSecure client;
    client.setCACert(rootCACertificate);
    t_httpUpdate_return ret = httpUpdate.update(client, firmwareURL);

    switch (ret) {
    case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

    case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
}
int OTA::FirmwareCheck(){
    String payload;
    int httpCode;
    String FirmwareURL = "";
    FirmwareURL += firmwareVersionURL;
    FirmwareURL += "?";
    FirmwareURL += String(rand());
    Serial.println(FirmwareURL);
    WiFiClientSecure * client = new WiFiClientSecure;

    if (client) {
        client -> setCACert(rootCACertificate);
        HTTPClient https;

        if (https.begin( * client, FirmwareURL)) {
            Serial.print("[HTTPS] GET...\n");
            // start connection and send HTTP header
            delay(100);
            httpCode = https.GET();
            delay(100);
            if (httpCode == HTTP_CODE_OK) // if version received
            {
                payload = https.getString(); // save received version
            } else {
                Serial.print("Error Occured During Version Check: ");
                Serial.println(httpCode);
            }
            https.end();
        }
        delete client;
    }

    if (httpCode == HTTP_CODE_OK) // if version received
    {
        payload.trim();
        if (payload.equals(FirmwareVer)) {
            Serial.printf("\nDevice  IS Already on Latest Firmware Version:%s\n", FirmwareVer);
            return 0;
        } else {
            Serial.println(payload);
            Serial.println("New Firmware Detected");
            return 1;
        }
    }
    return 0;
}

void OTA::OTALoop(){
    if (millis() - lastUpdate > 60000) {
        lastUpdate = millis();
        if (FirmwareCheck()) {
            FirmwareUpdate();
        }
    }
}