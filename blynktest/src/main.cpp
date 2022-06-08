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
#include <Adafruit_NeoPixel.h>

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
const int servoPin1 = 22;//サーボ
const int servoPin2 = 23;//サーボ
const int MT_F = 12;//DCモータ
const int MT_R = 14;//DCモータ
int speed=0;
bool isLight=false;
#define C5 523.251
#define BUZZER_PIN 32
#define NEO1_PIN 18
#define NUMPIXELS 8
Adafruit_NeoPixel pixels1(NUMPIXELS, NEO1_PIN, NEO_GRB + NEO_KHZ800);
#define NEO2_PIN 19
#define NUMPIXELS 8
Adafruit_NeoPixel pixels2(NUMPIXELS, NEO2_PIN, NEO_GRB + NEO_KHZ800);



// This function is called every time the Virtual Pin 1 state changes
BLYNK_WRITE(V0) ///LightPin:Relay_operates_on_LOW_Input_Voltage_coneccted_NC
{
  int buttonState = param.asInt();
  // Update state
  if(buttonState == HIGH){
          myservo1.attach(22);
        myservo2.attach(23);
        // myservo1.write(90); // 初期化
        // myservo2.write(90); // 初期化
        myservo1.write(120); // 左翼を上に
        myservo2.write(120); //右翼を下に
        delay(500);
        myservo1.write(90); // ホームポジション
        myservo2.write(90); // ホームポジション
        // delay(500);
        // myservo1.detach();
        // myservo2.detach();
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
        // myservo1.write(90); // 初期化
        // myservo2.write(90); // 初期化
        myservo1.write(60); // 左翼を下に
        myservo2.write(60); //右翼を上に
        delay(500);
        myservo1.write(90); // ホームポジション
        myservo2.write(90); // ホームポジション
        // delay(500);
        // myservo1.detach();
        // myservo2.detach();
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
    // myservo1.write(90); // 初期化
    // myservo2.write(90); // 初期化
    myservo1.write(120); // 左翼を上に
    myservo2.write(60); //右翼を上に
    delay(500);
    myservo1.write(90); // ホームポジション
    myservo2.write(90); // ホームポジション
    // delay(500);
    // myservo1.detach();
    // myservo2.detach();
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

BLYNK_WRITE (V5)
{
  int buttonState = param.asInt();
  if(buttonState == HIGH){
    pixels1.clear(); //NeoPixelの出力をリセット
    pixels2.clear();
    for(int i=0; i<NUMPIXELS; i++) { //LEDを１つずつ制御
      pixels1.setPixelColor(i, pixels1.Color(60-8*i, i*10, i*8)); //LEDの色を設定
      pixels1.show();   //LEDに色を反映
      pixels2.setPixelColor(i, pixels2.Color(60-8*i, i*10, i*8));
      pixels2.show();
      delay(125); //125ms待機
      Serial.println("HIGH");
    }
    delay(500);
    pixels1.clear(); //NeoPixelの出力をリセット
    pixels2.clear();
  }else{
    digitalWrite(ledPin, LOW);
    Serial.println("LOW");
    
  }
}
int i;
BLYNK_WRITE (V6)
{
  int buttonState = param.asInt();
  if(buttonState == HIGH){
    for(i=0;i<8;i++){
      tone(BUZZER_PIN,C5,250);

      }
    Serial.println("HIGH");
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
  pixels1.begin();
  pixels2.begin();

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
  Serial.println(speed);
  for(int i=0; i<NUMPIXELS; i++) { //LEDを１つずつ制御
      pixels1.setPixelColor(i, pixels1.Color(0,0,0)); //LEDの色を設定
      pixels1.show();   //LEDに色を反映
      pixels2.setPixelColor(i, pixels2.Color(0,0,0));
      pixels2.show();
  }
  // isLight?
  // digitalWrite(33,HIGH):
  // digitalWrite(33,LOW);
}