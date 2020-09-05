// VirtualPanel P-FileDraw example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

// Example similar to K-Point-Click but now writing and reading a drawing to and from a file.
// This example is to demonstrate reading a file using PanelSyncRequest() (see ReadFile())
// During this read other panel functions are blocked to prevent timeouts using a simple flag.

#include "VirtualPanel.h"

const char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE","$PURPLE","$BROWN","$PINK","$GRAY"};
const int MaxColorNum = 9;
int ColorNum = 0;

const char * PenSize[] = {"$1PX","$2PX","$3PX","$4PX"};
const int MaxPenSizeNum = 3;
int PenSizeNum = 0;

bool FileOpen = false;
int32_t LinePos = 0;
bool BlockPanel = false;


//---------------------------------------------------------------------------
void setup() 
{
  Panel.begin(); // init port and protocol
}

//---------------------------------------------------------------------------
void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}

//---------------------------------------------------------------------------
void PanelCallback(vp_channel event) 
{ 
  if(BlockPanel) return;

  switch (event) 
  {
    case PanelConnected: InitPanel(); break; 
    case Button_3: Panel.send(OpenFile_1, ""); break;
    case Button_4: ClearFile(); break;
    case GraphButton_1: ColorSelect(); break;
    case GraphButton_2: PenSizeSelect(); break;
    case GraphButton_3: StartNewLine(); break;
    case GraphButton_4: DeletePoint(); break;
    case GraphClick: DrawLine(); break;
    case GraphRightClick: StartNewLine(); break;
    case OpenFile_1: ReadFile(); break;
    default: break;
  }
}

//---------------------------------------------------------------------------
void ColorSelect()
{
  if (++ColorNum > MaxColorNum) ColorNum=0;
  Panel.send(GraphButton_1,  Color[ColorNum]);
  Panel.send(GraphDrawPixel, Color[ColorNum]);
  Panel.send(GraphDrawLine,  Color[ColorNum]);
  if(FileOpen)
  {
    Panel.send(WriteLineFile_1, "CS");
    LinePos++;
  }
}

//---------------------------------------------------------------------------
void PenSizeSelect()
{
  if (++PenSizeNum > MaxPenSizeNum) PenSizeNum=0;
  Panel.send(GraphButton_2, PenSize[PenSizeNum]);
  Panel.send(GraphDrawPixel,PenSize[PenSizeNum]);
  Panel.send(GraphDrawLine, PenSize[PenSizeNum]);
  if(FileOpen)
  {
    Panel.send(WriteLineFile_1, "PS");
    LinePos++;
  }
}

//---------------------------------------------------------------------------
void StartNewLine()
{
  Panel.send(GraphDrawLine); // Start a new line 
  Panel.sendf(Display_2, "New Line");
  if(FileOpen)
  {
    Panel.send(WriteLineFile_1, "NL");
    LinePos++;
  }
}

//---------------------------------------------------------------------------
void DrawLine()
{
  if(FileOpen)
  {
    Panel.send(GraphDrawPixel, Panel.vpr_uint);
    Panel.send(GraphDrawLine, Panel.vpr_uint);
    Panel.sendf(WriteLineFile_1, "LP X%03d Y%03d", highByte(Panel.vpr_uint), lowByte(Panel.vpr_uint));
    Panel.sendf(Display_2, "X%03d Y%03d", highByte(Panel.vpr_uint), lowByte(Panel.vpr_uint));
    LinePos++;
  }
  else
    Panel.send(Display_1, "File Not open!");
}

//---------------------------------------------------------------------------
void ClearFile()
{
  if(!FileOpen) return;
  Panel.send(ClearFile_1);
  ReadFile();
}

//---------------------------------------------------------------------------
void ReadFile()
{
  int X = 0;
  int Y = 0;

  if(!FileOpen && Panel.vpr_type != vp_type::vp_long) return; // file open cancelled

  FileOpen = false;
  LinePos = 1;
  Panel.send(ReadLineFile_1, LinePos);
  Panel.sendf(Display_1, "File Open");
  Panel.send(Graph, "$CLEAR");
  ColorNum = MaxColorNum;
  ColorSelect();
  PenSizeNum=MaxPenSizeNum;
  PenSizeSelect();
  
  BlockPanel = true;
  while(PanelSyncRequest(ReadLineFile_1) && Panel.vpr_type == vp_type::vp_string)
  {
    Panel.send(MonitorLog, Panel.vpr_string); 
    if      (!strcmp(Panel.vpr_string,"")) LinePos--; 
    else if (!strcmp(Panel.vpr_string,"CS")) ColorSelect();
    else if (!strcmp(Panel.vpr_string,"PS")) PenSizeSelect();
    else if (!strcmp(Panel.vpr_string,"NL")) StartNewLine();
    else 
    {
      sscanf(Panel.vpr_string, "LP X%d Y%d", &X, &Y);
      Panel.send(GraphDrawLine, _Point((byte)X,(byte)Y));
    }
    LinePos++;
  }
  Panel.send(WriteLineFile_1, LinePos);
  BlockPanel = false;
  FileOpen = true;
}

//---------------------------------------------------------------------------
void DeletePoint()
{
  if(!FileOpen) return;
  Panel.send(WriteLineFile_1, --LinePos);
  Panel.send(WriteLineFile_1, "");
  ReadFile();
}

//---------------------------------------------------------------------------
void InitPanel()
{
  Panel.send(ApplicationName,"File Draw");
  Panel.send(Button_3, "Open\nFile");
  Panel.send(Button_4, "Clear\nFile");
  Panel.send(GraphButton_1, "■");
  Panel.send(GraphButton_1, Color[ColorNum]);
  Panel.send(GraphButton_2, PenSize[PenSizeNum]);
  Panel.send(GraphButton_3, "New\nLine");
  Panel.send(GraphButton_4, "Delete\nentry");
  Panel.send(Graph, (bool)true);
  SetDefaultPath();
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
      Panel.send(GraphCaption_1, "Sketch path not found.\nNavigate there for example.\nOr open new.");
  }
}
