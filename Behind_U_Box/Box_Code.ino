 //Libraries
#include "dht.h"
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <Wire.h> 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//PINS
int gasled= 7;
int dhtled = 8;
int pos = 0;    // variable to store the servo position

int buzzer = 5;
int sensorThres = 600;
#define dht_apin A3 // Analog Pin sensor is connected to
int smokeA0 = A0;
RF24 radio(9, 10);
const byte address[6] = "00001";
dht DHT;
Servo myservo;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
    myservo.attach(4); 
    lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Behind You");
  delay(2000);
  lcd.clear();
pinMode(smokeA0, INPUT);
pinMode(gasled,OUTPUT);
pinMode(dhtled,OUTPUT);
Serial.begin(9600);
delay(500);//Delay to let system boot
Serial.println("DHT11 Humidity & temperature Sensor\n\n");
delay(1000);//Wait before accessing Sensor
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
 
}//end "setup()"
 
void loop(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    delay(5); }// tell servo to go to position in variable 'pos'  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);  }             
dhtsensor();
gasSensor();
pulse();
Serial.print("250");
}


//DHT sensor
void dhtsensor(){
DHT.read11(dht_apin);
lcd.setCursor(0,0);
lcd.print("Humidity: ");
lcd.print(DHT.humidity);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("Temp: ");
lcd.print(DHT.temperature); 
lcd.print("C");
delay(3000);
lcd.clear();

if(DHT.temperature>35||DHT.temperature<20||DHT.humidity<75||DHT.humidity>85)
{
tone(buzzer,1000);
digitalWrite(dhtled,HIGH);
delay(2000);  
}
}

//Gas Sensor
void gasSensor(){
int analogSensor = analogRead(smokeA0);
lcd.setCursor(0,0);
lcd.print("Gas Population:");
lcd.setCursor(0,1);
lcd.print(analogSensor);
if (analogSensor > sensorThres)
{
digitalWrite(gasled, HIGH);
tone(buzzer, 1000, 200);
delay(3000);
}
else
{
digitalWrite(gasled, LOW);
noTone(buzzer);
}
delay(2000);
lcd.clear();
}
void pulse(){

int value= "";

lcd.setCursor(0,0);
lcd.print("Heart Rate: ");
  radio.read(&value, sizeof(value));
delay(3000);
lcd.clear();
}
