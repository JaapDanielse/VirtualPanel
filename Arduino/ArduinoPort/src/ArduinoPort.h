/*
  ArduinoPort.h
  MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

  ArduinoPort is a libray to provide a simple, controlled, 
	event communication between an Arduino and a PC based application
	under C# using the ArduinoPort.dll.
  	
	V1.0.1    7-06-2019 JpD
*/

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SENDFBUFFERSIZE 60 // Buffersize for formatted text sendf
#define RECEIVEBUFFERSIZE 40 // Buffersize for pannel events

// message content type declaration
enum class vp_type
{
	vp_void,
	vp_string,
	vp_boolean,
	vp_byte,
	vp_int,
	vp_uint,
	vp_long,
	vp_ulong,
	vp_float,
	
	vp_error 
};


class ArduinoPort
{
	public:
		using PanelCallbackFunction = void(*)(int);
		
		ArduinoPort() = default;
		ArduinoPort(const char* panel_id, PanelCallbackFunction CallBackPointer, Stream& comport);

		void send(int channel);
		void send(int channel, bool value);
		void send(int channel, const char* message);
		void send(int channel, const __FlashStringHelper* message);
		void send(int channel, uint8_t value);
		void send(int channel, int16_t value);
		void send(int channel, uint16_t value);
		void send(int channel, int32_t value);
		void send(int channel, uint32_t value);
		void send(int channel, float value);
		void sendf(int channel, const char* message, ...);
		void sendf(int channel, const __FlashStringHelper* message, ...);
		bool delay(uint16_t delaytime, bool receive = true);
		void receive();

    vp_type  vpr_type = vp_type::vp_error;

		char*    vpr_string = nullptr;
		bool     vpr_boolean = false;
		uint8_t  vpr_byte = 0;
		int16_t  vpr_int = 0;
		uint16_t vpr_uint = 0;
		int32_t  vpr_long = 0;
		uint32_t vpr_ulong = 0;
		float    vpr_float = 0.0f;

	private:
		const char* _panel_id;
		PanelCallbackFunction _CallBackPointer;
		Stream* _comport;

		char SerialInpBuf[RECEIVEBUFFERSIZE];
		int  SerialInpIdx = 0;
		
		bool IsAllHex(char * hexvalue);
		uint32_t Hex2Bin(char* hexvalue);
};