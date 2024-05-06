#include <Arduino.h>

#include <Ultrasonic.h>

#include "notes.h"

#define LED_PIN 2

#define TRIG_PIN A0
#define ECHO_PIN A1

int detectedNote();
void playNote(int note);

Ultrasonic Sensor(TRIG_PIN, ECHO_PIN);

void setup() 
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() 
{
  static int lastNote = 0;
  static unsigned long lastNoteTime = 0;

  if (millis() - lastNoteTime >= 500) {
    int note = detectedNote();
    if (note > 0) {
      digitalWrite(LED_PIN, HIGH);

      playNote(note);
      lastNote = note;
      lastNoteTime = millis();
    }
  } else if (millis() - lastNoteTime > 250) {
      digitalWrite(LED_PIN, LOW);
      delay(50);
  }
}

int detectedNote()
{
  unsigned int distance = Sensor.read();

  if (distance >= 5 && distance <= 15)
    return DO;
  else if (distance >= 16 && distance <= 25)
    return RE;
  else if (distance >= 26 && distance <= 35)
    return MI;
  else if (distance >= 36 && distance <= 45)
    return FA;
  else if (distance >= 46 && distance <= 55)
    return SOL;
  else if (distance >= 56 && distance <= 65)
    return LA;
  else if (distance >= 66 && distance <= 75)
    return CI;
  else
    return 0;
}

void playNote(int note)
{
  Serial.print("*");
  Serial.print(note);
  Serial.println("#");
  delay(5);
}