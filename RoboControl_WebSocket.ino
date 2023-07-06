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
#include <ArduinoOTA.h>
#include <AsyncElegantOTA.h>
#include <PubSubClient.h>
#include <Servo.h>
#include "html.h"


// Replace with your network credentials
const char *ssid = "Super-Haching";
const char *password = "27101966";
const char *mqtt_server = "192.168.2.230";
const char *mqtt_username = "Ravson";
const char *mqtt_password = "Hunzapfen1";

#define clientID_Name "Robo"
#define USER_MQTT_CLIENT_NAME "Robo"

char charPayload[50];
const char *willTopic = USER_MQTT_CLIENT_NAME "/LWT";


AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

WiFiClient espClient;
PubSubClient client(espClient);

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;
Servo Servo7;

String message = "";
String sliderValue1 = "100";
String sliderValue2 = "140";
String sliderValue3 = "120";
String sliderValue4 = "25";
String sliderValue5 = "80";
String sliderValue6 = "80";
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
int stepFlag = 0;
long previousStepMillis = 0;
bool startAnimation = false;
bool servosArmed = true;

uint8_t angle_1 = sliderValue1.toInt();
uint8_t angle_2 = sliderValue2.toInt();
uint8_t angle_3 = sliderValue3.toInt();
uint8_t angle_4 = sliderValue4.toInt();
uint8_t angle_5 = sliderValue5.toInt();
uint8_t angle_6 = sliderValue6.toInt();
uint8_t angle_7 = sliderValue7.toInt();


float prev_angle_1 = float(angle_1);
float prev_angle_2 = float(angle_2);
float prev_angle_3 = float(angle_3);
float prev_angle_4 = float(angle_4);
float prev_angle_5 = float(angle_5);
float prev_angle_6 = float(angle_6);
float prev_angle_7 = float(angle_7);


void initWifi();
void notifyClients(String sliderValues);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void initWebSocket();
void smoothServo(int target_value, float *prev_value, Servo &theServo, float k1, float k2);
void initServo();
void eyeAnimation();
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();


void setup() {
  Serial.begin(115200);
  initServo();
  initWiFi();

  initWebSocket();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
  });

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


  ArduinoOTA.setHostname("Robo_Control");
  ArduinoOTA.begin();

  AsyncElegantOTA.begin(&server);  // Start AsyncElegantOTA

  // Start server
  server.begin();
}


void loop() {

  currentMillis = millis();

  if (currentMillis - previousMillis > 5) {
    previousMillis = currentMillis;
    smoothServo(angle_1, &prev_angle_1, Servo1, 0.10, 0.90);
    smoothServo(angle_2, &prev_angle_2, Servo2, 0.15, 0.85);
    smoothServo(angle_3, &prev_angle_3, Servo3, 0.10, 0.90);
    smoothServo(angle_4, &prev_angle_4, Servo4, 0.15, 0.85);
    smoothServo(angle_5, &prev_angle_5, Servo5, 0.05, 0.95);
    smoothServo(angle_6, &prev_angle_6, Servo6, 0.05, 0.95);
    smoothServo(angle_7, &prev_angle_7, Servo7, 0.05, 0.95);

    eyeAnimation();
  }

  if (round(prev_angle_1) != angle_1) {
    Serial.print(angle_1);
    Serial.print("\t");
    Serial.print(prev_angle_1);
    Serial.print("\t");
    Serial.println(round(prev_angle_1));
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ArduinoOTA.handle();

  ws.cleanupClients();
}



// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
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
    Serial.println(message);
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
      notifyClients(servosArmed ? "armed&true" : "armed&false");
    }

    if (strcmp((char *)data, "reset") == 0) {
      Serial.println("Restarting ESP");
      client.publish(USER_MQTT_CLIENT_NAME "/status", "Restarting..");
      ESP.restart();
    }

    if (message.indexOf("armed&") >= 0) {
      if (message.substring(6) == "true") {
        servosArmed = true;
        notifyClients(servosArmed ? "armed&true" : "armed&true");
        client.publish(USER_MQTT_CLIENT_NAME "/status", "Arming Servos..");
        initServo();
      } else {
        servosArmed = false;
        notifyClients(servosArmed ? "armed&true" : "armed&false");
        client.publish(USER_MQTT_CLIENT_NAME "/status", "Disarming Servos..");
        Servo1.detach();  //GPIO16 = D0
        Servo2.detach();  //GPIO14 = D5
        Servo3.detach();  //GPIO12 = D6
        Servo4.detach();  //GPIO5 = D1
        Servo5.detach();  //GPIO4 = D2
        Servo6.detach();  //GPIO0 = D3
        Servo7.detach();  //GPIO2 = D4
      }
    }

    // if (strcmp((char *)data, "Disarm") == 0) {
    //   servosArmed = false;
    //   notifyClients(servosArmed ? "armed&true" : "armed&false");
    //   client.publish(USER_MQTT_CLIENT_NAME "/status", "Disarming Servos..");
    //   Servo1.detach();  //GPIO16 = D0
    //   Servo2.detach();  //GPIO14 = D5
    //   Servo3.detach();  //GPIO12 = D6
    //   Servo4.detach();  //GPIO5 = D1
    //   Servo5.detach();  //GPIO4 = D2
    //   Servo6.detach();  //GPIO0 = D3
    //   Servo7.detach();  //GPIO2 = D4
    // }

    if (strcmp((char *)data, "animation") == 0) {
      startAnimation = true;
      client.publish(USER_MQTT_CLIENT_NAME "/status", "Starting Animation");
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


void smoothServo(int target_value, float *prev_value, Servo &theServo, float k1, float k2) {
  if (round(*prev_value) != target_value) {
    float smoothed_value = 0;

    smoothed_value = (target_value * k1) + (*prev_value * k2);
    theServo.write(round(smoothed_value));
    *prev_value = smoothed_value;
  }
}

void initServo() {
  Servo1.attach(16, 500, 2400);  //GPIO16 = D0
  Servo2.attach(14, 500, 2400);  //GPIO14 = D5
  Servo3.attach(12, 500, 2400);  //GPIO12 = D6
  Servo4.attach(5, 500, 2400);   //GPIO5 = D1
  Servo5.attach(4, 500, 2400);   //GPIO4 = D2
  Servo6.attach(0, 500, 2400);   //GPIO0 = D3
  Servo7.attach(2, 500, 2400);   //GPIO2 = D4
  Servo1.write(angle_1);
  Servo2.write(angle_2);
  Servo3.write(angle_3);
  Servo4.write(angle_4);
  Servo5.write(angle_5);
  Servo6.write(angle_6);
  Servo7.write(angle_7);
}

void eyeAnimation() {
  if (startAnimation) {
    switch (stepFlag) {
      case 0:
        if (currentMillis - previousStepMillis > 500) {
          angle_1 = 60;
          angle_2 = 105;
          angle_3 = 50;
          angle_4 = 120;
          stepFlag = 1;
          previousStepMillis = currentMillis;
        }
        break;
      case 1:
        if (currentMillis - previousStepMillis > 100) {
          angle_2 = 60;
          angle_4 = 170;
          stepFlag = 2;
          previousStepMillis = currentMillis;
        }
        break;
      case 2:
        if (currentMillis - previousStepMillis > 400) {
          angle_2 = 105;
          angle_4 = 120;
          stepFlag = 3;
          previousStepMillis = currentMillis;
        }
        break;
      case 3:
        if (currentMillis - previousStepMillis > 500) {
          angle_1 = 150;
          angle_3 = 140;
          stepFlag = 0;
          previousStepMillis = currentMillis;
          startAnimation = false;
        }
        break;
    }
  }
}




void reconnect() {
  // Loop until we're reconnected
  int retries = 0;
  // Loop until we're reconnected
  while (!client.connected()) {
    if (retries < 150) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
      if (client.connect(clientID_Name, mqtt_username, mqtt_password, willTopic, 2, true, "Offline")) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish(willTopic, "Online");
        // ... and resubscribe
        client.subscribe(USER_MQTT_CLIENT_NAME "/Movement");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo1/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo2/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo3/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo4/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo5/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo6/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo7/Pos");
        client.subscribe(USER_MQTT_CLIENT_NAME "/IP");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Reset");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Disarm");
        client.subscribe(USER_MQTT_CLIENT_NAME "/Arm");


      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        retries++;
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
    if (retries > 1500) {
      ESP.restart();
    }
  }
}


//++++++++++++++++++++++++++Callback++++++++++++++++++++++++++
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  String newTopic = topic;
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';

  /* Converting String Variable into a Interger Variable
      as a subscribtion 16bit Variable*/
  String newPayload = String((char *)payload);
  int intPayload = newPayload.toInt();
  Serial.println(newPayload);
  Serial.println();
  newPayload.toCharArray(charPayload, newPayload.length() + 1);


  //++++++++++++++++++  ++++Incoming Statements++++++++++++++++++++++
  if (newTopic == USER_MQTT_CLIENT_NAME "/Movement") {
    if (newPayload == "Start") {
      startAnimation = true;
      client.publish(USER_MQTT_CLIENT_NAME "/status", "Starting Animation");
    }
    if (newPayload == "OFF") {
      // Servo1.write(106);
      client.publish(USER_MQTT_CLIENT_NAME "/status", "OFF");
    }
  }

  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo1/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue1 = newPayload;
    notifyClients(getSliderValues());
    angle_1 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo2/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue2 = newPayload;
    notifyClients(getSliderValues());
    angle_2 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo3/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue3 = newPayload;
    notifyClients(getSliderValues());
    angle_3 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo4/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue4 = newPayload;
    notifyClients(getSliderValues());
    angle_4 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo5/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue5 = newPayload;
    notifyClients(getSliderValues());
    angle_5 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo6/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue6 = newPayload;
    notifyClients(getSliderValues());
    angle_6 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo7/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue7 = newPayload;
    notifyClients(getSliderValues());
    angle_7 = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/IP") {
    client.publish(USER_MQTT_CLIENT_NAME "/IP/status", WiFi.localIP().toString().c_str());  //https://github.com/knolleary/pubsubclient/issues/248
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Reset") {
    client.publish(USER_MQTT_CLIENT_NAME "/status", "Restarting..");
    ESP.restart();
  }

  if (newTopic == USER_MQTT_CLIENT_NAME "/Arm") {
    if (newPayload == "true"){
    servosArmed = true;
    notifyClients(servosArmed ? "armed&true" : "armed&false");
    client.publish(USER_MQTT_CLIENT_NAME "/status", "Arming Servos..");
    initServo();
    }
    else if (newPayload == "false"){
          servosArmed = false;
    notifyClients(servosArmed ? "armed&true" : "armed&false");
    client.publish(USER_MQTT_CLIENT_NAME "/status", "Disarming Servos..");
    Servo1.detach();  //GPIO16 = D0
    Servo2.detach();  //GPIO14 = D5
    Servo3.detach();  //GPIO12 = D6
    Servo4.detach();  //GPIO5 = D1
    Servo5.detach();  //GPIO4 = D2
    Servo6.detach();  //GPIO0 = D3
    Servo7.detach();  //GPIO2 = D4
    }
  }
}
