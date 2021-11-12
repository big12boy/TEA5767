/*
TEA5767 FM Radio Library
Using I2C for Communication


big12boy - 2017
*/

#include <Wire.h>

#ifndef TEA5767_h
#define TEA5767_h

class TEA5767{
private:
	int _addr;
	short _lvl, _rdy, _sel, _staCnt;
	byte _freqH, _freqL;
	bool _muted, _search, _up, _stby, _snc, _stereo;
	float _stations[20];
	
	void send();
	void get();
	
public:
	TEA5767();
	short init(short minlvl);
	
	bool setFrequency(float frequency);
	void setMuted(bool muted);
	bool setSearch(bool up, int level);
	void setStandby(bool stby);
	void setStereoNC(bool snc);
	
	float getFrequency();
	int getReady(); //0 Not Ready, 1 Ready, 2 Reached Limit
	bool isStereo();
	short getSignalLevel();	
	bool isMuted();
	
	int findStations(short minlvl);
	float nextStation();
	float previousStation();
	short getStations();
};

#endif
