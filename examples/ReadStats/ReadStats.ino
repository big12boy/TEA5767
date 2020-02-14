/*
 * Simple Program to set a Frequency and read Statistics 
 * 
 * Licence: GNU GPL
 * 
 * by big12boy 2017
 */

#include <TEA5767.h>
TEA5767 radio = TEA5767();

float frequency = 99.10; //Enter your own Frequency
long baud = 250000; //Enter your own Baudrate

long lmillis = 0;

void setup() {
  //Setup Serial and I2C
  Serial.begin(baud);
  Wire.begin();
  
  //Set Frequency to start with
  radio.setFrequency(frequency);
}

void loop() {
  //Check for User Input
  if(Serial.available()){
    float frequency = Serial.parseFloat(); //Read Frequency from Serial
    radio.setFrequency(frequency); //Set Frequency
  }
  
  //Check for time (active every second
  if(lmillis <= millis()){
    lmillis = millis() + 1000; //Read current time and add 1 second
    
	//Print Stats to Serial Console
    printFrequency();
    printReady();
    printStereo();
    printSignalLevel();
    
    Serial.println();
  }
}

void printFrequency(){
  float frequency = radio.getFrequency(); //Get Frequency
  Serial.print("Frequency: ");
  Serial.println(frequency, 2);
}

void printReady(){
  int rdy = radio.getReady(); //Get State
  Serial.print("Ready: ");
  Serial.println(rdy);
}

void printStereo(){
  bool stereo = radio.isStereo(); //Get Stereo
  Serial.print("Stereo: ");
  Serial.println(stereo);
}

void printSignalLevel(){
  short level = radio.getSignalLevel(); //Get Signal Level
  Serial.print("Signal (0-15): ");
  Serial.println(level);
}
