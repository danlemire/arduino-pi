/****************************************************************************
PARTS: UNO with vibration switch (three pins)
define custom pins to for use in the program, set pins to skip dupont cables
plug vibration switch directly into the board.

GOAL: Toggle the state of the onboard LED light by tapping the module/UNO.
****************************************************************************/
#define PWR   9
#define GND  10
#define Shock 8

int LED = 13; //use the UNO onboard LED
int val;
int LEDstate = 0;

void  setup()
{
  pinMode(PWR,OUTPUT);
  digitalWrite(PWR,HIGH);
  pinMode(GND,OUTPUT);
  digitalWrite(GND,LOW);
  pinMode(Shock,INPUT);
  pinMode(LED, OUTPUT); //define LED as a output port
}
void loop()
{  
  val = digitalRead(Shock); //read the value of the digital input used with the shock sensor.
  if (val == LOW)
  { 
    if (LEDstate == 0) LEDon();
    else LEDoff();  
    delay(200);
  }
}  

void LEDon()
{
  digitalWrite(LED, HIGH);
  LEDstate = 1;
}

void LEDoff()
{
  digitalWrite(LED, LOW);
  LEDstate = 0;  
}
