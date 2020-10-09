VirtualPanel Release 1.2.1

VirtualPanel and ArduinoPort library
* Copy the VirtualPanel\ directory to the myDocuments\Arduino\libraries\ directory
* Copy the ArduinoPort\ directory to the myDocuments\Arduino\libraries\ directory

VirtualPanel Windows executable
* The VirtualPanel.exe is a portable application. You can place it anywhere.
* Keep together with ArduinoPort.dll
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after loading an example sketch, it will connect automatically.

V1.2.1 Release notes

- Bugfix: Files_2, 3 and 4 now also create file (if not exist) after dialog.
- Display_3 and 4 slightly longer.
- Inputs now (also) respond to Enter as send and Esc as discard.

V1.2.0 is backward compatible: the executable will operate correctly on earlier Arduino implementations, 
Recompiling Arduino implementations will compile unchanged.

VirtualPanel V1.2.1 was built with Visual studio 2019 / .NET Framework 4.7.2
Testing of the Arduino code was done using Arduino 1.8.13 IDE
