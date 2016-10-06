#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    hex_xml = new DataReaderHex();
    hex_xml->loadXml("xml/hex.xml");
    sendHex = hex_xml->sendSerial;
    delete hex_xml;
    
    config_xml = new DataReaderConfig();
    config_xml->loadXml("xml/config.xml");
    lpr_node = config_xml->lpr_node;
    lpr_channel = config_xml->lpr_channel;
    delete config_xml;

    ofSetVerticalSync(true);

    bSendSerialMessage = false;
    keyActive = true;
    ofBackground(50);
    ofSetLogLevel(OF_LOG_VERBOSE);

//    font.load("DIN.otf", 32);
    

    serial.listDevices();
    vector<ofSerialDeviceInfo> deviceList = serial.getDeviceList();

    int baud = 9600;
    serial.setup(0, baud);  // open the first device
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {
    if (bSendSerialMessage) {
        // serial.writeByte(unsigned char );
        // ex) '165' = 0xA5
        //     serial.writeByte(165);


        //        Byte val[] = {0x5A,0xA5,0x0B,0x00,0xF4};
        Byte val0[] = {0x5A, 0xA5, 0x02,0x02, 0x03, 0x21, 0xDD};
        
        vector<Byte> sendByte;
        if(bConnect){
            sendByte = _hex.connect();
            bConnect = false;
            cout << "[connect]" << endl;
        }else if(bRandomColor){
            sendByte = _hex.randomColor();
            bRandomColor = false;
            cout << "[random color]" << endl;
        }else if(bReadProfile){
            sendByte = _hex.readProfile();
            bReadProfile = false;
            cout << "[read profile]" << endl;
        }else if(bSetNode){
            sendByte = _hex.setNode(6098);
            bSetNode = false;
            cout << "[set node 6098]" << endl;
        }else if(bSetChannel){
            sendByte = _hex.setChannel(33);
            bSetChannel = false;
            cout << "[set channel 33]" << endl;
        }else if(bOff){
            sendByte = _hex.lightoff();
            bOff = false;
        }else if(bSetBreathMode){
            sendByte = _hex.setBreathMode();
            bSetBreathMode = false;
        }
        
        for(int i=0;i<sendByte.size();i++){
            serial.writeByte(sendByte[i]);
        }
        Byte checksum = _hex.checkSum(sendByte);
        serial.writeByte(checksum);
        
        cout << " send serial " << endl;

        ss.clear();
        while (serial.available() > 0) {
            readByte = serial.readByte();
            cout << "read:" << hex << readByte << endl;
        }

        bSendSerialMessage = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(200);
    
    stringstream ss;
    ss<<"[LPR9201] node:"<<lpr_node<<"  ch:"<<lpr_channel;
    ofDrawBitmapString(ss.str(), 50, 25);
//    ofDrawBitmapString(lpr_node,50,20);
//    ofDrawBitmapString(lpr_channel,150,20);
    
    
//    string str[]={"CONNECT","SET CHANNEL","SET NODE","READ PROFILE","RANDOM COLOR","OFF","SET BREATH MODE"};
//    for(int i=0;i<7;i++){
//        if(i==0&& bConnect)ofSetColor()
//        font.drawString(str[i],50,50+i*50);
//    };
    
    
    

    //font.drawString("FPS:" + ofToString(ofGetFrameRate()), 50, ofGetHeight() - 50);
    ofDrawBitmapString("fps:"+ofToString(ofGetFrameRate()),50,ofGetHeight()-30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
//    if (key == OF_KEY_DOWN) {
//        keyActive = true;
//    }
//    if (keyActive) {
//        if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) {
//            if (sendMessage.size()) {
//                sendMessage.pop_back();
//            }
//        } else {
//            sendMessage.push_back(key);
//        }
//    }

    if (key == OF_KEY_RETURN) {
        bSendSerialMessage = true;
        sendMessage.clear();
    }
    
    if(key == '1'){
        bConnect = true;
        bSendSerialMessage = true;
    }else if(key == '2'){
        bSetChannel = true;
        bSendSerialMessage = true;
    }else if(key == '3'){
        bSetNode = true;
        bSendSerialMessage = true;
    }else if(key == '4'){
        bReadProfile = true;
        bSendSerialMessage = true;
    }else if(key == '5'){
        bRandomColor = true;
        bSendSerialMessage = true;
    }else if(key == '6'){
        bOff = true;
        bSendSerialMessage = true;
    }else if(key == '7'){
        bSetBreathMode = true;
        bSendSerialMessage = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) { keyActive = true; }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
