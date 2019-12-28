/*
	Coded for the ESP8266 Wemos D1 Mini Module
	PINOUT:
	MIDI Data Receive Pin	D1
	MIDI Data TX Pin (not used but defined for Software Serial Lib)	D2
	
	
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "midiDeviceMapper.h"
#include <SoftwareSerial.h>

byte midiSerialData[3];
int dataAvail=0;
byte readyToWrite=0;
byte dataIn;
//The midiDeviceMapper class is designed for easy management of individual midi controlls but is not nessesary
midiDeviceMapper midiMap;
SoftwareSerial swSer;
byte rxPin = D1, txPin = D2;

//Network Stuff
//Please enter corect details for wifi details
const char * ssid = "NETWORKNAME";
const char * password = "NETWORKKEY";
WiFiUDP Udp;
//UDP port to TX on
const unsigned int udpTXPort = 1000;
//IP Address of receiver node
IPAddress serverAddress(192,168,1,250);
const byte packetSize=3;
byte dataToSend[packetSize] = {0, 0, 0};


void setup()
{
  //Init main serial port for debug mesages
  Serial.begin(115200);
  Serial.println("\r\n\r\n");

  //Eable WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
        delay(100);
        Serial.print(".");
  }
  Serial.printf("\r\nMIDI Module ONLINE\r\nCurrent Ip Address:\t");
  Serial.print(WiFi.localIP());
  Serial.print("\r\n");
  
  //Set up TX and RX pins for SoftwareSerial (probbaly not required)
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
 
  //Init the SOftware Serial port to recive data from MIDI device at 31250kbaud 
  swSer.begin(31250, SWSERIAL_8N1, rxPin, txPin, false);

  /*
  
  Add MIDI mappings for each MIDI controll you want to read and trasmit:
	midiMap.addNode("Friendly String Name", MIDI CHanel(NOT REALLY USED), MIDI CONTROLL ID, MIDI VALUE from 0 to 127);
  You can access data from each mapping via:
	midiMap.getValue(char* deviceName) eg midiMap.getValue("Knob81") which will return the controls value 0 to 127
	or to get a scaled value (Float 0 to 1) scaled against any number you send
	midiMap.getScaledValue((char)81, 100) if the value of this knob was read as 63.5 the scaled value 0.5 will be multiplied by 100 and will return 50
  You can also directly access any element via:
    midiMap.findNode((char)81)->_value (note you need to check for NULL before this)
  */
  midiMap.addNode("Knob81", 0, 81, 0);
  midiMap.addNode("Knob82", 0, 82, 0);
  midiMap.addNode("Knob83", 0, 83, 0);
  midiMap.addNode("Knob84", 0, 84, 0);
  midiMap.addNode("Knob85", 0, 85, 0);
  midiMap.addNode("Knob86", 0, 86, 0);
  midiMap.addNode("Knob87", 0, 87, 0);
  midiMap.addNode("Knob88", 0, 88, 0);
  midiMap.addNode("Knob89", 0, 89, 0);
  midiMap.addNode("Knob90", 0, 90, 0);
  midiMap.addNode("Knob91", 0, 91, 0);
  midiMap.addNode("Knob92", 0, 92, 0);
  midiMap.addNode("Knob93", 0, 93, 0);
  midiMap.addNode("Knob94", 0, 94, 0);
  midiMap.addNode("Knob95", 0, 95, 0);
  midiMap.addNode("Knob96", 0, 96, 0);
  midiMap.addNode("Knob97", 0, 97, 0);
  midiMap.addNode("Knob98", 0, 98, 0);
  midiMap.addNode("Knob99", 0, 99, 0);
  midiMap.addNode("Knob100", 0, 100, 0);
  midiMap.addNode("Knob101", 0, 101, 0);
  midiMap.addNode("Knob102", 0, 102, 0);
  midiMap.addNode("Knob103", 0, 103, 0);
  midiMap.addNode("Knob104", 0, 104, 0);
}

void loop()
{
  dataAvail = swSer.available();
  if( dataAvail )
  {
    dataIn = swSer.read();
    if(dataIn==176)
    {
      readyToWrite++;
    }
    else if(dataIn!=176 && readyToWrite==1)
    {
      midiSerialData[readyToWrite] = dataIn;
      readyToWrite++;
      while(readyToWrite!=3)
      {
        dataAvail = swSer.available();
        if( dataAvail )
        {
          midiSerialData[readyToWrite] = swSer.read();
          readyToWrite++;
        }
      }
    }
    else if(dataIn!=176 && readyToWrite==0)
    {
      readyToWrite++;
      midiSerialData[readyToWrite] = dataIn;
      readyToWrite++;
      while(readyToWrite!=3)
      {
        dataAvail = swSer.available();
        if( dataAvail )
        {
          midiSerialData[readyToWrite] = swSer.read();
          readyToWrite++;
        }
      }
    }

  }
  
  if(readyToWrite==3)
  {
    //Set data received for this controll node
	midiMap.setNode(midiSerialData[1], midiSerialData[0], midiSerialData[1], midiSerialData[2]);
	//Comment this out if you dont want any debug mesages
    Serial.printf("DEVICE ID[\t%d\t]\tVALUE[\t%d\t]\t[", midiSerialData[1], midiSerialData[2]);
    Serial.print(midiMap.findNode((char)midiSerialData[1])->_deviceName);
    Serial.printf("]\r\n");
    //Copy data reeceived from midi into UDP packet block
	memcpy(dataToSend, midiSerialData, packetSize);
	//Send data via UDP
    txData();
    //Clear serial recieve block because why not
	midiSerialData[0] = 0;
    midiSerialData[1] = 0;
    midiSerialData[2] = 0;
	//Reset readyToWrite block to 0
    readyToWrite=0;
  }
  //Yield or the esp will crash
  yield();
}

void txData()
{
  Udp.beginPacket(serverAddress, udpTXPort);
  Udp.write(dataToSend, packetSize);
  Udp.endPacket();
}
