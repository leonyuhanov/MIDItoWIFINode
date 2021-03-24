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
    
    short int addNode(char* deviceName, char midiChanel, char controllID, char value);
    
    MIDINODE* findNode(unsigned short int nodeID);
    MIDINODE* findNode(char* deviceName);
    MIDINODE* findNode(char controllID);
    MIDINODE* findNode(char midiChanel, char controllID);
    MIDINODE* findNode(char* deviceName, char midiChanel, char controllID);
    
    short int getControllID(char* deviceName);
    short int getmidiChanel(char* deviceName);
    short int getValue(char* deviceName);
    short int getScaledValue(char controllID, char originaValue);
   
    void setNode(char* deviceName, short int midiChanel=-1, short int controllID=-1, short int value=-1);
    void setNode(unsigned short int nodeID, short int midiChanel=-1, short int controllID=-1, short int value=-1);
    void setNode(char midiChanel, char controllID, char value);
    
    unsigned short int totalNodes;
    MIDINODE* startPointer;
    
	  const char noteCount=12;
	  const char octaveCount=11;
	  const char* defaultNoteList[12] = {"C ","C#","D ","D#","E ","F ","F#","G ","G#","A ","A#","B "};
	  const char* defaultOctaveList[11] = {"-1","0 ","1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 "};
    
  private:
    float _maxValue;
    
};
#endif
