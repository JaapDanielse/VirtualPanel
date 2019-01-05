/*
  ArduinoPort.h (c) J.C. Daniëlse - December 2018

  ArduinoPort is a libray to provide a simple, controlled, 
	event communication between an Arduino and a PC based application
	under C# using the ArduinoPort.dll.
  	
  BSD license, all text above must be included in any redistribution.
	
	V1.0    28-12-2018 JpD
  Original version
	
	*/

#ifndef _ARDUINOPORT_h
#define _ARDUINOPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SENDFBUFFERSIZE 60 // Buffersize for formatted text Sendf
#define RECEIVEBUFFERSIZE 30 // Buffersize for pannel events

extern "C"
{
	typedef void(*PanelCallbackFunction) (int event, int type);
}

// message content type declaration
enum vp_type
{
	vp_void,
	vp_string,
	vp_boolean,
	vp_byte,
	vp_int,
	vp_uint,
	vp_long,
	vp_ulong,

	vp_error 
};


class ArduinoPort
{
	public:
		ArduinoPort(const char* panel_id, PanelCallbackFunction CallBackPointer, HardwareSerial& comport=Serial, long baudrate = 115200);
		void Send(int channel);
		void Send(int chanel, bool value);
		void Send(int chanel, const char* message);
		void Send(int chanel, const __FlashStringHelper* message);
		void Send(int chanel, uint8_t value);
		void Send(int chanel, int16_t value);
		void Send(int chanel, uint16_t value);
		void Send(int chanel, int32_t value);
		void Send(int chanel, uint32_t value);
		void Sendf(int chanel, const char* message, ...);
		void Sendf(int chanel, const __FlashStringHelper* message, ...);
		void Receive(void);
		void Init(void);

		char*    vpr_string;
		bool     vpr_boolean;
		uint8_t  vpr_byte;
		int16_t  vpr_int;
		uint16_t vpr_uint;
		int32_t  vpr_long;
		uint32_t vpr_ulong;

	private:
		const char* _panel_id;
		PanelCallbackFunction _CallBackPointer;
		HardwareSerial* _comport;

		char SerialInpBuf[RECEIVEBUFFERSIZE];
		int  SerialInpIdx = 0;
		long _baudrate;

		int  _chanel;
		int _type;
		char* _message;
		
		bool IsAllHex(char * hexvalue);
		uint32_t Hex2Bin(char* hexvalue);
};


#endif

