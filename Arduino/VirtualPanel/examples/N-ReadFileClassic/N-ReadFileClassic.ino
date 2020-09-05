// VirtualPanel O-ReadFileClassic example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"


//--------------------------------------------------------------
void setup() 
{
  Panel.begin(); // init port and protocol
}


//--------------------------------------------------------------
void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}


//--------------------------------------------------------------
void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"Read File Classic");
      Panel.send(Display_1, "Montitor shows actions");
      Panel.send(Button_3,"Read\nFile");
      Panel.send(Monitor, (bool)true);
      SetDefaultPath();
      break;

    case Button_3:
      Panel.send(OpenFile_1, "HitchhikersGuide.txt"); // open the file "TheHobbit.txt" via dialog but with name and extention
      break;

    case OpenFile_1: // file open event
      if(Panel.vpr_type == vp_type::vp_long) // long indicates file open  (ontains line count) 
      {
        Panel.send(MonitorLog, "$CLEAR"); // clear the monitor log
        Panel.send(ReadLineFile_1); // read the first line
      }
      else
        Panel.sendf(MonitorLog, "File not open"); // file was not opened
      break;

    case ReadLineFile_1: 
      // using Classic read all read operations (for this file) come via the same event case
      // when using file sections this is complex. Then consider using PanelSyncRequest()
      
      if (Panel.vpr_type == vp_type::vp_string) // string: line read, void: end of file.
      {
        Panel.send(MonitorLog, Panel.vpr_string);  // write to monitor 
        Panel.send(ReadLineFile_1); // request the next line 
      }
      break;

    default: break;
  }
}


//--------------------------------------------------------------
void SetDefaultPath()
{
  char SketchPath[] = __FILE__; // get a string with the sketch file path (any file of the sketch)
  if(strrchr(SketchPath, '\\') != NULL)
  {
    *(strrchr(SketchPath, '\\')+1)=0; // truncate to a path
    Panel.send(OpenFile_1, SketchPath); // set the path to the sketch directory
  }
  else
  {
      Panel.send(MonitorLog, "Sketch path not found.");
      Panel.send(MonitorLog, "Please navigate to sketch path");
      Panel.send(MonitorLog, "in the file open dialog.");
  }
}
