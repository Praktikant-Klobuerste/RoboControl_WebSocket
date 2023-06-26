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

uint8_t angle_1 = sliderValue1.toInt();
uint8_t angle_2 = sliderValue2.toInt();
uint8_t angle_3 = sliderValue3.toInt();
uint8_t angle_4 = sliderValue4.toInt();
uint8_t angle_5 = sliderValue5.toInt();
uint8_t angle_6 = sliderValue6.toInt();
uint8_t angle_7 = sliderValue7.toInt();


float prev_angle_1;
float prev_angle_2;
float prev_angle_3;
float prev_angle_4;
float prev_angle_5;
float prev_angle_6;
float prev_angle_7;


void initWifi();
void notifyClients(String sliderValues);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void initWebSocket();
void smoothServo(int target_value, float *prev_value, Servo &theServo);


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

  currentMillis = millis();

  if (currentMillis - previousMillis > 5) {
    previousMillis = currentMillis;
    smoothServo(angle_1, &prev_angle_1, Servo1);
    smoothServo(angle_2, &prev_angle_2, Servo2);
    smoothServo(angle_3, &prev_angle_3, Servo3);
    smoothServo(angle_4, &prev_angle_4, Servo4);
    smoothServo(angle_5, &prev_angle_5, Servo5);
    smoothServo(angle_6, &prev_angle_6, Servo6);
    smoothServo(angle_7, &prev_angle_7, Servo7);
  }

  if (round(prev_angle_1) != angle_1) {
    Serial.print(angle_1);
    Serial.print("\t");
    Serial.print(prev_angle_1);
    Serial.print("\t");
    Serial.println(round(prev_angle_1));
  }

  ws.cleanupClients();
}



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
      angle_1 = sliderValue1.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      angle_2 = sliderValue2.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      angle_3 = sliderValue3.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      angle_4 = sliderValue4.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("5s") >= 0) {
      sliderValue5 = message.substring(2);
      angle_5 = sliderValue5.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("6s") >= 0) {
      sliderValue6 = message.substring(2);
      angle_6 = sliderValue6.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("7s") >= 0) {
      sliderValue7 = message.substring(2);
      angle_7 = sliderValue7.toInt();
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


void smoothServo(int target_value, float *prev_value, Servo &theServo) {
  if (round(*prev_value) != target_value) {
    float smoothed_value = 0;

    smoothed_value = (target_value * 0.05) + (*prev_value * 0.95);
    theServo.write(round(smoothed_value));
    *prev_value = smoothed_value;
  }
}