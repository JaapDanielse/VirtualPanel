// VirtualPanel S-MultiPanel example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

// This example shows how to use multiple panels in one application.

#include "VirtualPanel.h"

//---------------------------------------------------------------------------
void setup() 
{
  Panel.begin(); // init panel
}

//---------------------------------------------------------------------------
void loop() 
{
  Panel.receive(); // receive from panel
}
