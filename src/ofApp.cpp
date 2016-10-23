#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    _serial.setup(5);
    ofSetFrameRate(60);

    ofSetVerticalSync(true);

    bSendSerialMessage = false;
    keyActive = true;
    ofBackground(50);
    ofSetLogLevel(OF_LOG_VERBOSE);

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

    //    pad = new PadManagement();
    //    serial.setup(_serial);

    scene.setup();

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
    //    serial.update();
    sound.update();
    for (int i = 0; i < ball_num; i++) {
        ball[i].update();
    }
    relativeTime = sound.relativeTime;
    absoluteTime = sound.absoluteTime;
    scene_name = sound.now_scene;
    scene.update(absoluteTime, relativeTime, scene_name, &_serial, &ball, sound.isPlaying);
}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();

    for (int i = 0; i < ball_num; i++) {
        ball[i].draw();
    }
    sound.draw();
    scene.draw();

    ofSetColor(200);
    ofDrawBitmapString("[LPR9201]", 20, 25);
    ofDrawBitmapString("node:" + lpr_node, 20, 45);
    ofDrawBitmapString("ch:" + lpr_channel, 20, 65);

    ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate()), 20, ofGetHeight() - 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 't') {
        _serial.sendSerial(_hex.connect());
    } else if (key == 'y') {
        _serial.sendSerial(_hex.setChannel(ofToInt(lpr_channel)));
    } else if (key == 'u') {
        _serial.sendSerial(_hex.setNode(ofToInt(lpr_node)));
    } else if (key == 'i') {
        _serial.sendSerial(_hex.changeColor(color, 5000));
    } else if (key == 'o') {
        _serial.sendSerial(_hex.lightoff());
    } else if (key == 'p') {
        _serial.sendSerial(_hex.setDirectAlpha(10));
    }else if(key == 'g'){
        _serial.sendSerial(_hex.sensorThreshold(0));
    }
    /*else if (key == 'a') {
        _serial.sendSerial(_hex.changeGroupColor(1, ofColor(0, 255, 255), 1000));
    } else if (key == 's') {
        _serial.sendSerial(_hex.changeGroupColor(2, ofColor(0, 255, 255), 1000));
    } else if (key == 'q') {
        _serial.sendSerial(_hex.uartOverrunResend());
        _serial.sendSerial(_hex.sensorThreshold(0));
    } else if (key == 'w') {
        vector<bool> colorIndex;
        for (int i = 0; i < 16; i++) {
            colorIndex.push_back(false);
        }
        _serial.sendSerial(_hex.selectRandomColor(colorIndex));
    } else if (key == 'e') {
        _serial.sendSerial(_hex.randomColor(1000));
    }*/
    

    if (key == '9') {
//        _serial.sendSerial(_hex.setGroupId(1));
        _serial.sendSerial(_hex.changeGroupColor(1, ofColor(0, 255, 255), 1000));

    } else if (key == '0') {
        _serial.sendSerial(_hex.changeGroupColor(2, ofColor(0, 255, 255), 1000));
//        _serial.sendSerial(_hex.setGroupId(2));
    }

    if (key == 32) {
        if (sound.isPlaying) {
            for (int i = 0; i < scene.isStart.size(); i++) {
                scene.isStart[i] = false;
            }
            sound.pause();
        } else {
            sound.play();
        }
    } else if (key == OF_KEY_DOWN) {
        sound.goToStart();
    } else if (key == OF_KEY_LEFT) {
        sound.adjust_position -= 20;
    } else if (key == OF_KEY_RIGHT) {
        sound.adjust_position += 20;
    }
    
    scene.keyEvent(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
