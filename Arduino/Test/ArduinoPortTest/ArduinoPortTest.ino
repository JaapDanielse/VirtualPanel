/*
 TestPanel.ino
 Test application for the Arduino VirtualPanel library

 V0.1    31-10-2015 JpD
 Original version

*/

#include "ArduinoPort.h"


enum vp_chanel
{
	command_0,
	command_1,
	command_2,
	command_3,
	command_4,
	command_5,
	command_6,
	command_7,
	command_8,
	command_9
};

void PanelCallback(int event, int type); // you need to define the callback function first

ArduinoPort MyPanel("Test", PanelCallback, Serial, 115200);


//-----------------------------------------------------------------------------------------------
// Callback

void PanelCallback(int chanel, int type)
{

	switch (chanel)
	{
  	case command_0:
  	{
  		MyPanel.Send(command_0, "CallBack(0)!");
  		switch (type)
  		{
  		case vp_void: {MyPanel.Send(chanel); break; }
  		case vp_string: {MyPanel.Send(chanel, MyPanel.vpr_string); break;  }
  		case vp_boolean: {MyPanel.Send(chanel, MyPanel.vpr_boolean); break;  }
  		case vp_byte: {MyPanel.Send(chanel, MyPanel.vpr_byte); break;  }
  		case vp_int: {MyPanel.Send(chanel, MyPanel.vpr_int); break;  }
  		case vp_uint: {MyPanel.Send(chanel, MyPanel.vpr_uint); break;  }
  		case vp_long: {MyPanel.Send(chanel, MyPanel.vpr_long); break;  }
      case vp_ulong: {MyPanel.Send(chanel, MyPanel.vpr_ulong);  break; }
      case vp_float: {MyPanel.Send(chanel, MyPanel.vpr_float);  break; }
  		case vp_error: {MyPanel.Sendf(chanel, "Error %s", MyPanel.vpr_string);  break; }
  		}
  
  
  		break;
  	}
  	case command_1:
  	{
  		MyPanel.Send(command_0, "CallBack(1)!");
  		break;
  	}
	}
}


//-----------------------------------------------------------------------------------------------
// Initialisation

void setup()
{
	MyPanel.Init();

	MyPanel.Send(command_0);
	MyPanel.Send(command_1, "test");
	MyPanel.Sendf(command_1, "test %d *c", 15);
	MyPanel.Send(command_2, true);
	MyPanel.Send(command_3, (byte)255);
	MyPanel.Send(command_4, (int)32767);
	MyPanel.Send(command_4, (int)-1);
	MyPanel.Send(command_5, (unsigned int)65535);
	MyPanel.Send(command_6, (long)2147483647);
	MyPanel.Send(command_6, (long)-15);
  MyPanel.Send(command_7, (unsigned long)4294967295);
  MyPanel.Send(command_8, (float)1234.5678);

	MyPanel.Send(command_2, false);
	MyPanel.Send(command_3, (byte)100);
	MyPanel.Send(command_4, (int)100);
	MyPanel.Send(command_5, (unsigned int)100);
	MyPanel.Send(command_6, (long)-1);
	MyPanel.Send(command_7, (unsigned long)100);



}

//-----------------------------------------------------------------------------------------------
// Main Loop

void loop()
{
	MyPanel.Receive();

}
/* end module */
