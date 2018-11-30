// 
// 
// 

#include "VirtualPanel.h"

// VirtualPanel 

VirtualPanel::VirtualPanel(const char* panel_id, PanelCallbackFunction CallBackPointer, HardwareSerial& comport, long baudrate)
{
	_CallBackPointer = CallBackPointer;
	_panel_id = panel_id;
	_comport = &comport;
	_baudrate = baudrate;

}

void VirtualPanel::Init(void)
{
	_comport->begin(_baudrate);
//	_comport->print("[");
//	_comport->print(_panel_id);
//	_comport->println("]");
}

void VirtualPanel::Send(int chanel)
{
	char buf[4];
	sprintf(buf, "%02X%1X", chanel, vp_void);
	_comport->println(buf);
}

void VirtualPanel::Send(int chanel, boolean value)
{
	char buf[5];
	sprintf(buf, "%02X%1X%1X", chanel, vp_boolean, value);
	_comport->println(buf);
}

void VirtualPanel::Sendf(int chanel, const char* message, ...)
{
	char buf[SENDFBUFFERSIZE];
	sprintf(buf, "%02X%1X", chanel, vp_string);
	_comport->print(buf);
	va_list args;
	va_start(args, message);
	vsnprintf(buf, 80, message, args);
	va_end(args);
	_comport->println(buf);
}

void VirtualPanel::Send(int chanel, const char* message)
{
	char buf[4];
	sprintf(buf, "%02X%1X", chanel, vp_string);
	_comport->print(buf);
	_comport->println(message);
}

void VirtualPanel::Send(int chanel, byte value)
{
	char buf[6];
	sprintf(buf, "%02X%1X%02X", chanel, vp_byte, value);
	_comport->println(buf);
}

void VirtualPanel::Send(int chanel, int value)
{
	char buf[8];
	sprintf(buf, "%02X%1X%04X", chanel, vp_int, value);
	_comport->println(buf);
}

void VirtualPanel::Send(int chanel, unsigned int  value)
{
	char buf[8];
	sprintf(buf, "%02X%1X%04X", chanel, vp_uint, value);
	_comport->println(buf);
}

void VirtualPanel::Send(int chanel, long value)
{
	char buf[12];
	sprintf(buf, "%02X%1X%08lX", chanel, vp_long, value);
	_comport->println(buf);
}

void VirtualPanel::Send(int chanel, unsigned long value)
{
	char buf[12];
	sprintf(buf, "%02X%1X%08lX", chanel, vp_ulong, value);
	_comport->println(buf);
}

void VirtualPanel::Receive(void)
{
	char buf[9];
	unsigned long value;
	bool hex;
	int len;

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
				return;
			}

			strncpy(buf, SerialInpBuf, 2);
			buf[2] = 0;
			_chanel = (int)Hex2Bin(buf);

			strncpy(buf, &SerialInpBuf[2], 1);
			buf[1] = 0;
			_type = (int)Hex2Bin(buf);

			len = strlen(&SerialInpBuf[3]);
			hex = IsAllHex(&SerialInpBuf[3]) && len <= 8;
			if (hex)
				value = Hex2Bin(&SerialInpBuf[3]);

			switch (_type)
			{
			case vp_void:
				break;
			case vp_string:
				vpr_string = &SerialInpBuf[3]; break;
			case vp_boolean:
				if (hex && len == 1) { if (value == 1) vpr_boolean = true; else vpr_boolean = false;  break; }
			case vp_byte:
				if (hex && len == 2) { vpr_byte = (byte)value; break; }
			case vp_int:
				if (hex && len == 4) { vpr_int = (int)value; break; }
			case vp_uint:
				if (hex && len == 4) { vpr_uint = (unsigned int)value; break; }
			case vp_long:
				if (hex && len == 8) { vpr_long = (long)value; break; }
			case vp_ulong:
				if (hex && len == 8) { vpr_ulong = (unsigned long)value; break; }
			default:
				_type = vp_error;
				vpr_string = SerialInpBuf;
			}

			(*_CallBackPointer) (_chanel, _type);

			SerialInpIdx = 0;
		}
	}
}

bool VirtualPanel::IsAllHex(char* hexvalue)
{
	int len = strlen(hexvalue);

	for (int i = 0; i < len; i++)
	{
		if ((hexvalue[i] < 48) || (hexvalue[i] > 57 && hexvalue[i] < 65) || (hexvalue[i] > 70))
			return false;
	}
	return true;
}

unsigned long VirtualPanel::Hex2Bin(char* hexvalue)
{
	unsigned long val = 0;
	unsigned long tmp = 0;

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




