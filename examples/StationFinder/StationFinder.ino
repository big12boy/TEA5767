/*
 * Sweep through all Frequencies and find available Stations
 * Some Stations may appear more than once!
 * 
 * Licence: GNU GPL
 * 
 * by big12boy 2017
 */

#include <TEA5767.h>
TEA5767 radio = TEA5767();

//User changeable
float frequency = 87.50; //Start Frequency
short minlvl = 14; //Required Signal Level (0-5=unuseable, 6-9=poor, 10-12=good, 13-14=really good, 15=excellent)
long baud = 250000;
//---------------

float freq[100]; //Upto 100 Stations can be stored
short freqs = 0;

void setup() {
  Serial.begin(baud);
  Wire.begin();
  
  radio.setFrequency(frequency); //Set Start Frequency
  delay(20);
}

void loop() {
  //Sweep
  if(frequency <= 108.00){
    //Get Data
    bool stereo = radio.isStereo();
    short lvl = radio.getSignalLevel();
  
    //Is it useable?
    if(lvl >= minlvl && stereo){
      foundStation(frequency, lvl); //Print Station to Console
    }
  
    frequency += 0.1; //Increase a bit
    if(frequency > 108.00){ //Check for upper Limit
      printArray();
      radio.setFrequency( freq[0] );
    }
    else radio.setFrequency(frequency);  //Set new Frequency
    
    delay(20); //Wait for stabilization
  }
  //Select Station
  else{
    if(Serial.available()){
      int sel = Serial.parseInt();
      if(sel <= freqs && sel > 0){
        //Set Frequency
        radio.setFrequency( freq[sel-1] );
        //Print to Console
        Serial.println();
        Serial.print("Set Frequency: ");
        Serial.println( freq[sel-1] );
      }
    }
  }
}

void foundStation(float aFreq, short aLvl){
  //Add to to Array
  freq[freqs] = aFreq;
  freqs++;
  
  //Print Station Data
  Serial.println("Found Station:");
  Serial.print("Frequency: ");
  Serial.println(aFreq);
  Serial.print("Signal:    ");
  Serial.println(aLvl);  
  Serial.println();  
}

void printArray(){
  Serial.println();
  Serial.println("Stored Frequencies:");
  for(int i = 0; i < freqs; i++){
    Serial.print(i+1);
    Serial.print("=");
    Serial.print(freq[i]);
    Serial.print("  ");
  }
  Serial.println();
  Serial.println("Send Number to recall a Frequency!");
}
