#pragma once

#include "ofMain.h"
#include "DataReaderConfig.hpp"
#include "DataReaderBall.hpp"
#include "hex.hpp"
#include "ballManagement.hpp"
#include "padManagement.hpp"
#include "ofxGui.h"
#include "serialCommunication.hpp"
#include "soundPlayer.hpp"
#include "sceneManagement.hpp"
#include "ballBaseScene.hpp"

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
    DataReaderConfig *config_xml;
    DataReaderBall *ball_xml;
    BallBaseScene *baseScene;
    
    PadManagement *pad;
    vector<BallManagement> ball;
    SoundPlayer sound;
    ofxPanel gui;
    ofxColorSlider color;
    ofxIntSlider fadeTime;
    SerialCommunication _serial;
    SceneManagement scene;
    
    
    
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
    int ball_num;
    
    int absoluteTime;
    int relativeTime;
    string scene_name;
};
