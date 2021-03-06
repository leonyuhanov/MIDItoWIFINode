#include "midiDeviceMapper.h"
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

midiDeviceMapper::midiDeviceMapper()
{
  startPointer = NULL;
  totalNodes = 0;
  _maxValue = 127;
}

short int midiDeviceMapper::addNode(char* deviceName, char midiChanel, char controllID, char value)
{
  MIDINODE* nodePointer;
  //if(findNode(deviceName)==NULL)
  if( findNode(deviceName, midiChanel, controllID)==NULL )
  {
    nodePointer = (MIDINODE*) malloc(sizeof(MIDINODE));
    nodePointer->_nodeID = totalNodes+1;
    nodePointer->_deviceName = new char[strlen(deviceName)+1];
    memcpy(nodePointer->_deviceName, deviceName,strlen(deviceName)+1);
    nodePointer->_midiChanel = midiChanel;
    nodePointer->_controllID = controllID;
    nodePointer->_value = value;
    nodePointer->_scaledValue = ((float)value/_maxValue);
    nodePointer->nextNode = startPointer;
    startPointer = nodePointer;
    totalNodes++;
    return 1;
  }
  return 2;
}


MIDINODE* midiDeviceMapper::findNode(unsigned short int nodeID)
{
  MIDINODE* nodePointer = startPointer;
  while(nodePointer != NULL)
  { 
      if(nodePointer->_nodeID==nodeID)
      {
        return nodePointer;
      }
      nodePointer = nodePointer->nextNode; 
   } 
   return NULL;
}

MIDINODE* midiDeviceMapper::findNode(char* deviceName)
{
  MIDINODE* nodePointer = startPointer;
  while(nodePointer != NULL)
  { 
      if(strcmp(nodePointer->_deviceName, deviceName)==0)
      {
        return nodePointer;
      }
      nodePointer = nodePointer->nextNode; 
   } 
   return NULL;
}

MIDINODE* midiDeviceMapper::findNode(char controllID)
{
  MIDINODE* nodePointer = startPointer;
  while(nodePointer != NULL)
  { 
      if(nodePointer->_controllID==controllID)
      {
        return nodePointer;
      }
      nodePointer = nodePointer->nextNode; 
   } 
   return NULL;
}

MIDINODE* midiDeviceMapper::findNode(char midiChanel, char controllID)
{
  MIDINODE* nodePointer = startPointer;
  while(nodePointer != NULL)
  { 
      if(nodePointer->_midiChanel==midiChanel && nodePointer->_controllID==controllID)
      {
        return nodePointer;
      }
      nodePointer = nodePointer->nextNode; 
   } 
   return NULL;
}

MIDINODE* midiDeviceMapper::findNode(char* deviceName, char midiChanel, char controllID)
{
  MIDINODE* nodePointer = startPointer;
  while(nodePointer != NULL)
  { 
      if( strcmp(nodePointer->_deviceName, deviceName)==0 && nodePointer->_midiChanel==midiChanel && nodePointer->_controllID==controllID )
      {
        return nodePointer;
      }
      nodePointer = nodePointer->nextNode; 
   } 
   return NULL;
}   

void midiDeviceMapper::setNode(char* deviceName, short int midiChanel, short int controllID, short int value)
{
  MIDINODE* nodePointer = findNode(deviceName);
  if(nodePointer!=NULL)
  {
    if(midiChanel!=-1)
    {
      nodePointer->_midiChanel = midiChanel;
    }
    if(controllID!=-1)
    {
      nodePointer->_controllID = controllID;
    }
    if(value!=-1)
    {
      nodePointer->_value = value;
      nodePointer->_scaledValue=((float)nodePointer->_value) / _maxValue;
    }
  }
}

void midiDeviceMapper::setNode(unsigned short int nodeID, short int midiChanel, short int controllID, short int value)
{
  MIDINODE* nodePointer = findNode((char)nodeID);
  if(nodePointer!=NULL)
  {
    if(midiChanel!=-1)
    {
      nodePointer->_midiChanel = midiChanel;
    }
    if(controllID!=-1)
    {
      nodePointer->_controllID = controllID;
    }
    if(value!=-1)
    {
      nodePointer->_value = value;
      nodePointer->_scaledValue = ((float)nodePointer->_value) / _maxValue;
    }
  }
}

void midiDeviceMapper::setNode(char midiChanel, char controllID, char value)
{
  MIDINODE* nodePointer = findNode(midiChanel, controllID);
  if(nodePointer!=NULL)
  {
    nodePointer->_value = value;
    nodePointer->_scaledValue = ((float)nodePointer->_value) / _maxValue;
  }
}

short int midiDeviceMapper::getControllID(char* deviceName)
{
  MIDINODE* nodePointer = findNode(deviceName);
  if(nodePointer!=NULL)
  {
    return nodePointer->_controllID;
  }
  else
  {
    return -1;
  }
}

short int midiDeviceMapper::getmidiChanel(char* deviceName)
{
  MIDINODE* nodePointer = findNode(deviceName);
  if(nodePointer!=NULL)
  {
    return nodePointer->_midiChanel;
  }
  else
  {
    return -1;
  }
}
short int midiDeviceMapper::getValue(char* deviceName)
{
  MIDINODE* nodePointer = findNode(deviceName);
  if(nodePointer!=NULL)
  {
    return nodePointer->_value;
  }
  else
  {
    return -1;
  }
}
short int midiDeviceMapper::getScaledValue(char controllID, char originaValue)
{
  MIDINODE* nodePointer = findNode(controllID);
  if(nodePointer!=NULL)
  {
    return nodePointer->_scaledValue * ((float)originaValue);
  }
  else
  {
    return -1;
  }
}
