#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#define LED_PIN 15

Servo myservo1;
Servo myservo2;  
const char *ssid = "plane_control_A";        //  *** 書き換え必要 ***
const char *password = "oit1105noplane"; //  *** 書き換え必要（8文字以上）***
const int MT_F = 02;
const int MT_R = 04;


const IPAddress ip(192, 168, 123, 46);
const IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80); // ポート設定

void left_Servo()
{
  myservo1.attach(13);
  myservo2.attach(12);
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

}

void right_Servo()
{
  myservo1.attach(13);
  myservo2.attach(12);
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
}

void up_Servo()
{
  myservo1.attach(13);
  myservo2.attach(12);
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
}

void accel_DC()
{
  int speed;
    
    analogWrite( MT_F, 0 );
    analogWrite( MT_R, 0 );
    
    speed = 0;
    while( speed <= 255 ){
        analogWrite( MT_F, speed );
        delay( 50 );
        speed = speed + 5;
    }
    while(speed==255){
      
    }

    
}

void break_DC()
{
  analogWrite( MT_F, 128 );
  analogWrite( MT_R, 0 );

    delay( 1000 );
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  myservo1.attach(13);
  myservo2.attach(12, 500, 2400);
  pinMode( MT_F, OUTPUT );
  pinMode( MT_R, OUTPUT );
  // SPIFFSのセットアップ
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAP(ssid, password);       // SSIDとパスの設定
  delay(100);                        // このdelayを入れないと失敗する場合がある
  WiFi.softAPConfig(ip, ip, subnet); // IPアドレス、ゲートウェイ、サブネットマスクの設定

  IPAddress myIP = WiFi.softAPIP(); // WiFi.softAPIP()でWiFi起動

  // 各種情報を表示
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // GETリクエストに対するハンドラーを登録
  // rootにアクセスされた時のレスポンス
  server.on(
      "/", HTTP_GET,
      [](AsyncWebServerRequest *request)
      {
        request->send(SPIFFS, "/index.html");
        myservo1.attach(13);
        myservo2.attach(12);
        myservo1.write(90);
        myservo2.write(90);

        delay(100);
        myservo1.detach();
        myservo2.detach();
      });
  server.on(
      "/right", HTTP_GET,
      [](AsyncWebServerRequest *request)
      {
        request->send(SPIFFS, "/index.html");
        digitalWrite(LED_PIN, HIGH);
        Serial.println("on");
        right_Servo();
      });
  // offにアクセスされた時のレスポンス
  server.on(
      "/left", HTTP_GET,
      [](AsyncWebServerRequest *request)
      {
        request->send(SPIFFS, "/index.html");
        digitalWrite(LED_PIN, LOW);
        Serial.println("off");
        left_Servo();
      });
  server.on(
      "/up", HTTP_GET,
      [](AsyncWebServerRequest *request)
      {
        request->send(SPIFFS, "/index.html");
        digitalWrite(LED_PIN, LOW);
        Serial.println("off");
        up_Servo();
      }); 
  server.on(
      "/accel", HTTP_GET,
      [](AsyncWebServerRequest *request)
      {
        request->send(SPIFFS, "/index.html");
        digitalWrite(LED_PIN, LOW);
        Serial.println("off");
        accel_DC();
      });   
  server.on(
      "/break", HTTP_GET,
      [](AsyncWebServerRequest *request)
      {
        request->send(SPIFFS, "/index.html");
        digitalWrite(LED_PIN, LOW);
        Serial.println("off");
        break_DC();
      });
  server.onNotFound(
      [](AsyncWebServerRequest *request)
      {
        Serial.println("NOT FOUND: " + String(request->url()));
        request->send(404, "text/plain", "Not found");
      });

  // サーバースタート
  server.begin();

  Serial.println("Server start!");
}

void loop()
{
  // 何もしない
}