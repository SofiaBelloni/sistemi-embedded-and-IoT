#include "ConnectionManager.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

ConnectionManager::ConnectionManager(char* ssid, char* password){
    WiFi.begin(ssid, password);
    Serial.print("Connecting...");
    while (WiFi.status() != WL_CONNECTED) {  
        delay(500);
        Serial.print(".");
    } 
    //Serial.println("Connected: \n local IP: "+WiFi.localIP());
}

bool ConnectionManager::IsConnected(){
    return WiFi.status()== WL_CONNECTED;
}

int ConnectionManager::SendData(char* address, const char* message){
    if (this->IsConnected())
    {
        HTTPClient http;    
        http.begin(String(address) + "/api/data");      
        http.addHeader("Content-Type", "application/json");     
        int ret = http.POST(message);   
        http.end();
        return ret;
    }
    return -1;
}
    