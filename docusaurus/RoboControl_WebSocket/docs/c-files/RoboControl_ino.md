# RoboControl.ino

### imports

```c title="imports" showLineNumbers
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>
#include <AsyncElegantOTA.h>
#include <PubSubClient.h>
#include <Servo.h>

#include "filesystem.h"
#include "html.h"
#include "settings_html.h"
#include "css.h"
#include "script.h"
#include "secrets.h"
```

### variables

```c title="variables" showLineNumbers
// Replace with your network credentials
const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;
const char *mqtt_server = MQTT_SERVER;
const char *mqtt_username = MQTT_USERNAME;
const char *mqtt_password = MQTT_PASSWORD;

#define clientID_Name "Robo"
#define USER_MQTT_CLIENT_NAME "Robo"
#define SERVO_CONFIG_FILE "/servo_settings.json"


char charPayload[50];
const char *willTopic = USER_MQTT_CLIENT_NAME "/LWT";


AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

WiFiClient espClient;
PubSubClient client(espClient);


const uint8_t numServos = 7;
Servo servos[numServos];
const int servoPins[numServos] = { 16, 14, 12, 5, 4, 0, 2 };  //{D0, D5, D6, D1, D2, D3, D4}
uint8_t servoAngles[numServos] = { 120, 105, 80, 120, 90, 80, 10 };
float prevAngles[numServos] = { 120.0, 105.0, 80.0, 120.0, 90.0, 10.0 };


float Servo_K1[numServos] = { 0.10, 0.15, 0.15, 0.15, 0.05, 0.05, 0.05 };
float Servo_K2[numServos] = { 0.90, 0.85, 0.85, 0.85, 0.95, 0.95, 0.95 };

String message = "";
String sliderValue1 = "120";
String sliderValue2 = "105";
String sliderValue3 = "80";
String sliderValue4 = "120";
String sliderValue5 = "90";
String sliderValue6 = "80";
String sliderValue7 = "10";


unsigned long currentMillis;
long previousMillis = 0;  // set up timers
int stepFlag = 0;
long previousStepMillis = 0;
uint8_t animationNumber = 0;
bool servosArmed = true;
```

### functions

```c title="functions" showLineNumbers
String getSliderValues();
void initWiFi();
void notifyClients(String sliderValues);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void initWebSocket();
void smoothServo(int target_value, float *prev_value, Servo &theServo, float k1, float k2);
void initServos();
void animations();
void eyeAnimation();
void headAnimation();
void confuseAnimation();
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
void restartESP();
void detachServos();
void loadServoParam();
```

```c title="void setup" showLineNumbers
void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  loadServoParam();
  initServos();
  initWiFi();

  initWebSocket();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
  });

  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", settings_html);
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/css", styles_css);
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/javascript", script_js);
  });

  server.on("/json", HTTP_GET, [](AsyncWebServerRequest *request) {
    const char *PARAM_INPUT = "value";
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      writeFile(LittleFS, SERVO_CONFIG_FILE, inputMessage.c_str(), "w");
      loadServoParam();
    } else {
      inputMessage = "No message sent";
    }
    Serial.print("Message Param: ");
    Serial.println(inputMessage);
    request->send(LittleFS, SERVO_CONFIG_FILE, "text/plain");
  });


  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


  ArduinoOTA.setHostname("Robo_Control");
  ArduinoOTA.begin();

  AsyncElegantOTA.begin(&server);  // Start AsyncElegantOTA

  // Start server
  server.begin();
}
```

```c title="void loop" showLineNumbers
void loop() {

  currentMillis = millis();

  if (currentMillis - previousMillis > 5) {
    previousMillis = currentMillis;

    for (int i = 0; i < numServos; i++) {
      smoothServo(servoAngles[i], &prevAngles[i], servos[i], Servo_K1[i], Servo_K2[i]);
    }

    animations();
  }



  if (round(prevAngles[0]) != servoAngles[0]) {
    Serial.print(servoAngles[0]);
    Serial.print("\t");
    Serial.print(prevAngles[0]);
    Serial.print("\t");
    Serial.println(round(prevAngles[0]));
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ArduinoOTA.handle();

  ws.cleanupClients();
}
```

### String getSliderValues

```c title="String getSliderValues" showLineNumbers
//Get Slider Values
String getSliderValues() {

  StaticJsonDocument<512> doc;
  JsonObject sliderValues = doc.createNestedObject("sliderValues");
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);
  sliderValues["sliderValue4"] = String(sliderValue4);
  sliderValues["sliderValue5"] = String(sliderValue5);
  sliderValues["sliderValue6"] = String(sliderValue6);
  sliderValues["sliderValue7"] = String(sliderValue7);

  char Nachricht[512];
  serializeJson(doc, Nachricht, sizeof(Nachricht));
  return Nachricht;
}
```

### void initWiFi

```c title="void initWiFi" showLineNumbers
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
```

### void notifyClients

```c title="void notifyClients" showLineNumbers
void notifyClients(String values) {
  ws.textAll(values);
}
```

### void handleWebSocketMessage

```c title="void handleWebSocketMessage" showLineNumbers
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char *)data;
    Serial.println(message);
    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      servoAngles[0] = sliderValue1.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      servoAngles[1] = sliderValue2.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      servoAngles[2] = sliderValue3.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      servoAngles[3] = sliderValue4.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("5s") >= 0) {
      sliderValue5 = message.substring(2);
      servoAngles[4] = sliderValue5.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("6s") >= 0) {
      sliderValue6 = message.substring(2);
      servoAngles[5] = sliderValue6.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("7s") >= 0) {
      sliderValue7 = message.substring(2);
      servoAngles[6] = sliderValue7.toInt();
      Serial.println(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (strcmp((char *)data, "getValues") == 0) {
      notifyClients(getSliderValues());
      loadServoParam();
      notifyClients(servosArmed ? "armed&true" : "armed&false");
    }

    if (strcmp((char *)data, "reset") == 0) {
      restartESP();
    }

    if (message.indexOf("armed&") >= 0) {
      if (message.substring(6) == "true") {
        initServos();
      } else {
        detachServos();
      }
    }

    if (message.indexOf("animation&") >= 0) {
      animationNumber = message.substring(10).toInt();
      Serial.print("animationNumber: ");
      Serial.println(animationNumber);
    }

    // if (strcmp((char *)data, "animation") == 0) {
    //   animationNumber = 1;
    //   client.publish(USER_MQTT_CLIENT_NAME "/status", "Starting Animation");
    // }
  }
}
```

### void onEvent

```c title="void onEvent" showLineNumbers
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
```

### void initWebSocket

```c title="void initWebSocket" showLineNumbers
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}
```

### void smoothServo

```c title="void smoothServo" showLineNumbers
void smoothServo(int target_value, float *prev_value, Servo &theServo, float k1, float k2) {
  if (round(*prev_value) != target_value) {
    float smoothed_value = 0;

    smoothed_value = (target_value * k1) + (*prev_value * k2);
    theServo.write(round(smoothed_value));
    *prev_value = smoothed_value;
  }
}
```

### void initServos

```c title="void initServos" showLineNumbers
void initServos() {
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i], 500, 2400);
    servos[i].write(servoAngles[i]);
  }
  servosArmed = true;
  notifyClients(servosArmed ? "armed&true" : "armed&true");
  client.publish(USER_MQTT_CLIENT_NAME "/status", "Arming Servos..");
}
```

### void animations

```c title="void animations" showLineNumbers
void animations() {
  switch (animationNumber) {
    case 0:
      break;
    case 1:
      eyeAnimation();
      break;
    case 2:
      headAnimation();
      break;
    case 3:
      confuseAnimation();
      break;
  }
}
```

### void eyeAnimation

```c title="void eyeAnimation" showLineNumbers
void eyeAnimation() {
  switch (stepFlag) {
    case 0:
      if (currentMillis - previousStepMillis > 500) {
        servoAngles[0] = 60;
        servoAngles[1] = 105;
        servoAngles[2] = 50;
        servoAngles[3] = 120;
        stepFlag = 1;
        previousStepMillis = currentMillis;
      }
      break;
    case 1:
      if (currentMillis - previousStepMillis > 100) {
        servoAngles[1] = 60;
        servoAngles[3] = 170;
        stepFlag = 2;
        previousStepMillis = currentMillis;
      }
      break;
    case 2:
      if (currentMillis - previousStepMillis > 400) {
        servoAngles[1] = 105;
        servoAngles[3] = 120;
        stepFlag = 3;
        previousStepMillis = currentMillis;
      }
      break;
    case 3:
      if (currentMillis - previousStepMillis > 500) {
        servoAngles[0] = 150;
        servoAngles[2] = 140;
        stepFlag = 0;
        previousStepMillis = currentMillis;
        animationNumber = 0;
      }
      break;
  }
}
```

### void headAnimation

```c title="void headAnimation" showLineNumbers
void headAnimation() {
  switch (stepFlag) {
    case 0:
      if (currentMillis - previousStepMillis > 1000) {
        servoAngles[4] = 90;
        servoAngles[5] = 80;
        servoAngles[6] = 90;
        stepFlag = 1;
        previousStepMillis = currentMillis;
      }
      break;
    case 1:
      if (currentMillis - previousStepMillis > 1000) {
        servoAngles[4] = 100;
        servoAngles[5] = 15;
        servoAngles[6] = 30;
        stepFlag = 2;
        previousStepMillis = currentMillis;
      }
      break;
    case 2:
      if (currentMillis - previousStepMillis > 1000) {
        servoAngles[4] = 140;
        servoAngles[5] = 70;
        servoAngles[6] = 180;
        stepFlag = 3;
        previousStepMillis = currentMillis;
      }
      break;
    case 3:
      if (currentMillis - previousStepMillis > 1000) {
        servoAngles[4] = 90;
        servoAngles[5] = 80;
        servoAngles[6] = 90;
        stepFlag = 0;
        previousStepMillis = currentMillis;
        animationNumber = 0;
      }
      break;
  }
}
```

### void confuseAnimation

```c title="void confuseAnimation" showLineNumbers
void confuseAnimation() {
  switch (stepFlag) {
    case 0:
      if (currentMillis - previousStepMillis > 200) {
        servoAngles[4] = 90;
        servoAngles[5] = 80;
        servoAngles[6] = 90;
        stepFlag = 1;
        previousStepMillis = currentMillis;
      }
      break;
    case 1:
      if (currentMillis - previousStepMillis > 1000) {
        servoAngles[0] = 60;
        servoAngles[1] = 80;
        servoAngles[2] = 140;
        servoAngles[3] = 140;
        servoAngles[4] = 150;
        servoAngles[5] = 10;
        stepFlag = 2;
        previousStepMillis = currentMillis;
      }
      break;
    case 2:
      if (currentMillis - previousStepMillis > 2000) {
        servoAngles[0] = 150;
        servoAngles[1] = 105;
        servoAngles[2] = 50;
        servoAngles[3] = 120;
        servoAngles[4] = 20;
        servoAngles[5] = 160;
        stepFlag = 3;
        previousStepMillis = currentMillis;
      }
      break;
    case 3:
      if (currentMillis - previousStepMillis > 1000) {
        servoAngles[4] = 80;
        servoAngles[5] = 80;
        servoAngles[6] = 70;
        stepFlag = 0;
        previousStepMillis = currentMillis;
        animationNumber = 0;
      }
      break;
  }
}
```

### void reconnect

```c title="void reconnect" showLineNumbers
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
```

### void callback

```c title="void callback" showLineNumbers
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
      animationNumber = 1;
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
    servoAngles[0] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo2/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue2 = newPayload;
    notifyClients(getSliderValues());
    servoAngles[1] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo3/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue3 = newPayload;
    notifyClients(getSliderValues());
    servoAngles[2] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo4/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue4 = newPayload;
    notifyClients(getSliderValues());
    servoAngles[3] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo5/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue5 = newPayload;
    notifyClients(getSliderValues());
    servoAngles[4] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo6/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue6 = newPayload;
    notifyClients(getSliderValues());
    servoAngles[5] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo7/Pos") {
    const char *cPos = charPayload;
    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);
    sliderValue7 = newPayload;
    notifyClients(getSliderValues());
    servoAngles[6] = intPayload;
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/IP") {
    client.publish(USER_MQTT_CLIENT_NAME "/IP/status", WiFi.localIP().toString().c_str());  //https://github.com/knolleary/pubsubclient/issues/248
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/Reset") {
    restartESP();
  }

  if (newTopic == USER_MQTT_CLIENT_NAME "/Arm") {
    if (newPayload == "true") {
      initServos();
    } else if (newPayload == "false") {
      detachServos();
    }
  }
}
```

### void detachServos

```c title="void detachServos" showLineNumbers
void detachServos() {
  for (int i = 0; i < numServos; i++) {
    servos[i].detach();
  }
  servosArmed = false;
  notifyClients(servosArmed ? "armed&true" : "armed&false");
  client.publish(USER_MQTT_CLIENT_NAME "/status", "Disarming Servos..");
}
```

### void restartESP

```c title="restartESP" showLineNumbers
void restartESP() {
  Serial.println("Restarting ESP");
  client.publish(USER_MQTT_CLIENT_NAME "/status", "Restarting..");
  ESP.restart();
}
```

### void loadServoParam

```c title="void loadServoParam" showLineNumbers
void loadServoParam() {
  if (loadFile(LittleFS, SERVO_CONFIG_FILE)) {
    uint8_t i = 0;
    for (JsonPair servoParameter_item : config["servoParameter"].as<JsonObject>()) {
      const char *servoParameter_item_key = servoParameter_item.key().c_str();  // "Servo1", "Servo2", ...

      Servo_K1[i] = servoParameter_item.value()["K1"];  // 0.95, 0.95, 0.95, 0.95, 0.95, 0.95, 0.95
      Servo_K2[i] = servoParameter_item.value()["K2"];  // 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05
      i += 1;
    }
    char Nachricht[512];
    serializeJson(config, Nachricht, sizeof(Nachricht));
    notifyClients(Nachricht);
  }
}
```
