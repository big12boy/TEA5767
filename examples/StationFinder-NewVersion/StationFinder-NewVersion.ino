/*
 * Using new Library Functions!
 * Sweep through all Frequencies, find available Stations and switch on User Input
 * 
 * Licence: GNU GPL
 * 
 * by big12boy 2017
 */

#include <TEA5767.h>
TEA5767 radio = TEA5767();

//User changeable
short minlvl = 14; //Required Signal Level (0-5=unuseable, 6-9=poor, 10-12=good, 13-14=really good, 15=excellent)
long baud = 250000; //Baudrate of the Serial Interface
//---------------

void setup() {
  Serial.begin(baud); //Initialize Serial Connection
  
  radio.init(minlvl); //Initialize needed Features and search for Stations

  //Print the result
  Serial.print("Found ");
  Serial.print(radio.getStations()); //Get Number of Stations from Library
  Serial.println(" Station(s):");
  Serial.println();

  //Print all available Stations
  listStations();
  
  Serial.println("Send something to change to the next Station!");
}

void loop() {
  //Wait for User Input
  if(Serial.available()){
    radio.nextStation(); //Switch to next Station

    delay(50);    //Wait for the Signal to stabilize
    printStation(); //Print Station Details

    while(Serial.available())Serial.read(); //Clear the Serial Buffer
  }
}

void listStations(){
  short stations = radio.getStations(); //Get available Stations
  for(short i = 0; i < stations; i++){ //Go through all Stations
    delay(50);  //Wait for the Signal to stabilize
    printStation(); //Print Details
    radio.nextStation(); //Jump to the next Station
  }
  Serial.println("----------------------"); //Finish of the List
}

void printStation(){
  Serial.print("Frequency:   ");
  Serial.println(radio.getFrequency()); //Print current Frequency
  Serial.print("Signallevel: ");
  Serial.println(radio.getSignalLevel()); //Print current Signal Level (0-15)
  Serial.println();
}
