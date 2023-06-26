/* 
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-web-server-websocket-sliders/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
#include "html.h"


// Replace with your network credentials
const char *ssid = "Super-Haching";
const char *password = "27101966";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create a WebSocket object

AsyncWebSocket ws("/ws");

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;
Servo Servo7;

String message = "";
String sliderValue1 = "30";
String sliderValue2 = "80";
String sliderValue3 = "70";
String sliderValue4 = "25";
String sliderValue5 = "0";
String sliderValue6 = "0";
String sliderValue7 = "10";

//Get Slider Values
String getSliderValues() {

  StaticJsonDocument<1000> sliderValues;
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);
  sliderValues["sliderValue4"] = String(sliderValue4);
  sliderValues["sliderValue5"] = String(sliderValue5);
  sliderValues["sliderValue6"] = String(sliderValue6);
  sliderValues["sliderValue7"] = String(sliderValue7);

  char Nachricht[1000];
  serializeJson(sliderValues, Nachricht, sizeof(Nachricht));

  return Nachricht;
}

unsigned long currentMillis;
long previousMillis = 0;  // set up timers
float prev_angle_1 = (float)sliderValue1.toInt();
float prev_angle_2 = (float)sliderValue2.toInt();
float prev_angle_3 = (float)sliderValue3.toInt();
float prev_angle_4 = (float)sliderValue4.toInt();
float prev_angle_5 = (float)sliderValue5.toInt();
float prev_angle_6 = (float)sliderValue6.toInt();
float prev_angle_7 = (float)sliderValue7.toInt();


// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char *)data;
    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      smoothValue(sliderValue1.toInt(), &prev_angle_1, Servo1);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      smoothValue(sliderValue2.toInt(), &prev_angle_2, Servo2);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      smoothValue(sliderValue3.toInt(), &prev_angle_3, Servo3);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      smoothValue(sliderValue4.toInt(), &prev_angle_4, Servo4);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("5s") >= 0) {
      sliderValue5 = message.substring(2);
      smoothValue(sliderValue5.toInt(), &prev_angle_5, Servo5);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("6s") >= 0) {
      sliderValue6 = message.substring(2);
      smoothValue(sliderValue6.toInt(), &prev_angle_6, Servo6);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("7s") >= 0) {
      sliderValue7 = message.substring(2);
      smoothValue(sliderValue7.toInt(), &prev_angle_7, Servo7);
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (strcmp((char *)data, "getValues") == 0) {
      notifyClients(getSliderValues());
    }
  }
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}


void smoothValue(int target_value, float *prev_value, Servo &theServo) {
  unsigned int i = 0;
  float smoothed_value = 0;
  while (i < 500) {
    currentMillis = millis();
    if (currentMillis - previousMillis > 5) {
      previousMillis = currentMillis;
      smoothed_value = (target_value * 0.05) + (*prev_value * 0.95);
      theServo.write(round(smoothed_value));
      if (round(smoothed_value) == target_value) {
        break;
      }
      Serial.println(smoothed_value);
      *prev_value = smoothed_value;
    }
  }
}

void setup() {
  Serial.begin(115200);
  Servo1.attach(16, 500, 2400);  //GPIO16 = D0
  Servo2.attach(14, 500, 2400);  //GPIO14 = D5
  Servo3.attach(12, 500, 2400);  //GPIO12 = D6
  Servo4.attach(5, 500, 2400);   //GPIO5 = D1
  Servo5.attach(4, 500, 2400);   //GPIO4 = D2
  Servo6.attach(0, 500, 2400);   //GPIO0 = D3
  Servo7.attach(2, 500, 2400);   //GPIO2 = D4
  initWiFi();

  initWebSocket();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
  });


  // Start server
  server.begin();
}

void loop() {


  ws.cleanupClients();
}