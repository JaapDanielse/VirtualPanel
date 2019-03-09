/*
  VirtualPanel.h (c) J.C. Daniëlse - December 2018

  VirtualPanel is a small libray implementing the comunication
	from an Arduino to VirtualPanel.exe on a PC.
	This library uses the ArduinoPort library as communications protocol.
  	
  BSD license, all text above must be included in any redistribution.
	
	V1.0    28-12-2018 JpD
  Original version
	
	*/

#ifndef _VIRTUALPANEL_h
#define _VIRTUALPANEL_h

#include "ArduinoPort.h" 

const char PanelID[] = "[VirtualPanel]"; // Panel ID used to connect to the right panel application

void PanelCallback(int event, int type); // Callback Function declaration. Calback routine itself must be created in the sketch

extern ArduinoPort Panel; // Callback Function instantiation -> see PanelOne.cpp

uint16_t _Point( uint8_t x, uint8_t y); // Declaration of graph point helper function (packs two bytes in a iunt16_t).

uint32_t _Line( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye); // Declaration of graph line helper function (packs four bytes in a uint32_t).

uint32_t _VLine( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye); // Declaration of graph line helper function (packs four bytes in a uint32_t). (converting y coordinates to values)

uint16_t _VPoint( uint8_t x, uint8_t y); // Declaration of graph point helper function (packs two bytes in a iunt16_t). (converting y coordinate to value)

uint32_t _Sound( uint16_t frequency, uint16_t duration); // Declaration of Beep helper funtion


enum vp_event // event/channel list 
{
  //
  ApplicationName, // >string, >color string
  PanelConnected,  // <void (triggers Static Display)
  Reset,           // >void
  StaticDisplay,   // >bool (true/false) <void
  DynamicDisplay,  // >bool (true/false), >int delay  <void
  UnixTime,        // >void <unixtime (local)
  Beep,            // >void (500,400) >int (F,400) >long (F,D) 
  //
  Button_1,  // >any >colorstring >symbolstring <void
  Button_2,  // 
  Button_3,  // 
  Button_4,  // 
  Button_5,  // 
  Button_6,  // 
  Button_7,  // 
  Button_8,  // 
  Button_9,  // 
  Button_10, // 
  Button_11, // 
  Button_12, // 
  Button_13, // 
  Button_14, // 
  Button_15, // 
  Button_16, // 
  Button_17, // 
  //
  ScrollBar_1, // >bool >int (value) <int (value) (no static display)
  ScrollBar_2, // 
  ScrollBar_3, // 
  ScrollBar_4, // 
  ScrollBar_5, // 
  //
  MaxScrollBar_1, // >int (max value)
  MaxScrollBar_2, // 
  MaxScrollBar_3, // 
  MaxScrollBar_4, // 
  MaxScrollBar_5, // 
  //
  Led_1,   // >bool >colorstring >off string 
  Led_2,   // 
  Led_3,   // 
  Led_4,   // 
  Led_5,   // 
  Led_6,   // 
  Led_7,   // 
  Led_8,   // 
  Led_9,   // 
  Led_10,  // 
  Led_11,  // 
  Led_12,  // 
  Led_13,  // 
  //
  Display_1, // >any >colorstring ($YELLOW, $ORANGE, $RED, $BLUE, $BLACK, $WHITE, $BLACK, $OFF, $DEL >sizestring <void (dubblec lick)
  Display_2, // 
  Display_3, // 
  Display_4, // 
  //
	PanelInput_1, // >bool (static, volatile) >any num
	PanelInput_2, //
	//
	MinPanelInput_1, // >int >long >ulong 
	MinPanelInput_2, //
	//
	MaxPanelInput_1, // >int >long >ulong 
	MaxPanelInput_2, //
	//
	PanelInputLabel_1, // >any
	PanelInputLabel_2, //
  //
  Monitor,        // >bool (window visible)
  MonitorField_1, // >any
  MonitorField_2, // 
  MonitorField_3, // 
  MonitorField_4, // 
  MonitorField_5, // 
  MonitorField_6, // 
  //
  MonitorScrollBox,  // >any
  //
  MonitorInput_1, // >any num <any num
	MonitorInput_2, //
	MonitorInput_3, //
	MonitorInput_4, //
	MonitorInput_5, //
	MonitorInput_6, //
	//
	MinMonitorInput_1, // >int >long >ulong 
	MinMonitorInput_2, //
	MinMonitorInput_3, //
	MinMonitorInput_4, //
	MinMonitorInput_5, //
	MinMonitorInput_6, //
	//
	MaxMonitorInput_1, // >int >long >ulong 
	MaxMonitorInput_2, //
	MaxMonitorInput_3, //
	MaxMonitorInput_4, //
	MaxMonitorInput_5, //
	MaxMonitorInput_6, //
	//
	MonitorInputLabel_1, // >any
	MonitorInputLabel_2, //
	MonitorInputLabel_3, //
	MonitorInputLabel_4, //
	MonitorInputLabel_5, //
	MonitorInputLabel_6, //
	//
  Graph, // >bool false/true
  GraphGrid, // >int vert.gridcount
  GraphPen, // >color string  >thickness string
  GraphDrawLine, // ULong 4x byte (Fx,Fy,Tx,Ty) UInt 2 x byte (X,Y)
  GraphDrawPixel, // UInt 2 x byte (X,Y)
  GraphText, // >string >int (point)
  //
	GraphValue_1, // >byte >color string >tickness string ($1PX, $2PX, $3PX, $4PX)
	GraphValue_2, // 
	GraphValue_3, //  
	GraphValue_4, //  
	GraphValue_5, //  
  //
  GraphValueCount_1, // >int
  GraphValueCount_2, // 
  GraphValueCount_3, // 
  GraphValueCount_4, //   
  GraphValueCount_5, // 
  // 
	GraphCaption_1, //
	GraphCaption_2, //
	//
	GraphLabel_1, //
	GraphLabel_2, //
	GraphLabel_3, //
	GraphLabel_4, //
	GraphLabel_5, //
	//
	GraphButton_1, //
	GraphButton_2, //
	GraphButton_3, //
	GraphButton_4,  //
	//
  GraphClick, //
  GraphDoubleClick, //
  GraphRightClick, //
	//
  Info,
  InfoLabel,
  InfoText
  //
};

#endif
