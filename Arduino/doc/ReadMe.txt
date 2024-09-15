VirtualPanel Release 2.0.0 (September 2024)

VirtualPanel library
* VirtualPanel can be installed as a standard Arduino .zip library.
  . In the Arduino IDE select: Sketch->Include Library->Add .ZIP Library...
  . Select VirtualPanel.zip from your download location.
!! WHEN UPDATING an earlier version of VirtualPanel delete the myDocuments\Arduino\libraries\ArduinoPort directory and it's content


VirtualPanel Windows executable
* The VirtualPanel executable (just one file) is in the VirtualPanel\exe subdirectory.
* The VirtualPanel.exe is a portable application, you can place it anywhere.
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.
* VirtualPanel.exe is not code certified. 

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after compiling and uploading an example sketch, it will connect automatically.


V2.0.0 Release notes
- Supporting SAMD (Arduino 0, - Zero, MKR) and RENESAS (UNOR4) (exclude non available program memory functions same as for SAM (DUE)).
- Beep is now asynchronous. Panel will not delay during beep.
- PanelSyncRequest allowed for PannelConnected channel to verify pannel connection.
- Harmonized data types event channel is now uint8_t everywhere, uint32 used for all 32 bit exports
- Redefine of the F() macro for SAM (DUE), SAMD (Arduino 0, - Zero, MKR) and RENESAS (UNOR4) architecture.
- Suppressed unwanted/unjust -Wformat-overflow and -Wformat (printf) warnings for SAM architecture. 
- Message log screen formatting improved by setting tab values.
- Message errors are shown in the message log.
- Message errors are indicated in the connect led with an orange color.
- Corrected send message data format in the message log format to readable form.
- The String message format is changed to include the string lenght. Incomplete strings are detected and discarded.
- The Float message format is changed from a string to an actual short float binary format in hex.
- Monitor panel "hold" status will be set to resume on reset.
- PanelInput(1..2), MonitorInput_(1..6) and GraphInput(1..5) sending a boolean "false" will hide the input if visible.
- Application title font(style) set to default on reset.
- MonitorLog "File" now written without extra LF
- OpenFile(1..4) can now be used as void to open file via dialog
- Comm button (top left next to the drop down) can now also stop the comm search
- Command string property speed={speed value} to work on a set speed must be same as Panel.begin({speed value}) in the sketch.
- Added begin(HardwareSerial, Speed) overload to support Arduino Zero Native USB port: Panel.begin(SerialUSB) (speed optional).
- Command string property port=COMx to search for the designated port only.
- ArduinoPort library combined in VirtualPanel library folder. Only the VirtualPanel folder remains.
- ArduinoPort DLL combined in VirtualPanel.exe. Only the .exe file remains.
- R-ArduinoPort-Relay sketch adapted to work with combined VP and AP libraries
- Moved to .NET Framework 4.8

V2.0.0 is NOT backward compatible: the executable will not operate correctly on earlier Arduino compiled implementations.
Recompiling Arduino and re-uploding existing implementations, however, will work unchanged.

VirtualPanel V2.0.0 was built with Visual studio 2022 - 17.8.3 / .NET Framework 4.8
Testing of the Arduino code was done using Arduino 2.3.1 IDE
