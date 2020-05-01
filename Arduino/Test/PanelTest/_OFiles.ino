bool File1Open = false;
bool File2Open = false;

void FilesCallback(vp_channel event)
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
        Panel.send(ApplicationName,"Files");
        Panel.send(Button_4,"Next\nPanel");
        Panel.send(Button_6,"Create\nFile");
        Panel.send(Button_7,"Copy\nFile");
        Panel.send(OpenFile_1, "C:\\users\\public\\"); // set a default directory (dialog overwrites)
        Panel.send(Monitor, true);
      break;

    case Button_4:
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;

    case Button_6:
        Panel.send(FileOpenDialogTitle_1, "Create New File");
        Panel.send(OpenFile_1, "MyNewFile.txt"); // name and extention specified. 
      break;

    case Button_7:
        if(File1Open)
        {
          Panel.send(FileOpenDialogTitle_2, "Copy Destination");
          Panel.send(OpenFile_2, "MyCopyFile.txt"); // name and extention specified. Same directory
        }
        else
        {
          Panel.send(MonitorLog, "Nothing to copy from");
        }
      break;

    case OpenFile_1:
        // write a file 
        if(Panel.vpr_type == vp_type::vp_long) 
        {
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
        Panel.send(ClearFile_2); // Clear content of file 2
        Panel.send(ReadLineFile_1, (int32_t)1); // reset file 1 to line 1 (first line)
        Panel.send(ReadLineFile_1); // request the first line (when read comes in at ReadLineFile_1:)
      break;
 
    case ReadLineFile_1:
        if (Panel.vpr_type == vp_type::vp_void) // check if not end of file
        {
          Panel.send(MonitorLog, "End Of File"); // show in monitor
        }
        else
        {
          Panel.sendf(WriteLineFile_2, "%s - copied!", Panel.vpr_string); // write to file 2
          Panel.sendf(MonitorLog, "%s - copied!", Panel.vpr_string); // show in monitor
          Panel.send(ReadLineFile_1); // request next line form file one (when read comes in at ReadLineFile_1:)
        }
      break;
  }
}
