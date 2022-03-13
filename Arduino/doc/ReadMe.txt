VirtualPanel Release 1.5.0 (March 2022)

VirtualPanel and ArduinoPort library
* Copy the VirtualPanel\ directory to the myDocuments\Arduino\libraries\ directory
* Copy the ArduinoPort\ directory to the myDocuments\Arduino\libraries\ directory

VirtualPanel Windows executable
* The VirtualPanel.exe is a portable application. You can place it anywhere.
* Keep together with ArduinoPort.dll
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after loading an example sketch, it will connect automatically.

V1.5.0 Release notes

- Added $LBLUE, $DBLUE and $DPURPLE colors to enable creating a scale. N.B. Not avaialable as panel color.
- Added $8PX and $16PX to draw really fat lines circles and pixels
- Quick reference updated.

V1.5.0 is backward compatible: the executable will operate correctly on earlier Arduino implementations, 
Recompiling Arduino implementations will compile unchanged.

VirtualPanel V1.5.0 was built with Visual studio 2019 - 16.9.5 / .NET Framework 4.7.2
Testing of the Arduino code was done using Arduino 1.8.19 IDE
