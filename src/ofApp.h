#pragma once

#include "ofMain.h"
#include "DataReaderHex.hpp"
#include "DataReaderConfig.hpp"
#include "hex.hpp"

class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    //ofTrueTypeFont font;

    bool bSendSerialMessage;  // a flag for sending serial
    int readByte;

    bool keyActive;
    string sendMessage;
    stringstream ss;
    ofSerial serial;
    
    vector<Byte> sendHex;

   private:
    DataReaderHex *hex_xml;
    DataReaderConfig *config_xml;
    
    
    Hex _hex;
    bool bConnect;
    bool bRandomColor;
    bool bReadProfile;
    bool bSetNode;
    bool bSetChannel;
    bool bOff;
    bool bSetBreathMode;
    
    string lpr_node;
    string lpr_channel;
    bool edit_lprNode;
    bool edit_lprCh;
};
