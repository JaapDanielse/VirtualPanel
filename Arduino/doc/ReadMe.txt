VirtualPanel Release 1.6.0 (February 2024)

VirtualPanel and ArduinoPort library
* Copy the VirtualPanel\ directory to the myDocuments\Arduino\libraries\ directory
* Copy the ArduinoPort\ directory to the myDocuments\Arduino\libraries\ directory

VirtualPanel Windows executable
* The VirtualPanel.exe is a portable application. You can place it anywhere.
* Keep together with ArduinoPort.dll
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.
* VirtualPanel.exe is not code certified 

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after loading an example sketch, it will connect automatically.

V1.6.0 Release notes

- Monitor panel "hold" status will be set to resume on reset.
- PanelInput(1..2), MonitorInput_(1..6) and GraphInput(1..5) sending a boolean "false" will hide the input if visible.
- Application title font(style) set to default on reset.
- MonitorLog "File" now written without extra LF
- OpenFile(1..4)  can now be used as void to open file via dialog
- Comm button (top left next to the drop down) can now also stop the comm search
- Command string property port=COMx to start with designated port.
- Moved to .NET Framework 4.8


V1.6.0 is backward compatible: the executable will operate correctly on earlier Arduino implementations, 
Recompiling Arduino implementations will compile unchanged.

VirtualPanel V1.6.0 was built with Visual studio 2022 - 17.8.3 / .NET Framework 4.8
Testing of the Arduino code was done using Arduino 2.3.1 IDE
