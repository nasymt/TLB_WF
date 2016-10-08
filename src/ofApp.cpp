#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // serial = new SerialCommunication();
    _serial.setup(5);
    ofSetFrameRate(60);

    ofSetVerticalSync(true);

    bSendSerialMessage = false;
    keyActive = true;
    ofBackground(50);
    ofSetLogLevel(OF_LOG_VERBOSE);

    hex_xml = new DataReaderHex();
    hex_xml->loadXml("xml/hex.xml");
    sendHex = hex_xml->sendSerial;
    delete hex_xml;
    
    sound.setup();

    config_xml = new DataReaderConfig();
    config_xml->loadXml("xml/config.xml");
    lpr_node = config_xml->lpr_node;
    lpr_channel = config_xml->lpr_channel;
    if (config_xml->auto_setup) {
        cout << "auto_setup" << endl;
//        vector<Byte> sendByte;
//        sendByte = _hex.setNode(ofToInt(lpr_node));
//        _serial.sendSerial(sendByte);
//        sendByte = _hex.setChannel(ofToInt(lpr_channel));
//        _serial.sendSerial(sendByte);
    }
    delete config_xml;

    ball_xml = new DataReaderBall();
    ball_xml->loadXml("xml/ball.xml");
    ball_num = ball_xml->ball_num;

    pad = new SelectPad();
    pad->setup(_serial);
    
    scene.setup(_serial);

    for (int i = 0; i < ball_num; i++) {
        ball.push_back(BallManagement());
        ball[i].setup(i, ball_num);
    }

    //    font.load("DIN.otf", 32);

    gui.setup();
    //    gui.add(color.setup("color",ofColor(255,0,0),ofColor(0,0),ofColor(255,255)));
    gui.add(color.setup("color", ofColor(255, 0, 0), ofColor(0), ofColor(255, 255, 255)));
    gui.add(fadeTime.setup("fadeTime", 1000, 0, 10000));
    gui.setPosition(580, 20);
}

//--------------------------------------------------------------
void ofApp::update() {
    pad->update();
    sound.update();
    if(sound.isPlaying){
        relativeTime = sound.relativeTime;
        absoluteTime = sound.absoluteTime;
        scene_name = sound.now_scene;
        
        scene.update(absoluteTime,relativeTime,scene_name);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();

    for (int i = 0; i < ball_num; i++) {
        ball[i].draw();
    }
    sound.draw();

    pad->draw();

    ofSetColor(200);
    ofDrawBitmapString("[LPR9201]", 20, 25);
    ofDrawBitmapString("node:" + lpr_node, 20, 45);
    ofDrawBitmapString("ch:" + lpr_channel, 20, 65);

    ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate()), 20, ofGetHeight() - 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == '1') {
        //        _serial.sendSerial(_hex.connect());
        pad->sendSerial(_hex.connect(),&_serial);
    }/* else if (key == '2') {
        pad->sendSerial(_hex.setChannel(ofToInt(lpr_channel)),&_serial);
    } else if (key == '3') {
        pad->sendSerial(_hex.setNode(ofToInt(lpr_node)),&_serial);
    } else if (key == '4') {
    } else if (key == '5') {
        pad->sendSerial(_hex.changeColor(color),&_serial);
    } else if (key == '6') {
        pad->sendSerial(_hex.lightoff(),&_serial);
    } else if (key == '7') {
        pad->sendSerial(_hex.setBreathMode(),&_serial);
    } else if (key == '8') {
        pad->sendSerial(_hex.setDirectAlpha(99),&_serial);
    }*/
    
    if(key == 'p'){
        if(sound.isPlaying){
            sound.pause();
        }else {
            sound.play();
        }
    }else if(key == OF_KEY_LEFT){
        sound.goToStart();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) { pad->mouseEvent(x, y); }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
