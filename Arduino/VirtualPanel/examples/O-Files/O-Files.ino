// VirtualPanel O-Files example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool MonitorStatus = false;
bool InfoStatus = false;

bool File1Open = false;
bool File2Open = false;
bool File3Open = false;



void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
        Panel.send(ApplicationName,"Files");
        Panel.send(Display_1, "Montitor shows actions");
        Panel.send(Button_3,"Moni-\ntor");
        Panel.send(Button_4,"Info");
        Panel.send(Button_6,"Create\nFile");
        Panel.send(Button_7,"Input\nFile");
        Panel.send(Button_8,"Output\nFile");
        Panel.send(Button_11,"Copy\nin-out");
        Panel.send(Button_14,"Delete\nInput");
        Panel.send(OpenFile_1, "C:\\users\\public\\"); // set a default directory (dialog overwrites)
        InfoPanel();
      break;

    case Button_3:
        MonitorStatus = !MonitorStatus;
        Panel.send(Monitor, MonitorStatus);
        break;

    case Button_4:
        InfoStatus = !InfoStatus;
        Panel.send(Info, InfoStatus);
        break;

    case Button_6:
        Panel.send(FileOpenDialogTitle_1, "Create New File");
        Panel.send(OpenFile_1, "MyNewFile.txt"); // opens file via dialog
      break;

    case Button_7:
        Panel.send(FileOpenDialogTitle_2, "Input File");
        Panel.send(OpenFile_2, "MyNewFile.txt"); // opens file directly if it exists
      break;

    case Button_8:
        Panel.send(FileOpenDialogTitle_3, "Output File");
        Panel.send(OpenFile_3, "Output.txt"); // opens file via dialog
        break;

    case Button_11:
        if(!File2Open)
        {
          Panel.send(MonitorLog, "No input file");
          break;
        }
        
        if(!File3Open)
        {
          Panel.send(MonitorLog, "No output file");
          break;
        }
        //Panel.send(ReadLineFile_2, (int32_t)1); // sets file to first line
        Panel.send(ReadLineFile_2); // request the first line (when read comes in at ReadLineFile_2:)
      break;

    case Button_14:
        if(!File2Open)
        {
          Panel.send(MonitorLog, "No input file");
          break;
        }
        File2Open = false;
        Panel.send(DeleteFile_2); 
        Panel.send(Display_1, "Input deleted");
        Panel.send(MonitorLog, "Input deleted");
      break;


    case OpenFile_1:
        // write a file 
        if(Panel.vpr_type == vp_type::vp_long) 
        {
          Panel.send(Display_1, "File written");
          File1Open = true; // flag file one open
          Panel.send(ClearFile_1); // clear content of file 1 (if any)
          
          for( long i=1; i <= 25; i++)
          {
             Panel.sendf(WriteLineFile_1, "Line %ld", i);
             Panel.sendf(MonitorLog, "Line %ld", i);
          }
          Panel.sendf(MonitorLog, "Done writing!");
        }
        else
          Panel.sendf(MonitorLog, "File not open"); // file was not opened
      break;
 
    case OpenFile_2:    
        Panel.send(Display_1, "Input File open");
        Panel.sendf(MonitorLog, "Input File open");
        File2Open = true;
        break;

    case OpenFile_3:    
        // Panel.send(ClearFile_3); // Clear content of file 3 (when omittes adds to the end of file 3)
        Panel.send(Display_1, "Output File open");
        Panel.sendf(MonitorLog, "Output File open");
        File3Open = true;
      break;
 
    case ReadLineFile_2:
        if (Panel.vpr_type == vp_type::vp_void) // check if not end of file
        {
         Panel.send(Display_1, "Copy Done!");
         Panel.send(MonitorLog, "End Of File 2"); // show in monitor
        }
        else
        {
          Panel.sendf(WriteLineFile_3, "%s", Panel.vpr_string); // write to file 3
          Panel.sendf(MonitorLog, "%s - copied!", Panel.vpr_string); // show in monitor
          Panel.send(ReadLineFile_2); // request next line form file one (when read comes in at ReadLineFile_2:)
        }
      break;
  }
}

void InfoPanel()
{
  Panel.send(InfoTitle, "Files");
  Panel.send(InfoText, "If you press \"Create file\", using a file dialog you create a file");
  Panel.send(InfoText, "and 25 lines are writen to it\n");
  Panel.send(InfoText, "\"Input File\" selects an input to copy from.");
  Panel.send(InfoText, "\"Output File\" selects an output to copy to.\n");
  Panel.send(InfoText, "If no directory or file is known a dialog is used,");
  Panel.send(InfoText, "File is opened via a dialog unless specified as forced /f\n");
  Panel.send(InfoText, "In the monitor log you see the actions.");
}
