VirtualPanel Release 2.0.1 (October 2024)

VirtualPanel library
* VirtualPanel can be installed as a standard Arduino .zip library.
  . In the Arduino IDE select: Sketch->Include Library->Add .ZIP Library...
  . Select VirtualPanel.zip from your download location.
!! WHEN UPDATING a version of VirtualPanel before 2.0.0 cdelete the myDocuments\Arduino\libraries\ArduinoPort directory and it's content


VirtualPanel Windows executable
* The VirtualPanel executable (just one file) is in the VirtualPanel\exe subdirectory.
* The VirtualPanel.exe is a portable application, you can place it anywhere.
* To add to the Start menu right click VirtualPanel.exe and select Pin to Start.
* VirtualPanel.exe is not code certified. 

See examples at: myDocuments\Arduino\libraries\VirtualPanel\examples
If you activate the VirtualPanel.exe after compiling and uploading an example sketch, it will connect automatically.


V2.0.1 Release notes
- Corrected grey background on button_13 to light color.

V2.0.1 is backward compatible with 2.0.0: The executable will operate correctly on V2.0.0 Arduino compiled implementations.
Recompiling Arduino implementations from before 2.0.1 and re-uploding, will work unchanged.

VirtualPanel V2.0.1 was built with Visual studio 2022 - 17.8.3 / .NET Framework 4.8
Testing of the Arduino code was done using Arduino 2.3.1 IDE
