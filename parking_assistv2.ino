/*
 * Using UNOR3, with CharlieWing.
 * 
 * Will need to provide external 5V to Sonar to us 3v3 board, or use a down-stepper.
 * 
 */










#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Adafruit_SleepyDog.h"

// If you're using the full breakout...
//Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 425 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define PIR5v        2
#define PIRtrigger   3
#define PIRgnd       4
#define PIRaction    13


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int distanceNow, distanceOld, timeCount = 100;
bool sleep=false;
int PIRread;

void setup() {
  pinMode(PIR5v, OUTPUT);
  pinMode(PIRgnd,OUTPUT);
  pinMode(PIRtrigger,INPUT);
  digitalWrite(PIR5v,HIGH);
  digitalWrite(PIRgnd,LOW);
   
    Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!"); 
  
}

void loop() {
  //matrix.drawFastHLine(1,0,9,255);
  //matrix.drawFastHLine(6,0,9,255);
  PIRread = digitalRead(PIRtrigger);
  Serial.println(PIRread);
  if (PIRread == LOW) { 
      digitalWrite(PIRaction, HIGH);
      //Serial.println("Motion Detected!");
  }
  else {
      digitalWrite(PIRaction, LOW);
      //Serial.println("no motion");
  }
  
  //delay(30);  // Wait 500ms between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //Serial.print("Ping: ");
  //Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  //Serial.println("cm");
  distanceNow = (uS / US_ROUNDTRIP_CM);


 if (PIRread == HIGH)
 {
    //timeCount++;
    lights(distanceNow);
     //if (timeCount % 55 == 0)
    //{
      //Serial.println("running 10 second loop");
      //timeCount = 0;
      //checkSleep();
      distanceOld = distanceNow;
    //}
  }
  else
  {
    matrix.clear();
    }

 
 
}

void checkSleep()
{
   if (distanceOld == distanceNow || distanceNow == 0)
    {
      Serial.println("sleeping 5");
      matrix.clear();
      Watchdog.sleep(5000);
      sleep = true;
    }
    else sleep = false;
}


void lights(int distance)
{
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(100);
 // for (int8_t x=0; x<=32; x++) {
    matrix.clear();
    matrix.setCursor(0,0);
    matrix.print(distance);
    delay(30);
  //}
}

