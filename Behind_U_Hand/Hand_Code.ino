
#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h>    

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//  Variables
const int PulseWire = A5;            
int Threshold = 550;        
                              
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
void setup() {   
  Serial.begin(9600);
//  radio.begin();
//  radio.openWritingPipe(address);
//  radio.setPALevel(RF24_PA_MIN);
//  radio.stopListening();
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  

  }
}
void loop() {
pulsesensor();
                  // considered best practice in a simple sketch.
}
void pulsesensor()
{
   int myBPM = pulseSensor.getBeatsPerMinute(); 
if (pulseSensor.sawStartOfBeat()) {            
 Serial.println("?  A HeartBeat Happened ! "); 
 Serial.print("BPM: ");                        
 Serial.println(myBPM);   
 int value;
  value = myBPM;
  radio.write(&value, sizeof(value));
 delay(1000);// Print the value inside of myBPM. 
}
  }

  