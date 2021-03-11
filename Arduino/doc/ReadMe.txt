VirtualPanel Release 1.3.0

VirtualPanel and ArduinoPort library
* Copy the VirtualPanel\ directory to the myDocuments\Arduino\libraries\ directory
* Copy the ArduinoPort\ directory to the myDocuments\Arduino\libraries\ directory

VirtualPanel Windows executable
* The VirtualPanel.exe is a portable application. You can place it anywhere.
* Keep together with ArduinoPort.dll
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after loading an example sketch, it will connect automatically.

V1.3.0 Release notes

- Button_1 .. 17 can be set to repeat.
- Bugfix: Input edit color reset on new input value.

V1.3.0 is backward compatible: the executable will operate correctly on earlier Arduino implementations, 
Recompiling Arduino implementations will compile unchanged.

VirtualPanel V1.3.0 was built with Visual studio 2019 / .NET Framework 4.7.2
Testing of the Arduino code was done using Arduino 1.8.13 IDE
