/*
  ArduinoPort.cpp 
  MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

  ArduinoPort is a libray to provide a simple, controlled, 	va_start(args, message);
	event communication between an Arduino and a PC based application
	under C# using the ArduinoPort.dll.
  	
	V1.2.0	14-7-2020  
*/

#include "ArduinoPort.h"

// ArduinoPort 
ArduinoPort::ArduinoPort(const char* panel_id, PanelCallbackFunction CallBackPointer, Stream& comport)
{
	_CallBackPointer = CallBackPointer;
	_panel_id = panel_id;
	_comport = &comport;
}

void ArduinoPort::send(int channel)
{
	char buf[4];
	sprintf(buf, "%02X%1X", channel, (uint8_t)vp_type::vp_void);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, bool value)
{
	char buf[5];
	sprintf(buf, "%02X%1X%1X", channel, (uint8_t)vp_type::vp_boolean, value);
	_comport->println(buf);
}

#ifndef ARDUINO_ARCH_SAM
void ArduinoPort::sendf(int channel, const __FlashStringHelper* message, ...)
{
	char buf[SENDFBUFFERSIZE];
	sprintf(buf, "%02X%1X", channel, (uint8_t)vp_type::vp_string);
	_comport->print(buf);
	
	va_list args;
	va_start(args, message);
	
	vsnprintf_P(buf, SENDFBUFFERSIZE, (const char*)message, args);
	
	va_end(args);
	_comport->println(buf);
}
#endif

void ArduinoPort::sendf(int channel, const char* message, ...)
{
	char buf[SENDFBUFFERSIZE];
	sprintf(buf, "%02X%1X", channel, (uint8_t)vp_type::vp_string);
	_comport->print(buf);
	va_list args;
	va_start(args, message);
	vsnprintf(buf, SENDFBUFFERSIZE, message, args);
	va_end(args);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, const char* message)
{
	char buf[4];
	sprintf(buf, "%02X%1X", channel, vp_type::vp_string);
	_comport->print(buf);
	_comport->println(message);
}

void ArduinoPort::send(int channel, const __FlashStringHelper* message)
{
	char buf[4];
	sprintf(buf, "%02X%1X", channel, vp_type::vp_string);
	_comport->print(buf);
	_comport->println(message);
}

void ArduinoPort::send(int channel, uint8_t value)
{
	char buf[6];
	sprintf(buf, "%02X%1X%02X", channel, vp_type::vp_byte, value);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, int16_t value)
{
	char buf[8];
	sprintf(buf, "%02X%1X%04X", channel, vp_type::vp_int, (uint16_t)value);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, uint16_t value)
{
	char buf[8];
	sprintf(buf, "%02X%1X%04X", channel, vp_type::vp_uint, value);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, int32_t value)
{
	char buf[12];
	sprintf(buf, "%02X%1X%08lX", channel, vp_type::vp_long, (unsigned long)value);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, uint32_t value)
{
	char buf[12];
	sprintf(buf, "%02X%1X%08lX", channel, vp_type::vp_ulong, (unsigned long)value);
	_comport->println(buf);
}

void ArduinoPort::send(int channel, float value)
{
	char buf[12];
	sprintf(buf, "%02X%1X", channel, vp_type::vp_float);
	_comport->print(buf);
	_comport->println(value,4);
}

bool ArduinoPort::delay(uint16_t delaytime, bool doReceive)
{
	uint32_t ResumeTime = millis() + delaytime;
	bool DataReceived = false;
	
	while (ResumeTime > millis())
	{
		if (_comport->available())
		{
			DataReceived = true;
    		if(doReceive)
				receive();
  		}
	}
  return DataReceived;
}

bool ArduinoPort::receive(int SyncChannel)
{
	char buf[9];
	uint32_t value=0;
	bool hex;
	int16_t len;

	while (_comport->available())
	{
		SerialInpBuf[SerialInpIdx++] = _comport->read();
		if (SerialInpIdx == RECEIVEBUFFERSIZE)
		{
			SerialInpIdx = 0;
		}

		if (SerialInpBuf[SerialInpIdx - 1] == '\r') SerialInpIdx--;

		if (SerialInpBuf[SerialInpIdx - 1] == '\n')
		{
			SerialInpBuf[SerialInpIdx - 1] = 0; // make a string

			if (!strcmp("ID", SerialInpBuf))
			{
				_comport->println(_panel_id);
   			SerialInpIdx = 0; //discard input
				return false;
			}

			strncpy(buf, SerialInpBuf, 2);
			buf[2] = 0;
			int16_t channel = Hex2Bin(buf);

			strncpy(buf, &SerialInpBuf[2], 1);
			buf[1] = 0;

			vp_type type = static_cast<vp_type>(Hex2Bin(buf));

			len = strlen(&SerialInpBuf[3]);
			hex = IsAllHex(&SerialInpBuf[3]) && len <= 8;
			if (hex)
				value = Hex2Bin(&SerialInpBuf[3]);
			   
      vpr_type = type;
			
			switch (type)
			{
				case vp_type::vp_void:
					break;
				case vp_type::vp_string:
					vpr_string = &SerialInpBuf[3]; break;
				case vp_type::vp_boolean:
					if (hex && len == 1) { vpr_boolean = (value == 1) ? true : false; } break;
				case vp_type::vp_byte:
					if (hex && len == 2) { vpr_byte = (uint8_t)value; } break;
				case vp_type::vp_int:
					if (hex && len == 4) { vpr_int = (int16_t)value; } break;
				case vp_type::vp_uint:
					if (hex && len == 4) { vpr_uint = (uint16_t)value; } break;
				case vp_type::vp_long:
					if (hex && len == 8) { vpr_long = (int32_t)value; } break;
				case vp_type::vp_ulong:
					if (hex && len == 8) { vpr_ulong = (uint32_t)value; } break;
				case vp_type::vp_float:
  					vpr_float = atof(&SerialInpBuf[3]); break;
					
				default:
					vpr_string = SerialInpBuf;
					break;
			}
			
			SerialInpIdx = 0;
			if(SyncChannel == channel) return true;
			_CallBackPointer(channel);
		}
	}
	return false;
}

bool ArduinoPort::IsAllHex(char* hexvalue)
{
	int len = strlen(hexvalue);

	for (int i = 0; i < len; i++)
	{
		if ((hexvalue[i] < 48) || (hexvalue[i] > 57 && hexvalue[i] < 65) || (hexvalue[i] > 70))
			return false;
	}
	return true;
}

uint32_t ArduinoPort::Hex2Bin(char* hexvalue)
{
	uint32_t val = 0;
	uint32_t tmp = 0;

	int len = strlen(hexvalue);

	for (int i = 0; i < len; i++)
	{
		tmp = 1;
		tmp = tmp << (4 * (len - 1 - i));
		if (hexvalue[i] <= 57)
			val += tmp * (hexvalue[i] - 48);
		else
			val += tmp * (hexvalue[i] - 55);
	}

	return val;
}




