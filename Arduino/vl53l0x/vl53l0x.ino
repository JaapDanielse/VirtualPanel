#include "Adafruit_VL53L0X.h"
#include "PanelOne.h"

Adafruit_VL53L0X TofSens = Adafruit_VL53L0X();

int MeasuredDistance = 0;

void setup() 
{
  Panel.Init(); // init pannel protocol and serial port
  TofSens.begin();
}


void loop() 
{

  VL53L0X_RangingMeasurementData_t measure;
  
  Panel.Receive(); // handle pannel data coming in
  
  TofSens.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) 
    MeasuredDistance = measure.RangeMilliMeter;
 // else
   // MeasuredDistance = 0;
  delay(100);
}


void PanelCallback(int event, int type) 
{ // callback is called when a message is received from the panel 
  // only channel and type are available as parameters. Pannel data in public vars defined by the library 
  
  switch (event) 
  {
    case PanelConnected: 
    { // initialize panel layout
      Panel.Send(ApplicationName,"TOF Sensor"); // set the application name
      Panel.Send(DynamicDisplay, 100); // enable dynamic display requests
      Panel.Send(GraphGrid, 15);

      break; 
    }

    case DynamicDisplay: // dynamic display request
    {
      int i;
      Panel.Sendf(Display_1,"%d", MeasuredDistance); // Output value to display

      i = map( MeasuredDistance, 0, 1500, 0, 255);
      Panel.Send(GraphValue_1,(byte)i);
      

      
      break;
    }
  }
}


