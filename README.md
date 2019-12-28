# MIDItoWIFINode
Receive MIDI Serial data from a hardware MIDI device and Transmit over WIFI with en ESP8266

Curtesy of Sparkfuns MIDI guide https://learn.sparkfun.com/tutorials/midi-tutorial/all

This is the MIDI OUT port of the Bheringer BCR2000 (I Have only tested this on this model, TYou may need to adjust the code for any other device as the data format may be diferent)

<img src="https://github.com/leonyuhanov/MIDItoWIFINode/blob/master/midi-labeled.png" width="400" />

* PIN 4 is the DATA OUT pin that connects into D1
* PIN 5 connects to +5v of the ESP8266 module
* PIN 2 conects to GND of the ESP8266 module

