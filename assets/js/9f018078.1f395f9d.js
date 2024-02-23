"use strict";(self.webpackChunkrobo_control_web_socket=self.webpackChunkrobo_control_web_socket||[]).push([[890],{8936:(e,n,r)=>{r.r(n),r.d(n,{assets:()=>a,contentTitle:()=>l,default:()=>u,frontMatter:()=>t,metadata:()=>o,toc:()=>c});var i=r(4848),s=r(8453);const t={sidebar_position:1},l="RoboControl.ino",o={id:"c-files/RoboControl_ino",title:"RoboControl.ino",description:"imports",source:"@site/docs/c-files/RoboControl_ino.md",sourceDirName:"c-files",slug:"/c-files/RoboControl_ino",permalink:"/RoboControl_WebSocket/docs/c-files/RoboControl_ino",draft:!1,unlisted:!1,editUrl:"https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/docs/c-files/RoboControl_ino.md",tags:[],version:"current",sidebarPosition:1,frontMatter:{sidebar_position:1},sidebar:"tutorialSidebar",previous:{title:"C Files",permalink:"/RoboControl_WebSocket/docs/category/c-files"},next:{title:"filesystem.h",permalink:"/RoboControl_WebSocket/docs/c-files/filesystem_h"}},a={},c=[{value:"imports",id:"imports",level:3},{value:"variables",id:"variables",level:3},{value:"functions",id:"functions",level:3},{value:"String getSliderValues",id:"string-getslidervalues",level:3},{value:"void initWiFi",id:"void-initwifi",level:3},{value:"void notifyClients",id:"void-notifyclients",level:3},{value:"void handleWebSocketMessage",id:"void-handlewebsocketmessage",level:3},{value:"void onEvent",id:"void-onevent",level:3},{value:"void initWebSocket",id:"void-initwebsocket",level:3},{value:"void smoothServo",id:"void-smoothservo",level:3},{value:"void initServos",id:"void-initservos",level:3},{value:"void animations",id:"void-animations",level:3},{value:"void eyeAnimation",id:"void-eyeanimation",level:3},{value:"void headAnimation",id:"void-headanimation",level:3},{value:"void confuseAnimation",id:"void-confuseanimation",level:3},{value:"void reconnect",id:"void-reconnect",level:3},{value:"void callback",id:"void-callback",level:3},{value:"void detachServos",id:"void-detachservos",level:3},{value:"void restartESP",id:"void-restartesp",level:3},{value:"void loadServoParam",id:"void-loadservoparam",level:3}];function d(e){const n={code:"code",h1:"h1",h3:"h3",pre:"pre",...(0,s.R)(),...e.components};return(0,i.jsxs)(i.Fragment,{children:[(0,i.jsx)(n.h1,{id:"robocontrolino",children:"RoboControl.ino"}),"\n",(0,i.jsx)(n.h3,{id:"imports",children:"imports"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="imports" showLineNumbers',children:'#include <ArduinoJson.h>\r\n#include <Arduino.h>\r\n#include <ESP8266WiFi.h>\r\n#include <ESPAsyncTCP.h>\r\n#include <ESPAsyncWebServer.h>\r\n#include <ArduinoOTA.h>\r\n#include <AsyncElegantOTA.h>\r\n#include <PubSubClient.h>\r\n#include <Servo.h>\r\n\r\n#include "filesystem.h"\r\n#include "html.h"\r\n#include "settings_html.h"\r\n#include "css.h"\r\n#include "script.h"\r\n#include "secrets.h"\n'})}),"\n",(0,i.jsx)(n.h3,{id:"variables",children:"variables"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="variables" showLineNumbers',children:'// Replace with your network credentials\r\nconst char *ssid = SECRET_SSID;\r\nconst char *password = SECRET_PASS;\r\nconst char *mqtt_server = MQTT_SERVER;\r\nconst char *mqtt_username = MQTT_USERNAME;\r\nconst char *mqtt_password = MQTT_PASSWORD;\r\n\r\n#define clientID_Name "Robo"\r\n#define USER_MQTT_CLIENT_NAME "Robo"\r\n#define SERVO_CONFIG_FILE "/servo_settings.json"\r\n\r\n\r\nchar charPayload[50];\r\nconst char *willTopic = USER_MQTT_CLIENT_NAME "/LWT";\r\n\r\n\r\nAsyncWebServer server(80);\r\nAsyncWebSocket ws("/ws");\r\n\r\nWiFiClient espClient;\r\nPubSubClient client(espClient);\r\n\r\n\r\nconst uint8_t numServos = 7;\r\nServo servos[numServos];\r\nconst int servoPins[numServos] = { 16, 14, 12, 5, 4, 0, 2 };  //{D0, D5, D6, D1, D2, D3, D4}\r\nuint8_t servoAngles[numServos] = { 120, 105, 80, 120, 90, 80, 10 };\r\nfloat prevAngles[numServos] = { 120.0, 105.0, 80.0, 120.0, 90.0, 10.0 };\r\n\r\n\r\nfloat Servo_K1[numServos] = { 0.10, 0.15, 0.15, 0.15, 0.05, 0.05, 0.05 };\r\nfloat Servo_K2[numServos] = { 0.90, 0.85, 0.85, 0.85, 0.95, 0.95, 0.95 };\r\n\r\nString message = "";\r\nString sliderValue1 = "120";\r\nString sliderValue2 = "105";\r\nString sliderValue3 = "80";\r\nString sliderValue4 = "120";\r\nString sliderValue5 = "90";\r\nString sliderValue6 = "80";\r\nString sliderValue7 = "10";\r\n\r\n\r\nunsigned long currentMillis;\r\nlong previousMillis = 0;  // set up timers\r\nint stepFlag = 0;\r\nlong previousStepMillis = 0;\r\nuint8_t animationNumber = 0;\r\nbool servosArmed = true;\n'})}),"\n",(0,i.jsx)(n.h3,{id:"functions",children:"functions"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="functions" showLineNumbers',children:"String getSliderValues();\r\nvoid initWiFi();\r\nvoid notifyClients(String sliderValues);\r\nvoid handleWebSocketMessage(void *arg, uint8_t *data, size_t len);\r\nvoid onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);\r\nvoid initWebSocket();\r\nvoid smoothServo(int target_value, float *prev_value, Servo &theServo, float k1, float k2);\r\nvoid initServos();\r\nvoid animations();\r\nvoid eyeAnimation();\r\nvoid headAnimation();\r\nvoid confuseAnimation();\r\nvoid callback(char *topic, byte *payload, unsigned int length);\r\nvoid reconnect();\r\nvoid restartESP();\r\nvoid detachServos();\r\nvoid loadServoParam();\n"})}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void setup" showLineNumbers',children:'void setup() {\r\n  Serial.begin(115200);\r\n  LittleFS.begin();\r\n  loadServoParam();\r\n  initServos();\r\n  initWiFi();\r\n\r\n  initWebSocket();\r\n\r\n  // Web Server Root URL\r\n  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {\r\n    request->send(200, "text/html", index_html);\r\n  });\r\n\r\n  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {\r\n    request->send(200, "text/html", settings_html);\r\n  });\r\n\r\n  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {\r\n    request->send(200, "text/css", styles_css);\r\n  });\r\n\r\n  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {\r\n    request->send(200, "text/javascript", script_js);\r\n  });\r\n\r\n  server.on("/json", HTTP_GET, [](AsyncWebServerRequest *request) {\r\n    const char *PARAM_INPUT = "value";\r\n    String inputMessage;\r\n    if (request->hasParam(PARAM_INPUT)) {\r\n      inputMessage = request->getParam(PARAM_INPUT)->value();\r\n      writeFile(LittleFS, SERVO_CONFIG_FILE, inputMessage.c_str(), "w");\r\n      loadServoParam();\r\n    } else {\r\n      inputMessage = "No message sent";\r\n    }\r\n    Serial.print("Message Param: ");\r\n    Serial.println(inputMessage);\r\n    request->send(LittleFS, SERVO_CONFIG_FILE, "text/plain");\r\n  });\r\n\r\n\r\n  client.setServer(mqtt_server, 1883);\r\n  client.setCallback(callback);\r\n\r\n\r\n  ArduinoOTA.setHostname("Robo_Control");\r\n  ArduinoOTA.begin();\r\n\r\n  AsyncElegantOTA.begin(&server);  // Start AsyncElegantOTA\r\n\r\n  // Start server\r\n  server.begin();\r\n}\n'})}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void loop" showLineNumbers',children:'void loop() {\r\n\r\n  currentMillis = millis();\r\n\r\n  if (currentMillis - previousMillis > 5) {\r\n    previousMillis = currentMillis;\r\n\r\n    for (int i = 0; i < numServos; i++) {\r\n      smoothServo(servoAngles[i], &prevAngles[i], servos[i], Servo_K1[i], Servo_K2[i]);\r\n    }\r\n\r\n    animations();\r\n  }\r\n\r\n\r\n\r\n  if (round(prevAngles[0]) != servoAngles[0]) {\r\n    Serial.print(servoAngles[0]);\r\n    Serial.print("\\t");\r\n    Serial.print(prevAngles[0]);\r\n    Serial.print("\\t");\r\n    Serial.println(round(prevAngles[0]));\r\n  }\r\n\r\n  if (!client.connected()) {\r\n    reconnect();\r\n  }\r\n  client.loop();\r\n  ArduinoOTA.handle();\r\n\r\n  ws.cleanupClients();\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"string-getslidervalues",children:"String getSliderValues"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="String getSliderValues" showLineNumbers',children:'//Get Slider Values\r\nString getSliderValues() {\r\n\r\n  StaticJsonDocument<512> doc;\r\n  JsonObject sliderValues = doc.createNestedObject("sliderValues");\r\n  sliderValues["sliderValue1"] = String(sliderValue1);\r\n  sliderValues["sliderValue2"] = String(sliderValue2);\r\n  sliderValues["sliderValue3"] = String(sliderValue3);\r\n  sliderValues["sliderValue4"] = String(sliderValue4);\r\n  sliderValues["sliderValue5"] = String(sliderValue5);\r\n  sliderValues["sliderValue6"] = String(sliderValue6);\r\n  sliderValues["sliderValue7"] = String(sliderValue7);\r\n\r\n  char Nachricht[512];\r\n  serializeJson(doc, Nachricht, sizeof(Nachricht));\r\n  return Nachricht;\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-initwifi",children:"void initWiFi"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void initWiFi" showLineNumbers',children:'// Initialize WiFi\r\nvoid initWiFi() {\r\n  WiFi.mode(WIFI_STA);\r\n  WiFi.begin(ssid, password);\r\n  Serial.println();\r\n  Serial.print("Connecting to ");\r\n  Serial.println(ssid);\r\n  while (WiFi.status() != WL_CONNECTED) {\r\n    Serial.print(\'.\');\r\n    delay(500);\r\n  }\r\n  Serial.println("");\r\n  Serial.println("WiFi connected");\r\n  Serial.println("IP address: ");\r\n  Serial.println(WiFi.localIP());\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-notifyclients",children:"void notifyClients"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void notifyClients" showLineNumbers',children:"void notifyClients(String values) {\r\n  ws.textAll(values);\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-handlewebsocketmessage",children:"void handleWebSocketMessage"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void handleWebSocketMessage" showLineNumbers',children:'void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {\r\n  AwsFrameInfo *info = (AwsFrameInfo *)arg;\r\n  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {\r\n    data[len] = 0;\r\n    message = (char *)data;\r\n    Serial.println(message);\r\n    if (message.indexOf("1s") >= 0) {\r\n      sliderValue1 = message.substring(2);\r\n      servoAngles[0] = sliderValue1.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (message.indexOf("2s") >= 0) {\r\n      sliderValue2 = message.substring(2);\r\n      servoAngles[1] = sliderValue2.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (message.indexOf("3s") >= 0) {\r\n      sliderValue3 = message.substring(2);\r\n      servoAngles[2] = sliderValue3.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (message.indexOf("4s") >= 0) {\r\n      sliderValue4 = message.substring(2);\r\n      servoAngles[3] = sliderValue4.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (message.indexOf("5s") >= 0) {\r\n      sliderValue5 = message.substring(2);\r\n      servoAngles[4] = sliderValue5.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (message.indexOf("6s") >= 0) {\r\n      sliderValue6 = message.substring(2);\r\n      servoAngles[5] = sliderValue6.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (message.indexOf("7s") >= 0) {\r\n      sliderValue7 = message.substring(2);\r\n      servoAngles[6] = sliderValue7.toInt();\r\n      Serial.println(getSliderValues());\r\n      notifyClients(getSliderValues());\r\n    }\r\n    if (strcmp((char *)data, "getValues") == 0) {\r\n      notifyClients(getSliderValues());\r\n      loadServoParam();\r\n      notifyClients(servosArmed ? "armed&true" : "armed&false");\r\n    }\r\n\r\n    if (strcmp((char *)data, "reset") == 0) {\r\n      restartESP();\r\n    }\r\n\r\n    if (message.indexOf("armed&") >= 0) {\r\n      if (message.substring(6) == "true") {\r\n        initServos();\r\n      } else {\r\n        detachServos();\r\n      }\r\n    }\r\n\r\n    if (message.indexOf("animation&") >= 0) {\r\n      animationNumber = message.substring(10).toInt();\r\n      Serial.print("animationNumber: ");\r\n      Serial.println(animationNumber);\r\n    }\r\n\r\n    // if (strcmp((char *)data, "animation") == 0) {\r\n    //   animationNumber = 1;\r\n    //   client.publish(USER_MQTT_CLIENT_NAME "/status", "Starting Animation");\r\n    // }\r\n  }\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-onevent",children:"void onEvent"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void onEvent" showLineNumbers',children:'void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {\r\n  switch (type) {\r\n    case WS_EVT_CONNECT:\r\n      Serial.printf("WebSocket client #%u connected from %s\\n", client->id(), client->remoteIP().toString().c_str());\r\n      break;\r\n    case WS_EVT_DISCONNECT:\r\n      Serial.printf("WebSocket client #%u disconnected\\n", client->id());\r\n      break;\r\n    case WS_EVT_DATA:\r\n      handleWebSocketMessage(arg, data, len);\r\n      break;\r\n    case WS_EVT_PONG:\r\n    case WS_EVT_ERROR:\r\n      break;\r\n  }\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-initwebsocket",children:"void initWebSocket"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void initWebSocket" showLineNumbers',children:"void initWebSocket() {\r\n  ws.onEvent(onEvent);\r\n  server.addHandler(&ws);\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-smoothservo",children:"void smoothServo"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void smoothServo" showLineNumbers',children:"void smoothServo(int target_value, float *prev_value, Servo &theServo, float k1, float k2) {\r\n  if (round(*prev_value) != target_value) {\r\n    float smoothed_value = 0;\r\n\r\n    smoothed_value = (target_value * k1) + (*prev_value * k2);\r\n    theServo.write(round(smoothed_value));\r\n    *prev_value = smoothed_value;\r\n  }\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-initservos",children:"void initServos"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void initServos" showLineNumbers',children:'void initServos() {\r\n  for (int i = 0; i < numServos; i++) {\r\n    servos[i].attach(servoPins[i], 500, 2400);\r\n    servos[i].write(servoAngles[i]);\r\n  }\r\n  servosArmed = true;\r\n  notifyClients(servosArmed ? "armed&true" : "armed&true");\r\n  client.publish(USER_MQTT_CLIENT_NAME "/status", "Arming Servos..");\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-animations",children:"void animations"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void animations" showLineNumbers',children:"void animations() {\r\n  switch (animationNumber) {\r\n    case 0:\r\n      break;\r\n    case 1:\r\n      eyeAnimation();\r\n      break;\r\n    case 2:\r\n      headAnimation();\r\n      break;\r\n    case 3:\r\n      confuseAnimation();\r\n      break;\r\n  }\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-eyeanimation",children:"void eyeAnimation"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void eyeAnimation" showLineNumbers',children:"void eyeAnimation() {\r\n  switch (stepFlag) {\r\n    case 0:\r\n      if (currentMillis - previousStepMillis > 500) {\r\n        servoAngles[0] = 60;\r\n        servoAngles[1] = 105;\r\n        servoAngles[2] = 50;\r\n        servoAngles[3] = 120;\r\n        stepFlag = 1;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 1:\r\n      if (currentMillis - previousStepMillis > 100) {\r\n        servoAngles[1] = 60;\r\n        servoAngles[3] = 170;\r\n        stepFlag = 2;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 2:\r\n      if (currentMillis - previousStepMillis > 400) {\r\n        servoAngles[1] = 105;\r\n        servoAngles[3] = 120;\r\n        stepFlag = 3;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 3:\r\n      if (currentMillis - previousStepMillis > 500) {\r\n        servoAngles[0] = 150;\r\n        servoAngles[2] = 140;\r\n        stepFlag = 0;\r\n        previousStepMillis = currentMillis;\r\n        animationNumber = 0;\r\n      }\r\n      break;\r\n  }\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-headanimation",children:"void headAnimation"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void headAnimation" showLineNumbers',children:"void headAnimation() {\r\n  switch (stepFlag) {\r\n    case 0:\r\n      if (currentMillis - previousStepMillis > 1000) {\r\n        servoAngles[4] = 90;\r\n        servoAngles[5] = 80;\r\n        servoAngles[6] = 90;\r\n        stepFlag = 1;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 1:\r\n      if (currentMillis - previousStepMillis > 1000) {\r\n        servoAngles[4] = 100;\r\n        servoAngles[5] = 15;\r\n        servoAngles[6] = 30;\r\n        stepFlag = 2;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 2:\r\n      if (currentMillis - previousStepMillis > 1000) {\r\n        servoAngles[4] = 140;\r\n        servoAngles[5] = 70;\r\n        servoAngles[6] = 180;\r\n        stepFlag = 3;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 3:\r\n      if (currentMillis - previousStepMillis > 1000) {\r\n        servoAngles[4] = 90;\r\n        servoAngles[5] = 80;\r\n        servoAngles[6] = 90;\r\n        stepFlag = 0;\r\n        previousStepMillis = currentMillis;\r\n        animationNumber = 0;\r\n      }\r\n      break;\r\n  }\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-confuseanimation",children:"void confuseAnimation"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void confuseAnimation" showLineNumbers',children:"void confuseAnimation() {\r\n  switch (stepFlag) {\r\n    case 0:\r\n      if (currentMillis - previousStepMillis > 200) {\r\n        servoAngles[4] = 90;\r\n        servoAngles[5] = 80;\r\n        servoAngles[6] = 90;\r\n        stepFlag = 1;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 1:\r\n      if (currentMillis - previousStepMillis > 1000) {\r\n        servoAngles[0] = 60;\r\n        servoAngles[1] = 80;\r\n        servoAngles[2] = 140;\r\n        servoAngles[3] = 140;\r\n        servoAngles[4] = 150;\r\n        servoAngles[5] = 10;\r\n        stepFlag = 2;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 2:\r\n      if (currentMillis - previousStepMillis > 2000) {\r\n        servoAngles[0] = 150;\r\n        servoAngles[1] = 105;\r\n        servoAngles[2] = 50;\r\n        servoAngles[3] = 120;\r\n        servoAngles[4] = 20;\r\n        servoAngles[5] = 160;\r\n        stepFlag = 3;\r\n        previousStepMillis = currentMillis;\r\n      }\r\n      break;\r\n    case 3:\r\n      if (currentMillis - previousStepMillis > 1000) {\r\n        servoAngles[4] = 80;\r\n        servoAngles[5] = 80;\r\n        servoAngles[6] = 70;\r\n        stepFlag = 0;\r\n        previousStepMillis = currentMillis;\r\n        animationNumber = 0;\r\n      }\r\n      break;\r\n  }\r\n}\n"})}),"\n",(0,i.jsx)(n.h3,{id:"void-reconnect",children:"void reconnect"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void reconnect" showLineNumbers',children:'void reconnect() {\r\n  // Loop until we\'re reconnected\r\n  int retries = 0;\r\n  // Loop until we\'re reconnected\r\n  while (!client.connected()) {\r\n    if (retries < 150) {\r\n      Serial.print("Attempting MQTT connection...");\r\n      // Create a random client ID\r\n      String clientId = "ESP8266Client-";\r\n      clientId += String(random(0xffff), HEX);\r\n      // Attempt to connect\r\n      if (client.connect(clientID_Name, mqtt_username, mqtt_password, willTopic, 2, true, "Offline")) {\r\n        Serial.println("connected");\r\n        // Once connected, publish an announcement...\r\n        client.publish(willTopic, "Online");\r\n        // ... and resubscribe\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Movement");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo1/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo2/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo3/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo4/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo5/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo6/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Servo7/Pos");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/IP");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Reset");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Disarm");\r\n        client.subscribe(USER_MQTT_CLIENT_NAME "/Arm");\r\n\r\n\r\n      } else {\r\n        Serial.print("failed, rc=");\r\n        Serial.print(client.state());\r\n        Serial.println(" try again in 5 seconds");\r\n        retries++;\r\n        // Wait 5 seconds before retrying\r\n        delay(5000);\r\n      }\r\n    }\r\n    if (retries > 1500) {\r\n      ESP.restart();\r\n    }\r\n  }\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-callback",children:"void callback"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void callback" showLineNumbers',children:'//++++++++++++++++++++++++++Callback++++++++++++++++++++++++++\r\nvoid callback(char *topic, byte *payload, unsigned int length) {\r\n  Serial.print("Message arrived [");\r\n  String newTopic = topic;\r\n  Serial.print(topic);\r\n  Serial.print("] ");\r\n  payload[length] = \'\\0\';\r\n\r\n  /* Converting String Variable into a Interger Variable\r\n      as a subscribtion 16bit Variable*/\r\n  String newPayload = String((char *)payload);\r\n  int intPayload = newPayload.toInt();\r\n  Serial.println(newPayload);\r\n  Serial.println();\r\n  newPayload.toCharArray(charPayload, newPayload.length() + 1);\r\n\r\n\r\n  //++++++++++++++++++  ++++Incoming Statements++++++++++++++++++++++\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Movement") {\r\n    if (newPayload == "Start") {\r\n      animationNumber = 1;\r\n      client.publish(USER_MQTT_CLIENT_NAME "/status", "Starting Animation");\r\n    }\r\n    if (newPayload == "OFF") {\r\n      // Servo1.write(106);\r\n      client.publish(USER_MQTT_CLIENT_NAME "/status", "OFF");\r\n    }\r\n  }\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo1/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue1 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[0] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo2/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue2 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[1] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo3/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue3 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[2] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo4/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue4 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[3] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo5/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue5 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[4] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo6/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue6 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[5] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Servo7/Pos") {\r\n    const char *cPos = charPayload;\r\n    client.publish(USER_MQTT_CLIENT_NAME "/status", cPos);\r\n    sliderValue7 = newPayload;\r\n    notifyClients(getSliderValues());\r\n    servoAngles[6] = intPayload;\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/IP") {\r\n    client.publish(USER_MQTT_CLIENT_NAME "/IP/status", WiFi.localIP().toString().c_str());  //https://github.com/knolleary/pubsubclient/issues/248\r\n  }\r\n\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Reset") {\r\n    restartESP();\r\n  }\r\n\r\n  if (newTopic == USER_MQTT_CLIENT_NAME "/Arm") {\r\n    if (newPayload == "true") {\r\n      initServos();\r\n    } else if (newPayload == "false") {\r\n      detachServos();\r\n    }\r\n  }\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-detachservos",children:"void detachServos"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void detachServos" showLineNumbers',children:'void detachServos() {\r\n  for (int i = 0; i < numServos; i++) {\r\n    servos[i].detach();\r\n  }\r\n  servosArmed = false;\r\n  notifyClients(servosArmed ? "armed&true" : "armed&false");\r\n  client.publish(USER_MQTT_CLIENT_NAME "/status", "Disarming Servos..");\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-restartesp",children:"void restartESP"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="restartESP" showLineNumbers',children:'void restartESP() {\r\n  Serial.println("Restarting ESP");\r\n  client.publish(USER_MQTT_CLIENT_NAME "/status", "Restarting..");\r\n  ESP.restart();\r\n}\n'})}),"\n",(0,i.jsx)(n.h3,{id:"void-loadservoparam",children:"void loadServoParam"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",metastring:'title="void loadServoParam" showLineNumbers',children:'void loadServoParam() {\r\n  if (loadFile(LittleFS, SERVO_CONFIG_FILE)) {\r\n    uint8_t i = 0;\r\n    for (JsonPair servoParameter_item : config["servoParameter"].as<JsonObject>()) {\r\n      const char *servoParameter_item_key = servoParameter_item.key().c_str();  // "Servo1", "Servo2", ...\r\n\r\n      Servo_K1[i] = servoParameter_item.value()["K1"];  // 0.95, 0.95, 0.95, 0.95, 0.95, 0.95, 0.95\r\n      Servo_K2[i] = servoParameter_item.value()["K2"];  // 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05\r\n      i += 1;\r\n    }\r\n    char Nachricht[512];\r\n    serializeJson(config, Nachricht, sizeof(Nachricht));\r\n    notifyClients(Nachricht);\r\n  }\r\n}\n'})})]})}function u(e={}){const{wrapper:n}={...(0,s.R)(),...e.components};return n?(0,i.jsx)(n,{...e,children:(0,i.jsx)(d,{...e})}):d(e)}},8453:(e,n,r)=>{r.d(n,{R:()=>l,x:()=>o});var i=r(6540);const s={},t=i.createContext(s);function l(e){const n=i.useContext(t);return i.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function o(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(s):e.components||s:l(e.components),i.createElement(t.Provider,{value:n},e.children)}}}]);