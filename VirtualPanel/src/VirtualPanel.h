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

const char PanelID[] = "[PANEL01V01]"; // Panel ID used to connect to the right panel application

void PanelCallback(int event, int type); // Callback Function declaration. Calback routine itself must be created in the sketch

extern ArduinoPort Panel; // Callback Function instantiation -> see PanelOne.cpp

uint16_t _Point( uint8_t x, uint8_t y); // Declaration of graph point helper function (packs two bytes in a iunt16_t).

uint32_t _Line( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye); // Declaration of graph line helper function (packs four bytes in a uint32_t).


enum vp_event // event/channel list 
{
  //
  ApplicationName, // ApplicationName
  PanelConnected,  // PannelConnected
  Reset,           // Reset
  StaticDisplay,   // StaticDisplay
  DynamicDisplay,  // DynamicDisplay
  UnixTime,        // UnixTime
  PanelColor,      // Panel
  Pling,           // Pling
  //
  Button_1,  // Button_1
  Button_2,  // Button_2
  Button_3,  // Button_3
  Button_4,  // Button_4
  Button_5,  // Button_5
  Button_6,  // Button_6
  Button_7,  // Button_7
  Button_8,  // Button_8
  Button_9,  // Button_9
  Button_10, // Button_10
  Button_11, // Button_11
  Button_12, // Button_12
  Button_13, // Button_13
  Button_14, // Button_14
  Button_15, // Button_15
  Button_16, // Button_16
  Button_17, // Button_17
  //
  ScrollBar_1, // ScrollBar_1
  ScrollBar_2, // ScrollBar_2
  ScrollBar_3, // ScrollBar_3
  ScrollBar_4, // ScrollBar_4
  //
  MaxScrollBar_1, // MaxScrollBar_1
  MaxScrollBar_2, // MaxScrollBar_2 
  MaxScrollBar_3, // MaxScrollBar_3
  MaxScrollBar_4, // MaxScrollBar_4
  //
  Led_1,   // Led_1
  Led_2,   // Led_2
  Led_3,   // Led_3
  Led_4,   // Led_4
  Led_5,   // Led_5
  Led_6,   // Led_6
  Led_7,   // Led_7
  Led_8,   // Led_8
  Led_9,   // Led_9
  Led_10,  // Led_10
  Led_11,  // Led_11
  Led_12,  // Led_12
  Led_13,  // Led_13
  //
  Display_1, // Display 1
  Display_2, // Display 2
  Display_3, // Display 3
  Display_4, // Display 4
  //
  Monitor,        // Monitor
  MonitorField_1, // MonitorField_1
  MonitorField_2, // MonitorField_2
  MonitorField_3, // MonitorField_3
  MonitorField_4, // MonitorField_4
  MonitorField_5, // MonitorField_5
  MonitorField_6, // MonitorField_6
  //
  MonitorScrollBox,  // MonitorScrollBox
  //
  Graph, // false/true, byte (1(draw), 2(stat), 3(run)
  GraphGrid, // byte number of segments
  GraphPen, // $FINE, $THICK, $RED, $GREEN, $YELLOW, $ORANGE, $WHITE, $BLUE 
  GraphDrawLine, // ULong 4x byte (Fx,Fy,Tx,Ty) UInt 2 x byte (X,Y)
  GraphDrawPixel, // UInt 2 x byte (X,Y)
  GraphText, //
  //
	GraphValue_1, // byte 
	GraphValue_2, // byte 
	GraphValue_3, // byte 
	GraphValue_4, // byte 
	GraphValue_5, // byte 
  //
  GraphValueCount_1, // int
  GraphValueCount_2, // int
  GraphValueCount_3, // int 
  GraphValueCount_4, // int  
  GraphValueCount_5, // int 
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
	GraphButton_4  //
	//
};

#endif
