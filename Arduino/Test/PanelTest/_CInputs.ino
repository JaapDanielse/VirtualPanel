
  //static byte     MyByte = 0;
  static int16_t  MyInt = 0;
  static int32_t  MyLong = 0;
  //static float    MyFloat = 0;
  static uint16_t MyUInt = 0;
  static uint32_t MyULong = 0;

  static int16_t  MonValue_1 = 100;
  static int16_t  MonValue_2 = 200;
  static int16_t  MonValue_3 = 300;
  static int16_t  MonValue_4 = 400;
  static int16_t  MonValue_5 = 500;
  //static int16_t  MonValue_6 = 600;
  

void InputsCallback(vp_channel event)
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      InputsInit();
      break; 

    case Button_4:
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;

    case Button_5:
      Infomode = !Infomode;
      Panel.send(Info,Infomode);
      break;

    case Button_6:
      Monmode = !Monmode;
      Panel.send(Monitor,Monmode);
      break;

    case Display_1: // display has been double clicked 
      Panel.send(MinPanelInput_1, (int16_t)-500); // 
      Panel.send(MaxPanelInput_1, (int16_t)500); // 
      Panel.send(PanelInputLabel_1, F("One (Integer):")); // 
      Panel.send(PanelInput_1, MyInt); // 
    break;

    case Display_2: // display has been double clicked 
      Panel.send(MinPanelInput_2, (int16_t)0); // 
      Panel.send(MaxPanelInput_2, (int16_t)10000); // 
      Panel.send(PanelInputLabel_2, F("Two (Uns. Int):")); // 
      Panel.send(PanelInput_2, MyUInt); // 
    break;

    case Display_3: // display has been double clicked 
      Panel.send(MinPanelInput_1, (int32_t)-100000); // 
      Panel.send(MaxPanelInput_1, (int32_t)100000); // 
      Panel.send(PanelInputLabel_1, F("Three (Long):")); // 
      Panel.send(PanelInput_1, MyLong); // 
    break;

    case Display_4: // display has been double clicked 
      Panel.send(MinPanelInput_2, (uint32_t)0); // 
      Panel.send(MaxPanelInput_2, (uint32_t)500000); // 
      Panel.send(PanelInputLabel_2, F("Four (Uns. Long):")); // 
      Panel.send(PanelInput_2, MyULong); // 
    break;

   case MonitorField_3: // display has been double clicked 
     Panel.send(MinMonitorInput_3, (int16_t)0); // 
     Panel.send(MaxMonitorInput_3, (int16_t)1000); // 
     Panel.send(MonitorInput_3, MonValue_3); // 
     Panel.send(MonitorInputLabel_3, F("Mon Field 3:")); // 
     break;

   case MonitorField_4: // display has been double clicked 
     Panel.send(MinMonitorInput_4, (int16_t)0); // 
     Panel.send(MaxMonitorInput_4, (int16_t)1000); // 
     Panel.send(MonitorInput_4, MonValue_4); // 
     Panel.send(MonitorInputLabel_4, F("Mon Field 4:")); // 
     break;

   case MonitorField_5: // display has been double clicked 
     Panel.send(MinMonitorInput_5, (int16_t)0); // 
     Panel.send(MaxMonitorInput_5, (int16_t)1000); // 
     Panel.send(MonitorInput_5, MonValue_5); // 
     Panel.send(MonitorInputLabel_5, F("Mon Field 5:")); // 
     break;
    
   case MonitorField_6: // display has been double clicked 
     Panel.send(MinMonitorInput_6, (int16_t)2); // 
     Panel.send(MaxMonitorInput_6, (int16_t)10); // 
     Panel.send(MonitorInput_6, "test"); // 
     Panel.send(MonitorInputLabel_6, F("Mon Field 6 Text:")); // 
     break;

    case PanelInput_1:
      if (Panel.vpr_type == vp_type::vp_void)
          Panel.send(MonitorLog, F("Panel Input 1/3: discarded"));
      if (Panel.vpr_type == vp_type::vp_int)
      {
        MyInt = Panel.vpr_int;
        Panel.sendf(MonitorLog, F("Panel Input 1: %d"), MyInt);
      }
      if (Panel.vpr_type == vp_type::vp_long)
      {
        MyLong = Panel.vpr_long;
        Panel.sendf(MonitorLog, F("Panel Input 3: %ld"), MyLong);
      }
    break;

    case PanelInput_2:
      if (Panel.vpr_type == vp_type::vp_void)
          Panel.send(MonitorLog, F("Panel Input 2/4: discarded"));
      if (Panel.vpr_type == vp_type::vp_uint)
      {
        MyUInt = Panel.vpr_uint;
        Panel.sendf(MonitorLog, F("Panel Input 2: %d"), MyUInt);
      }
      if (Panel.vpr_type == vp_type::vp_ulong)
      {
        MyULong = Panel.vpr_ulong;
        Panel.sendf(MonitorLog, F("Panel Input 4: %ld"),MyULong);
      }
      break;


    case MonitorInput_1:
      if (Panel.vpr_type == vp_type::vp_void)
      {
        Panel.send(MonitorLog, F("Input 1: discarded"));
        Panel.send(MonitorInput_1, MonValue_1);
      }
      else
      {
        MonValue_1 = Panel.vpr_int;
        Panel.sendf(MonitorLog, F("Input 1: %d"), MonValue_1);
      }
      break;

    case MonitorInput_2:
      if (Panel.vpr_type == vp_type::vp_void)
      {
        Panel.send(MonitorLog, F("Input 2: discarded"));
        Panel.send(MonitorInput_2, MonValue_2);
      }
      else
      {
        MonValue_2 = Panel.vpr_int;
        Panel.sendf(MonitorLog, F("Input 2: %d"), MonValue_2);
      }
      break;


    case MonitorInput_3:
      if (Panel.vpr_type == vp_type::vp_void)
        Panel.send(MonitorLog, F("Input 3: discarded"));
      else
      {
        MonValue_3 = Panel.vpr_int;
        Panel.send(MonitorField_3, MonValue_3);
        Panel.sendf(MonitorLog, F("Input 3: %d"), MonValue_3);
      }
      break;

    case MonitorInput_4:
      if (Panel.vpr_type == vp_type::vp_void) 
        Panel.send(MonitorLog, F("Input 4: discarded"));
      else
      {
        MonValue_4 = Panel.vpr_int;
        Panel.send(MonitorField_4, MonValue_4);
        Panel.sendf(MonitorLog, F("Input 4: %d"), MonValue_4);
      }
      break;

    case MonitorInput_5:
      if (Panel.vpr_type == vp_type::vp_void) 
        Panel.send(MonitorLog, F("Input 5: discarded"));
      else
      {
        MonValue_5 = Panel.vpr_int;
        Panel.send(MonitorField_5, MonValue_5);
        Panel.sendf(MonitorLog, F("Input 5: %d"), MonValue_5);
      }
      break;

    case MonitorInput_6:
      if (Panel.vpr_type == vp_type::vp_void) 
        Panel.send(MonitorLog, F("Input 6: discarded"));
      else
      {
        Panel.send(MonitorField_6, Panel.vpr_string );
        Panel.sendf(MonitorLog, F("Input 6: %s"), Panel.vpr_string );
      }
      break;
      
    default: break;
  }

  if ( event != Button_4) 
  {
    Panel.sendf(Display_1, F("One: %d"), MyInt);
    Panel.sendf(Display_2, F("Two: %u"), MyUInt);
    Panel.sendf(Display_3, F("Three: %d"), MyLong);
    Panel.sendf(Display_4, F("Four: %ld"), MyULong);
    
  }
}


void InputsInit()
{
  Panel.send(ApplicationName,F("PanelTest - Inputs")); // set the application name
  Panel.send(PanelColor,"$GRAY"); // set the application name


  Panel.send(Button_4,  F("next\npanel"));
  Panel.send(Button_5,  F("info"));
  Panel.send(Button_6,  F("moni\ntor"));


  Panel.send(MonitorInput_1, (bool)true); // 
  Panel.send(MinMonitorInput_1, (int16_t)0); // 
  Panel.send(MaxMonitorInput_1, (int16_t)1000); // 
  Panel.send(MonitorInputLabel_1, F("Mon Field 1:")); // 
  Panel.send(MonitorInput_1, MonValue_1); // 
  
  Panel.send(MonitorInput_2, (bool)true); // 
  Panel.send(MinMonitorInput_2, (int16_t)0); // 
  Panel.send(MaxMonitorInput_2, (int16_t)1000); // 
  Panel.send(MonitorInputLabel_2, F("Mon Field 2:")); // 
  Panel.send(MonitorInput_2, MonValue_2); // 
  
  WriteInfo();
  Monmode = true;
  Panel.send(Monitor, Monmode); // 

  Panel.send(MonitorLog, "bool");
  Panel.send(MonitorLog, (bool)false);
  Panel.send(MonitorLog, (bool)true);
  Panel.send(MonitorLog, "byte");
  Panel.send(MonitorLog, (byte)0 );
  Panel.send(MonitorLog, (byte)255 );
  Panel.send(MonitorLog, "int (int16_t)");
  Panel.send(MonitorLog, (int16_t)100 );
  Panel.send(MonitorLog, (int16_t)-32768 );
  Panel.send(MonitorLog, (int16_t) 32767 );
  Panel.send(MonitorLog, "unsigned int (uint16_t)");
  Panel.send(MonitorLog, (uint16_t)0 );
  Panel.send(MonitorLog, (uint16_t)65535 );
  Panel.send(MonitorLog, "long (int32_t)");
  Panel.send(MonitorLog, (int32_t)-2147483648 );
  Panel.send(MonitorLog, (int32_t)2147483647 );
  Panel.send(MonitorLog, "unsigned long (uint32_t)");
  Panel.send(MonitorLog, (uint32_t)0 );
  Panel.send(MonitorLog, (uint32_t)4294967295 );

  Panel.send(MonitorField_3, MonValue_3 );
  Panel.send(MonitorField_4, MonValue_4  );
  Panel.send(MonitorField_5, MonValue_5  );
  Panel.send(MonitorField_6, F("test"));

}
