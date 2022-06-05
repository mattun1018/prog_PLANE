#include <Arduino.h>
#define BLYNK_TEMPLATE_ID "TMPL6dzVw4ZN"
#define BLYNK_DEVICE_NAME "progPLANEv2"
#define BLYNK_AUTH_TOKEN "oWgw6UQ5WpPj2mZ6c0KG4BXUPtawLEBh"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <math.h>
#include <ESP32Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "隼典のiPhone";
char pass[] = "matsumoto";

BlynkTimer timer;
Servo myservo1;
Servo myservo2;
// the number of the LED pin
const int ledPin = 5;
//サーボ
const int servoPin1 = 22;
const int servoPin2 = 23;
const int MT_F = 12;
const int MT_R = 14;
int speed=0;


// This function is called every time the Virtual Pin 1 state changes
BLYNK_WRITE(V0) ///LightPin:Relay_operates_on_LOW_Input_Voltage_coneccted_NC
{
  int buttonState = param.asInt();
  // Update state
  if(buttonState == HIGH){
          myservo1.attach(22);
        myservo2.attach(23);
        myservo1.write(90); // 初期化
        myservo2.write(90); // 初期化
        myservo1.write(120); // 左翼を上に
        myservo2.write(120); //右翼を下に
        delay(500);
        myservo1.write(90); // ホームポジション
        myservo2.write(90); // ホームポジション
        delay(500);
        myservo1.detach();
        myservo2.detach();
  }else{
     digitalWrite(ledPin, LOW);
     Serial.println("LOW");
  }
}

BLYNK_WRITE(V1) ///LightPin:Relay_operates_on_LOW_Input_Voltage_coneccted_NC
{
  int buttonState = param.asInt();
  // Update state
  if(buttonState == HIGH){
       myservo1.attach(22);
        myservo2.attach(23);
        myservo1.write(90); // 初期化
        myservo2.write(90); // 初期化
        myservo1.write(60); // 左翼を下に
        myservo2.write(60); //右翼を上に
        delay(500);
        myservo1.write(90); // ホームポジション
        myservo2.write(90); // ホームポジション
        delay(500);
        myservo1.detach();
        myservo2.detach();
     Serial.println("HIGH");
  }else{
     digitalWrite(ledPin, LOW);
     Serial.println("LOW");
  }
}

BLYNK_WRITE(V2) ///LightPin:Relay_operates_on_LOW_Input_Voltage_coneccted_NC
{
  int buttonState = param.asInt();
  // Update state
  if(buttonState == HIGH){
    myservo1.attach(22);
    myservo2.attach(23);
    myservo1.write(90); // 初期化
    myservo2.write(90); // 初期化
    myservo1.write(120); // 左翼を上に
    myservo2.write(60); //右翼を上に
    delay(500);
    myservo1.write(90); // ホームポジション
    myservo2.write(90); // ホームポジション
    delay(500);
    myservo1.detach();
    myservo2.detach();
     Serial.println("HIGH");
  }else{
     digitalWrite(ledPin, LOW);
     Serial.println("LOW");
  }
}

BLYNK_WRITE(V3) ///LightPin:Relay_operates_on_LOW_Input_Voltage_coneccted_NC
{
  int buttonState = param.asInt();
  // Update state
  if(buttonState == HIGH){
    speed=speed+25;
     Serial.println("HIGH");
     if(speed>255){
       speed=255;
     }
  }else{
     digitalWrite(ledPin, LOW);
     Serial.println("LOW");
  }
}

BLYNK_WRITE(V4) ///LightPin:Relay_operates_on_LOW_Input_Voltage_coneccted_NC
{
  int buttonState = param.asInt();
  if(buttonState == HIGH){
    speed=speed-25;
     Serial.println("HIGH");
     if(speed<0){
       speed=0;
     }
  }else{
     digitalWrite(ledPin, LOW);
     Serial.println("LOW");
  }
}



// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Serial.println("Connected!");
}
//////////////////////////////////////////////////////////////////////

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  //pinMode setting
  pinMode(ledPin , OUTPUT);

  //WiFI Setting
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(10,0,1,28), 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(10,0,1,28));

  // Setup a function to be called every second
  //  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  analogWrite( MT_F, speed );
  analogWrite( MT_R, 0 );
}