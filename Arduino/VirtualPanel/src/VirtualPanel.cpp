/*
  VirtualPanel.cpp 
  MIT Licence - Copyright (c) 2024 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

  VirtualPanel is a small libray implementing the comunication
	from an Arduino to VirtualPanel.exe on a PC.
	This library uses the ArduinoPort library as communications protocol.
  	
	V1.6.0	25-2-2024  
*/

#include "VirtualPanel.h"

VirtualPanel Panel(PanelCallback); // instantiation of the Panel object

vpsrq_Stats PanelSrqStatus = vpsrq_Success;

// Synchronous request handling
bool PanelSyncRequest(int16_t event)
{
  static bool SyncBusy = false;
  uint32_t SyncTimeout = 0;

  if(SyncBusy)
  {
	  PanelSrqStatus = vpsrq_ConcurrencyErr; // ConcurrencyErr
	  return false; 
  }
    
  for (uint16_t i=0; i < sizeof(vpsrq_Channels)/2; i++)
  {
    if(event == vpsrq_Channels[i])
    {
      SyncBusy = true;      
      Panel.send(event);
      SyncTimeout = millis() + 100;
      while(SyncTimeout > millis())
      {
        if(Panel.receive(event)) 
        {
          SyncBusy = false;
					PanelSrqStatus = vpsrq_Success; // Succes!
          return true;
        }
      }
      SyncBusy = false;
	    PanelSrqStatus = vpsrq_Timeout; // error Timeout 
			return false;
    }
  }
  PanelSrqStatus = vpsrq_InvalidChannel; // error not a SyncRequest event
  return false;	
}


// _Line Graph draw helper function. Packs four bytes into a uint32_t.
uint32_t _Line( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye)
{
	uint32_t linepoints;

	linepoints = ye;
	linepoints += (uint32_t)xe << 8 ;
	linepoints += (uint32_t)ys << 16 ;
	linepoints += (uint32_t)xs << 24 ;
	
	return(linepoints);
}

uint32_t _VLine( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye)
{
	uint32_t linepoints;

	ye = map(ye,0,255,0,220);
	ys = map(ys,0,255,0,220);
	linepoints = ye;
	linepoints += (uint32_t)xe << 8 ;
	linepoints += (uint32_t)ys << 16 ;
	linepoints += (uint32_t)xs << 24 ;
	
	return(linepoints);
}

// _Point Graph draw helper funtion. Packs two bytes into a uint16_t.
uint16_t _Point( uint8_t x, uint8_t y)
{
	uint16_t point;

	point = y;
	point += (uint16_t)x << 8 ;
	
	return(point);
}

// _Point Graph draw helper funtion. Packs two bytes into a uint16_t.
uint16_t _VPoint( uint8_t x, uint8_t y)
{
	uint16_t point;

	point = map(y,0,255,0,220);
	point += (uint16_t)x << 8 ;
	
	return(point);
}

// _Circle Graph draw helper function. Packs centre point (2xbyte) and radius (int16) into string.
char * _Circle( uint8_t x, uint8_t y, uint8_t rad)
{
	return (_Circle(x,y,rad, (uint16_t)0, (uint16_t)360));
}

// _Circle Graph draw helper function. Packs centre point (2xbyte), radius, start angle and arc (int16) into string.
char * _Circle( uint8_t x, uint8_t y, uint8_t rad, uint16_t angle, uint16_t arc)
{
	static char circleparams[17];
	if (arc <= (uint16_t)360)
  	sprintf(circleparams, "$$%02X%02X%02X%04X%04X", x, y, rad, angle%(uint16_t)360, arc);
	return(circleparams);
}

char * _VCircle( uint8_t x, uint8_t y, uint8_t rad)
{
	uint8_t Vy = map(y,0,255,0,220);
	return (_Circle(x,Vy,rad, (uint16_t)0, (uint16_t)360));
}

char * _VCircle( uint8_t x, uint8_t y, uint8_t rad, uint16_t angle, uint16_t arc)
{
	uint8_t Vy = map(y,0,255,0,220);
	return (_Circle(x,Vy,rad, angle, arc));
}

// _Line Graph draw helper function. Packs four bytes into a uint32_t.
uint32_t _Sound( uint16_t frequency, uint16_t duration)
{
	uint32_t BeepParam;
	
  BeepParam = duration;
	BeepParam += (uint32_t)frequency << 16 ;
	
	return(BeepParam);
}

#ifndef ARDUINO_ARCH_SAM
// _FString - dtostrf wrapper for use in sendf.
char * _FString(float FloatValue, int16_t StringSize, int16_t Decimals)
{
  static char FloatString[11];
	
	return(_FString(FloatValue, StringSize, Decimals, FloatString));
}

// _FString - dtostrf wrapper for use in sendf.
char * _FString(float FloatValue, int16_t StringSize, int16_t Decimals, char * ReturnBuffer)
{
  dtostrf(FloatValue, StringSize, Decimals, ReturnBuffer);
  uint16_t i=0;
  while (ReturnBuffer[i]==' ') ReturnBuffer[i++]='0';
  return(ReturnBuffer);
}
#endif


