/*
TEA5767 FM Radio Library
Using I2C for Communication


big12boy - 2017
*/

#include <Arduino.h>
#include <TEA5767.h>

TEA5767::TEA5767(){
	_addr = 0x60;
	_lvl = 2;
	_freqH = 0x00; _freqL = 0x00;
	_muted = false; _search = false; _up = true; _stby = false; _snc = true;
}

//Send Data to the Module
void TEA5767::send(){  	
	Wire.beginTransmission(_addr); 
	Wire.write((_muted << 7) | (_search << 6) | _freqH);
	Wire.write(_freqL);
	Wire.write((_up << 7) | (_lvl & 0x3 << 5) | 0x10);
	Wire.write(0x10 | (_stby << 6));
	Wire.write(0x00);
	Wire.endTransmission();
}
//Get Data from the Module
void TEA5767::get(){  	
	byte wIn;
	Wire.requestFrom(_addr, 5);
	while(Wire.available() < 5);
	
	wIn = Wire.read();
	bool rf = wIn & 0x80;
	bool blf = wIn & 0x40;
	if(!rf)_rdy = 0;
	else if(rf && !blf)_rdy = 1;
	else _rdy = 2;
	_freqH = wIn & 0x3F;
	
	wIn = Wire.read();
	_freqL = wIn;
	
	wIn = Wire.read();
	_stereo = wIn & 0x80;
	
	wIn = Wire.read();
	_lvl = wIn >> 4;
	
	wIn = Wire.read();	
}

//Set Functions
bool TEA5767::setFrequency(float frequency){
	if(frequency < 87.50 || frequency > 108.00) return false;
	
  	unsigned int freqC = (frequency * 1000000 + 225000) / 8192; 
	_freqH = freqC >> 8;
	_freqL = freqC & 0XFF;	
	send();
	return true;
}
void TEA5767::setMuted(bool muted){
	_muted = muted;	
	send();
}
bool TEA5767::setSearch(bool up, int level){
	_up = up;
	if(level < 1 || level > 3) return false;
	_lvl = level;
	_search = true;
	send();
	_search = false;
	//send();
	return true;
}
void TEA5767::setStandby(bool stby){
	_stby = stby;	
	send();
}
void TEA5767::setStereoNC(bool snc){
	_snc = snc;	
	send();
}

//Get Functions
float TEA5767::getFrequency(){
	get();	
	double freqI = (_freqH << 8) | _freqL;
	return (freqI * 8192 - 225000) / 1000000.00; 
}
int TEA5767::getReady(){
	get();	
	return _rdy;
}
bool TEA5767::isStereo(){
	get();	
	return _stereo;
}
short TEA5767::getSignalLevel(){
	get();	
	return _lvl;
}
