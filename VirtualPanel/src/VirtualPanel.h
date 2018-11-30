/*
Name:		VirtualPanel.h

V0.1    9-11-2015 JpD
Original version

*/

#ifndef _VIRTUALPANEL_h
#define _VIRTUALPANEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SENDFBUFFERSIZE 40
#define RECEIVEBUFFERSIZE 30

extern "C"
{
	typedef void(*PanelCallbackFunction) (int command, int type);
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


class VirtualPanel
{
public:
	VirtualPanel(const char* panel_id, PanelCallbackFunction CallBackPointer, HardwareSerial& comport=Serial, long baudrate = 115200);
	void Send(int channel);
	void Send(int chanel, boolean value);
	void Send(int chanel, const char* message);
	void Send(int chanel, byte value);
	void Send(int chanel, int value);
	void Send(int chanel, unsigned int value);
	void Send(int chanel, long value);
	void Send(int chanel, unsigned long value);
	void Sendf(int chanel, const char* message, ...);
	void Receive(void);
	void Init(void);

	char*         vpr_string;
	bool          vpr_boolean;
	byte          vpr_byte;
	int           vpr_int;
	unsigned int  vpr_uint;
	long          vpr_long;
	unsigned long vpr_ulong;

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
	unsigned long Hex2Bin(char* hexvalue);
};


#endif

