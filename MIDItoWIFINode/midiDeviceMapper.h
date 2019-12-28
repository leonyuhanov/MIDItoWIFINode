#ifndef midiDeviceMapper_h
#define midiDeviceMapper_h

typedef struct midiNode{ 
  unsigned short int _nodeID;
  char* _deviceName;
  char _midiChanel;
  char _controllID;
  char _value;
  float _scaledValue;
  midiNode* nextNode; 
}MIDINODE;

class midiDeviceMapper
{
  public:
    midiDeviceMapper();
    
    void addNode(char* deviceName, char midiChanel, char controllID, char value);
    
    MIDINODE* findNode(unsigned short int nodeID);
    MIDINODE* findNode(char* deviceName);
    MIDINODE* findNode(char controllID);
    
    short int getControllID(char* deviceName);
    short int getMidiChanel(char* deviceName);
    short int getValue(char* deviceName);
    short int getScaledValue(char controllID, char originaValue);
   
    void setNode(char* deviceName, short int midiChanel=-1, short int controllID=-1, short int value=-1);
    void setNode(unsigned short int nodeID, short int midiChanel=-1, short int controllID=-1, short int value=-1);
    
    unsigned short int totalNodes;
    MIDINODE* startPointer;
    
  private:
    float _maxValue;
    
};
#endif
