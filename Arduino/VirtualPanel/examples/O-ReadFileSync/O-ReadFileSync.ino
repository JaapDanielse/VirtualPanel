// VirtualPanel N-ReadFileSync example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool BlockEvents = false;

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
  if(BlockEvents) return;
  
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"Read File Synchronous");
      Panel.send(Display_1, "Montitor shows actions");
      Panel.send(Button_3,"Read\nFile");
      Panel.send(Monitor, (bool)true);
      SetDefaultPath();
      break;

    case Button_3:
      Panel.send(OpenFile_1, "TheHobbit.txt/f"); // open the file "TheHobbit.txt" directly in sketch directory 
      break;

    case OpenFile_1: // file open event
      if(Panel.vpr_type == vp_type::vp_long) // long indicates file open  (ontains line count) 
        ReadFile(); // read the file 
      else
        Panel.sendf(MonitorLog, "File not open"); // file was not opened
      break;

    default: break;
  }
}


//--------------------------------------------------------------
void ReadFile()
{
  // Synchronous request is a bit of a hack. If during a read another event takes too much time a timeout will occur.
  // This can be handled by blocking events during read (in this example) or by handling the timeout. See documentation
  // SynchronousRequest cannot be active twice. This will also cause an error.

  Panel.send(MonitorLog, "$CLEAR"); // clear the monitor log

  BlockEvents = true; // set flag to prevent event handling in PanelCallback
  while(PanelSyncRequest(ReadLineFile_1) && Panel.vpr_type == vp_type::vp_string) // read a line and check result
  {
    Panel.send(MonitorLog, Panel.vpr_string);  // write to monitor
  }
  BlockEvents = false; // clear flag to enable event handling again.
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
