#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <FirebaseArduino.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>
// WiFi configs
#define WIFI_SSID "HappyHouse"
#define WIFI_PASSWORD "15537011"

// Firebase configs
// Change "example" to the ID of the project
// If you link to the admin panel looking like this
// https://console.firebase.google.com/project/myfirebaseproject-b6c78/overview
// then FIREBASE_HOST will look like this
// "myfirebaseproject-b6c78.firebaseio.com"
#define FIREBASE_HOST "test-iot-project-36036.firebaseio.com"
// Sensor configs
// Change sensor pin number if needed
// Servo
#define SERVO_PIN 4
Servo myServo;
int angle = 0;
int lastAngle = 0;

void setup(){
    // Starting serial port
    Serial.begin(115200);
    // Connect to the WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
    // Connecting to the Firebase
    Firebase.begin(FIREBASE_HOST);
    // Servo
    myServo.attach(SERVO_PIN);
    myServo.write(0);
}

void loop(){
    angle = Firebase.getInt("servo/angle");
    if(Firebase.failed()) {
        Serial.println("Getting data from Firebase failed");
        delay(1000);
    }else if(angle != lastAngle){
        Serial.print("Angle changed: ");
        Serial.println(angle);
        myServo.write(angle);
        lastAngle = angle;
  }
}
