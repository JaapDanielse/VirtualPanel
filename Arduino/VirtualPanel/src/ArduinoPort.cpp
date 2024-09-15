/*
  ArduinoPort.cpp 
  MIT Licence - Copyright (c) 2024 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

  ArduinoPort is a libray to provide a simple, controlled, 	va_start(args, message);
	event communication between an Arduino and a PC based application
	under C# using the ArduinoPort.dll.
  	
	V2.0.0b4	16-08-2024  
*/

#include "ArduinoPort.h"
#include <stdarg.h>

// ArduinoPort 
ArduinoPort::ArduinoPort(const char* panel_id, PanelCallbackFunction CallBackPointer, Stream& comport)
{
	_CallBackPointer = CallBackPointer;
	_panel_id = panel_id;
	_comport = &comport;
}

#pragma GCC diagnostic push // save warning level
#ifndef ARDUINO_ARCH_SAM // next pragma's not valid for SAM arch.
  #pragma GCC diagnostic ignored "-Wformat-overflow" // temp. ignore format-overflow warnings
  #pragma GCC diagnostic ignored "-Wformat" // temp. ignore format warnings
#endif

void ArduinoPort::send(uint8_t channel)
{
	char buf[4];
	sprintf(buf, "%02X%1X", channel, (uint8_t)vp_type::vp_void);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, bool value)
{
	char buf[5];
	sprintf(buf, "%02X%1X%1X", channel, (uint8_t)vp_type::vp_boolean, value);
	_comport->println(buf);
}

#if !defined(ARDUINO_ARCH_SAM) && !defined(ARDUINO_ARCH_SAMD) && !defined(ARDUINO_ARCH_RENESAS)
void ArduinoPort::sendf(uint8_t channel, const __FlashStringHelper* message, ...)
{
	char hbuf[6];
	char buf[SENDFBUFFERSIZE];
	va_list args;
	va_start(args, message);
	vsnprintf_P(buf, SENDFBUFFERSIZE, (const char*)message, args);
	va_end(args);
	sprintf(hbuf, "%02X%1X%02X", channel, (uint8_t)vp_type::vp_string, (uint8_t)strlen(buf));
	_comport->print(hbuf);
	_comport->println(buf);
}
#endif

void ArduinoPort::sendf(uint8_t channel, const char* message, ...)
{
	char hbuf[6];
	char buf[SENDFBUFFERSIZE];
	va_list args;
	va_start(args, message);
	vsnprintf(buf, SENDFBUFFERSIZE, message, args);
	va_end(args);
	sprintf(hbuf, "%02X%1X%02X", channel, (uint8_t)vp_type::vp_string, (uint8_t)strlen(buf));
	_comport->print(hbuf);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, const char* message)
{
	char buf[6];
	sprintf(buf, "%02X%1X%02X", channel, vp_type::vp_string, (uint8_t)strlen(message));
	_comport->print(buf);
	_comport->println(message);
}

void ArduinoPort::send(uint8_t channel, const __FlashStringHelper* message)
{
	char buf[6];
	sprintf(buf, "%02X%1X%02X", channel, vp_type::vp_string, (uint8_t)FSHLength(message));
	_comport->print(buf);
	_comport->println(message);
}

void ArduinoPort::send(uint8_t channel, uint8_t value)
{
	char buf[6];
	sprintf(buf, "%02X%1X%02X", channel, vp_type::vp_byte, value);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, int16_t value)
{
	char buf[8];
	sprintf(buf, "%02X%1X%04X", channel, vp_type::vp_int, (uint16_t)value);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, uint16_t value)
{
	char buf[8];
	sprintf(buf, "%02X%1X%04X", channel, vp_type::vp_uint, value);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, int32_t value)
{
	char buf[12];
	sprintf(buf, "%02X%1X%08lX", channel, vp_type::vp_long, (uint32_t)value);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, uint32_t value)
{
	char buf[12];
	sprintf(buf, "%02X%1X%08lX", channel, vp_type::vp_ulong, value);
	_comport->println(buf);
}

void ArduinoPort::send(uint8_t channel, float value)
{
	char buf[12];
	uint32_t FloatAsUint32;
	
	memcpy(&FloatAsUint32, &value, sizeof FloatAsUint32);
	sprintf(buf, "%02X%1X%08lX", channel, vp_type::vp_float, (uint32_t) FloatAsUint32);
	_comport->println(buf);
}

#pragma GCC diagnostic pop // restore warning level

bool ArduinoPort::delay(uint16_t delaytime, bool doReceive)
{
	uint32_t ResumeTime = millis() + delaytime;
	bool DataReceived = false;
	
	do
	{
		if (_comport->available())
		{
			DataReceived = true;
    		if(doReceive)
				receive();
  		}
	}while (ResumeTime > millis());
	
  return DataReceived;
}

bool ArduinoPort::receive(int16_t SyncChannel)
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
			uint8_t channel = Hex2Bin(buf);

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
				{
					strncpy(buf, &SerialInpBuf[3], 2);
					buf[2] = 0;
					uint16_t SentStrLen = Hex2Bin(buf);
					uint16_t RcvStrLen = strlen(&SerialInpBuf[5]);
					if(SentStrLen != RcvStrLen) type = vp_error;
					vpr_string = &SerialInpBuf[5]; 
					break;
				}
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
					if (hex && len == 8) { memcpy(&vpr_float, &value, sizeof value); } break;
				default:
					vpr_string = SerialInpBuf;
					break;
			}
			
			SerialInpIdx = 0;
			if(SyncChannel == (int16_t) channel) return true;
			_CallBackPointer(channel);
		}
	}
	return false;
}

bool ArduinoPort::IsAllHex(char* hexvalue)
{
	uint16_t len = strlen(hexvalue);

	for (uint16_t i = 0; i < len; i++)
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

	uint16_t len = strlen(hexvalue);

	for (uint16_t i = 0; i < len; i++)
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


uint16_t ArduinoPort::FSHLength(const __FlashStringHelper* fshString)
{
  PGM_P p = reinterpret_cast<PGM_P>(fshString);
  uint16_t n = 0;
  while (1) 
  {
    byte c = pgm_read_byte(p++);
    if (c == 0) break;
    n++;
  }
  return n;
}

