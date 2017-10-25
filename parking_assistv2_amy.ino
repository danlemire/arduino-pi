/*************************************************************************************
 PARTS: UNO, Adafruit CharlieWing, Ultrasonic Sensor (HC-SR04), PIR motion

 GOAL: when motion is detected, measure the distance detected. Provide the distance to 
 target on the CharlieWing to provide parking distance estimation useful when backing
 into the garage.
   
*************************************************************************************/

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Adafruit_SleepyDog.h"

Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 425 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define PIR5v        2
#define PIRtrigger   3
#define PIRgnd       4
#define PIRaction    13
#define GND          10

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int distanceNow;
int PIRread;

void setup() 
{
  pinMode(PIR5v, OUTPUT);
  pinMode(PIRgnd,OUTPUT);
  pinMode(PIRtrigger,INPUT);
  digitalWrite(PIR5v,HIGH);
  digitalWrite(PIRgnd,LOW);

  pinMode (GND,OUTPUT);
  digitalWrite(GND,LOW);
  
  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) 
  {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!"); 
  matrix.setRotation(90);

}

void loop() 
{
  PIRread = digitalRead(PIRtrigger);
  Serial.println(PIRread);
  if (PIRread == LOW) digitalWrite(PIRaction, HIGH);
  else digitalWrite(PIRaction, LOW);
  
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  distanceNow = (uS / US_ROUNDTRIP_CM);
  //Serial.println(distanceNow);
  if (PIRread == HIGH) lights(distanceNow/10); //divide by 10 to update the display every 10cm.
  else matrix.clear();
}

void lights(int distance)
{
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(100);
  matrix.clear();
  matrix.setCursor(0,0);
  matrix.print(distance);
  delay(30);
}

