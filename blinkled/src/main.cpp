#include <Arduino.h>

#define LED_PIN 5

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  Serial.printf("Program Start\n");
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  Serial.printf("LED_PIN - HIGH\n");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.printf("LED_PIN - LOW\n");
  delay(1000);
}