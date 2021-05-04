# TEA5767-Library
Arduino Library for the TEA5767 Radio Module

## Supported Functions:
 - short: init(short minlvl)            //Initialize Bus and search for Stations
 - bool:  setFrequency(float frequency) //Set Radio Frequency
 - void:  setMuted(bool muted)          //Mute/Unmute Module
 - ~~bool:  setSearch(bool up, int level)~~	//Search for Stations <= Currently not working
 - void:  setStandby(bool stby)         //Enable/Disable Standby Mode
 - void:  setStereoNC(bool snc)         //Enable/Disable Stereo Noise Cancelling
 - float: getFrequency()                //Returns the current Radio Frequency
 - int:   getReady()                    //Get current State (0=Nothing, 1=Found Station, 2=Reached Frequency Limit)
 - bool:  isStereo()                    //Get if the Frequency support Stereo
 - short: getSignalLevel()              //Get Signal Level (0-15)
 - int:   findStations(short minlvl)    //Search for available Stations
 - float: nextStation()                 //Go to next Station
 - float: previousStation()             //Go to previous Station
 - short: getStations()                 //Get Number of Stations
  
## How to install:
  1.  Download ZIP
  2.  Click Sketch => Include Library => Add .ZIP Library
  3.  Select downloaded ZIP-File
  4.  Try out the included examples!
  
## How to connect the Module:
 - GND to GND
 - VCC to 5V (3.3V won't work perfectly well and cause random errors, like frequency shift)
 - SDA and SCL depend on your board, check [Arduino-Wire](https://www.arduino.cc/en/Reference/Wire)
