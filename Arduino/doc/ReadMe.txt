VirtualPanel Release 1.1.0

VirtualPanel and ArduinoPort library
* Copy the VirtualPanel\ directory to the myDocuments\Arduino\libraries\ directory
* Copy the ArduinoPort\ directory to the myDocuments\Arduino\libraries\ directory

VirtualPanel Windows executable
* The VirtualPanel.exe is a portable application. You can place it anywhere.
* Keep together with ArduinoPort.dll
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after loading an example sketch, it will connect automatically.


V1.1.0 Release notes 

- Added File-IO, allow reading and writing files on the PC.
- Added PanelColor channel, set color of the pannel collor bars to differentiate experiments. 
- Added Inputs on Graph Labels, allow to use inputs on the graph labels similar to the inputs on the monitor labels.
- Input handling improved, input colors change when editing, on discard old value is reset.
- Added $SMALL for Buttons. 
- Added GraphDrawCircle channel and _Circle and _VCircle functions allowing to draw circles and circle sections.
- Added _FString() overload with user buffer param. This is needed when more float values are used in one string.
- Added additonal examples, improved existing examples 

- Made auxillary windows (Monitor, Graph etc.) keep their relative positions when moving the main window.
- Made $BIG for buttons bigger.
- Slider operation for values higher than 1110 corrected.
- Fixed connection hangup problem when existing com port or bluetooth port is present.
- Info Panel now handles unicode characters.
- Setting graph label invisible also makes color bar invisible.
- Corrected string length setting on Monitor inputs.

- QuickReference (VirtualPanel\extras) is revised correcting errors and updated to include the added functionality.

V1.1.0 is backward compatible: the executable will operate correctly on earlier Arduino implementations, 
Recompiling Arduino implementations will compile unchanged.

VirtualPanel V1.1.0 was built with Visual studio 2019 / .NET Framework 4.7.2
Testing of the Arduino code was done using Arduino 1.8.12 IDE
