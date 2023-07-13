#include <ArduinoJson.h>
#include "LittleFS.h"


StaticJsonDocument<512> config;


void writeFile(fs::FS &fs, const char *path, const char *message, const char *mode) {
  Serial.printf("\nWriting file: %s\r\n", path);

  File file = fs.open(path, mode);
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

bool loadFile(fs::FS &fs, const char *path)
// Load existing configuration file
{
  String input;

  if (fs.exists(path)) {
    // The file exists, reading and loading
    Serial.printf("\nreading File: %s\n", path);
    File file = fs.open(path, "r");
    if (file) {
      Serial.println("Opening file:");

      while (file.available()) {
        char intRead = file.read();
        input += intRead;
      }

      DeserializationError error = deserializeJson(config, input);
      file.close();

      if (!error) {
        serializeJsonPretty(config, Serial);

        return true;
      } else {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
      }
    } else {
      Serial.println("Failed to open file for reading");
    }
  }
  return false;
}
