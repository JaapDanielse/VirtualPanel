/*
  ArduinoPort.h
  MIT Licence - Copyright (c) 2024 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

  ArduinoPort is a libray to provide a simple, controlled, 
	event communication between an Arduino and a PC based application
	under C# using the ArduinoPort.dll.
  	
	V2.0.0b4	16-8-2024  
*/

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SENDFBUFFERSIZE 60 // Buffersize for formatted text sendf
#define RECEIVEBUFFERSIZE 65 // Buffersize for pannel events: 60 + 5 (msg overhead)

// message content type declaration
enum vp_type : uint8_t
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
		using PanelCallbackFunction = void(*)(uint8_t);
		
		ArduinoPort() = default;
		ArduinoPort(const char* panel_id, PanelCallbackFunction CallBackPointer, Stream& comport);

		void send(uint8_t channel);
		void send(uint8_t channel, bool value);
		void send(uint8_t channel, const char* message);
		void send(uint8_t channel, const __FlashStringHelper* message);
		void send(uint8_t channel, uint8_t value);
		void send(uint8_t channel, int16_t value);
		void send(uint8_t channel, uint16_t value);
		void send(uint8_t channel, int32_t value);
		void send(uint8_t channel, uint32_t value);
		void send(uint8_t channel, float value);
		void sendf(uint8_t channel, const char* message, ...);
		void sendf(uint8_t channel, const __FlashStringHelper* message, ...);
		bool delay(uint16_t delaytime, bool receive = true);
		bool receive(int16_t SyncChannel = -1);

    vp_type  vpr_type = vp_type::vp_error;

		char*    vpr_string = nullptr;
		bool     vpr_boolean = false;
		uint8_t  vpr_byte = 0;
		int16_t  vpr_int = 0;
		uint16_t vpr_uint = 0;
		int32_t  vpr_long = 0;
		uint32_t vpr_ulong = 0;
		float    vpr_float = 0.0f;

	protected:
		const char* _panel_id;
		PanelCallbackFunction _CallBackPointer;
		Stream* _comport;

		char SerialInpBuf[RECEIVEBUFFERSIZE];
		uint16_t  SerialInpIdx = 0;
		
		bool IsAllHex(char * hexvalue);
		uint32_t Hex2Bin(char* hexvalue);
		uint16_t FSHLength(const __FlashStringHelper* fshString);
};