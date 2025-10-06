#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <SoftwareSerial.h>
SoftwareSerial ss(D3, D4);
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "AB"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB_fs4NDWAZRxsH0RO_q0kl1-tGHh8Oyhg"


// Insert RTDB URL
#define DATABASE_URL "https://eyemove-691bc-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

// Flags for data types
bool value1Flag = false;
bool value2Flag = false;
bool value3Flag = false;
bool value4Flag = false;
bool value5Flag = false;
bool value6Flag = false;

// Variables to hold sensor data
String value1 = "", value2 = "", value3 = "", value4 = "", value5 = "", value6 = "";

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  ss.begin(9600);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase signup successful");
    signupOK = true;
  } else {
    Serial.printf("Firebase signup error: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  readSerialData();

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    updateFirebaseData();
    if (Firebase.ready() && signupOK) {
      if (Firebase.RTDB.getString(&fbdo, "/predictions/id/direction")) {
        if (fbdo.dataType() == "string") {
          String intValue = fbdo.stringData();
          //ss.print(intValue);
          Serial.println("Firebase data: " + intValue);
          if (intValue == "A") {
            Serial.println("Detected 'A'. Performing action...");
            ss.write('A');
          }
          if (intValue == "F") {
            Serial.println("Detected 'B'. Performing action...");
            ss.write('F');
          }
          if (intValue == "R") {
            Serial.println("Detected 'B'. Performing action...");
            ss.write('R');
          }
          if (intValue == "L") {
            Serial.println("Detected 'B'. Performing action...");
            ss.write('L');
          }
          if (intValue == "B") {
            Serial.println("Detected 'B'. Performing action...");
            ss.write('B');
          }

        }
      } else {
        Serial.printf("Firebase read error: %s\n", fbdo.errorReason().c_str());
      }
    }
  }
  delay(4000); // Delay to prevent overloading Firebase with requests
}

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startTime > 15000) { // Timeout after 15 seconds
      Serial.println("Failed to connect to Wi-Fi.");
      return;
    }
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void readSerialData() {
  while (Serial.available() > 0) { //*Helloo How are you#
    char inchar = Serial.read();
    Serial.println("Inchar:" + String(inchar));
    if (inchar == '*') {
      value1 = readUntil('#');
      value1Flag = true;
    } else if (inchar == '^') {
      value2 = readUntil('#');
      value2Flag = true;
    } else if (inchar == '&') {
      value3 = readUntil('#');
      value3Flag = true;
    } else if (inchar == ')') {
      value4 = readUntil('#');
      value4Flag = true;
    } else if (inchar == '@') {
      value5 = readUntil('#');
      value5Flag = true;
    } else if (inchar == '!') {
      value6 = readUntil('#');
      value6Flag = true;
    }

  }
}

void updateFirebaseData() {
  if (value1Flag) {
    value1Flag = false;
    updateFirebase("Monitoring/temp", value1);
  }

  if (value2Flag) {
    value2Flag = false;
    updateFirebase("Monitoring/G_i", value2);
  }

  if (value3Flag) {
    value3Flag = false;
    updateFirebase("Monitoring/NIR", value3);
  }

  if (value4Flag) {
    value4Flag = false;
    updateFirebase("Monitoring/RESPERATION", value4);
  }

  if (value5Flag) {
    value5Flag = false;
    updateFirebase("Monitoring/gyro", value5);
  }
  if (value6Flag) {
    value6Flag = false;
    updateFirebase("Monitoring/bin2ultra", value6);
  }
}

String readUntil(char terminator) {
  String result = "";
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == terminator) {
      break;
    }
    result += c;
  }
  return result;
}

void updateFirebase(String path, String value) {
  if (Firebase.RTDB.setString(&fbdo, path, value)) {
    Serial.println("PASSED: " + path);
    Serial.println("Value: " + value);
  } else {
    Serial.println("FAILED to update " + path);
    Serial.println("Reason: " + fbdo.errorReason());
  }
}
