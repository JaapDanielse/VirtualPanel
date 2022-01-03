VirtualPanel Release 1.4.0 (January 2022)

VirtualPanel and ArduinoPort library
* Copy the VirtualPanel\ directory to the myDocuments\Arduino\libraries\ directory
* Copy the ArduinoPort\ directory to the myDocuments\Arduino\libraries\ directory

VirtualPanel Windows executable
* The VirtualPanel.exe is a portable application. You can place it anywhere.
* Keep together with ArduinoPort.dll
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after loading an example sketch, it will connect automatically.

V1.4.0 Release notes

- Added ATmega32U4 (Leonardo / Micro / Esplora) support (DTR control). Note: Reset not available.
- Added S-MultiPanel example to demonstrate panel reset use. 
- Added $7PT, $9PT and $11PT for buttons.
- Added $11PT and $13PT for displays. 
- Bugfix: Discard cross on inputs not always avaialble in newer Windows distributions. Replaced by unicode char.
- Bugfix: Solved declaration mismatch for event in VirtualPanel.h and in ArduinoPort.h now both uint16_t.
- Bugfix: Solved warnings on PanelTest (not in release package) added workaround for use with DUE.
- Bugfix: Reset and reconnect of ESP8266 corrected. (RTS control).
- Quick reference updated.

V1.4.0 is backward compatible: the executable will operate correctly on earlier Arduino implementations, 
Recompiling Arduino implementations will compile unchanged.

VirtualPanel V1.4.0 was built with Visual studio 2019 - 16.9.5 / .NET Framework 4.7.2
Testing of the Arduino code was done using Arduino 1.8.19 IDE
