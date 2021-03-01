#include <Arduino.h>

float filterRad = 0;
float radMinVal = 1000;
float radMaxVal = -1000;
unsigned long lastTime = millis();
void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(14, INPUT);
  analogReadResolution(16);
  // analogWriteRes(16);
}

void loop()
{
  float radar = analogRead(14) / 65536.0f;
  filterRad += (radar - filterRad) * 0.01;

  radMinVal = min(radMinVal, filterRad);
  radMaxVal = max(radMaxVal, filterRad);

  if (millis() > lastTime + 3000)
  {
    lastTime = millis();
    Serial.printf("radMinVal:%f radMaxVal:%f \n", radMinVal, radMaxVal);
  }
  analogWrite(13, filterRad * 255);
}