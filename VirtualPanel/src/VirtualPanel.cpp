/*
  VirtualPanel.cpp (c) J.C. Daniëlse - December 2018

  VirtualPanel is a small libray implementing the comunication
	from an Arduino to VirtualPanel.exe on a PC.
	This library uses the ArduinoPort library as communications protocol.
  	
  BSD license, all text above must be included in any redistribution.
	
	V1.0    28-12-2018 JpD
  Original version
	
	*/
	
#include "VirtualPanel.h"

ArduinoPort Panel = ArduinoPort(PanelID, PanelCallback); // Create VirtualPanel Object

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

// _Line Graph draw helper function. Packs four bytes into a uint32_t.
uint32_t _Sound( uint16_t frequency, uint16_t duration)
{
	uint32_t BeepParam;
	
  BeepParam = duration;
	BeepParam += (uint32_t)frequency << 16 ;
	
	return(BeepParam);
}
