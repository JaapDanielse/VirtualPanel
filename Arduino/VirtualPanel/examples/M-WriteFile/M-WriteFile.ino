// VirtualPanel M-WriteFile example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool FileOpen = false;

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
      Panel.send(ApplicationName,"Write File");
      Panel.send(Display_1, "Montitor shows actions");
      Panel.send(Button_3,"Write\nFile");
      Panel.send(Button_4,"Delete\nFile");
      Panel.send(Monitor, (bool)true);
      SetDefaultPath();
      break;

    case Button_3:
      Panel.send(OpenFile_1, "*.tst"); // open a file in sketch directory with .tst extention using dialog
      break;

    case Button_4:
      if(!FileOpen) break;
      Panel.send(DeleteFile_1); // delete the already opened file
      Panel.send(Display_1, "File Deleted"); // show in display
      break;

    case OpenFile_1:
      if(Panel.vpr_type == vp_type::vp_long) // long indicates file open  (ontains line count) 
        WriteFile(); // write the file 
      else
        Panel.sendf(MonitorLog, "File not open"); // file was not opened
      break;
    
    default: break;
  }
}


//--------------------------------------------------------------
void WriteFile()
{
  FileOpen = true;

  Panel.send(Display_1, "File Open"); // show in display
  Panel.send(ClearFile_1); // clear content of the file(if any)
  
  for( long i=1; i <= 25; i++)
  {
     Panel.sendf(WriteLineFile_1, "Line %ld", i); // write a line
     Panel.sendf(MonitorLog, "Line %ld", i); // show in monitor log
  }
  Panel.sendf(MonitorLog, "Done writing!"); // show in monitor log
  Panel.send(Display_1, "File Written"); // show in display
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
}
