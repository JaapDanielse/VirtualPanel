/*
  VirtualPanel.h 
  MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

  VirtualPanel is a small libray implementing the comunication
	from an Arduino to VirtualPanel.exe on a PC.
	This library uses the ArduinoPort library as communications protocol.
  	
	V1.1.0    23-03-2020 JpD
*/

#pragma once
#include "ArduinoPort.h" 

enum vp_channel : int // event/channel list 
{
  //
  ApplicationName, // >string, >color string
  PanelConnected,  // <void (triggers Static Display)
  Reset,           // >void
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
  Slider_1, // >bool >int (value) <int (value) (no static display)
  Slider_2, // 
  Slider_3, // 
  Slider_4, // 
  Slider_5, // 
  //
  MaxSlider_1, // >int (max value)
  MaxSlider_2, // 
  MaxSlider_3, // 
  MaxSlider_4, // 
  MaxSlider_5, // 
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
  MonitorLog,  // >any
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
  GraphDrawLine, // ULong 4x byte (Fx,Fy,Tx,Ty) UInt 2 x byte (X,Y), color string, pen size
  GraphDrawPixel, // UInt 2 x byte (X,Y), color string, pen size
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
  Info, //
  InfoTitle, //
  InfoText, //
	//
	PanelColor, //
	//
	GraphDrawCircle, //
	//
	GraphInput_1, //
	GraphInput_2, //
	GraphInput_3, //
	GraphInput_4, //
	GraphInput_5, //
	//
	MinGraphInput_1, //
	MinGraphInput_2, //
	MinGraphInput_3, //
	MinGraphInput_4, //
	MinGraphInput_5, //
	//
	MaxGraphInput_1, //
	MaxGraphInput_2, //
	MaxGraphInput_3, //
	MaxGraphInput_4, //
	MaxGraphInput_5, //
	//
	GraphInputLabel_1, //
	GraphInputLabel_2, //
	GraphInputLabel_3, //
	GraphInputLabel_4, //
	GraphInputLabel_5, //
  //
	OpenFile_1, //
	OpenFile_2, //
	OpenFile_3, //
	OpenFile_4, //
	//
	ReadLineFile_1, //
	ReadLineFile_2, //
	ReadLineFile_3, //
	ReadLineFile_4, //
	//
	WriteLineFile_1, //
	WriteLineFile_2, //
	WriteLineFile_3, //
	WriteLineFile_4, //
	//
	ClearFile_1, //
	ClearFile_2, //
	ClearFile_3, //
	ClearFile_4, //
	// 
	DeleteFile_1, //
	DeleteFile_2, //
	DeleteFile_3, //
	DeleteFile_4, //
	//
	FileOpenDialogTitle_1,
	FileOpenDialogTitle_2,
	FileOpenDialogTitle_3,
	FileOpenDialogTitle_4,
	//
	EndChannel //
  //
};

class VirtualPanel : public ArduinoPort
{
	public:
	 using VP_CallbackFunction = void (*)(vp_channel);
	 
	 VirtualPanel(VP_CallbackFunction cb) : ArduinoPort("[VirtualPanel]", (PanelCallbackFunction) cb, Serial){}
	 void begin()
	 {
	    Serial.begin(115200);
	 }
};

void PanelCallback(vp_channel event); // Callback Function declaration. Calback routine itself must be created in the sketch

extern VirtualPanel Panel; // Panel object declaration

uint16_t _Point( uint8_t x, uint8_t y); // Declaration of graph point helper function (packs two bytes in a iunt16_t).

uint32_t _Line( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye); // Declaration of graph line helper function (packs four bytes in a uint32_t).

char * _Circle( uint8_t xs, uint8_t ys, uint8_t rad, uint16_t angle, uint16_t arc); // Declaration of graph (packs four bytes in a uint32_t).

char * _Circle( uint8_t x, uint8_t y, uint8_t rad);


uint32_t _VLine( uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye); // Declaration of graph line helper function (packs four bytes in a uint32_t). (converting y coordinates to values)

uint16_t _VPoint( uint8_t x, uint8_t y); // Declaration of graph point helper function (packs two bytes in a iunt16_t). (converting y coordinate to value)

char * _VCircle( uint8_t xs, uint8_t ys, uint8_t rad, uint16_t angle, uint16_t arc); // Declaration of graph (packs four bytes in a uint32_t).

char * _VCircle( uint8_t x, uint8_t y, uint8_t rad);


uint32_t _Sound( uint16_t frequency, uint16_t duration); // Declaration of Beep helper funtion

char * _FString(float FloatValue, int16_t StringSize, int16_t Decimals); // Declaration of F(loat)String helper function

char * _FString(float FloatValue, int16_t StringSize, int16_t Decimals, char * ReturnBuffer);




