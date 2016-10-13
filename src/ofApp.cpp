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
    pad->update();
    sound.update();
    for (int i = 0; i < ball_num; i++) {
        ball[i].update();
    }
    if (sound.isPlaying) {
        relativeTime = sound.relativeTime;
        absoluteTime = sound.absoluteTime;
        scene_name = sound.now_scene;

        scene.update(absoluteTime, relativeTime, scene_name, &_serial, &ball);
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
    if (key == 'z') {
        pad->sendSerial(_hex.connect(), &_serial);
    } else if (key == 'x') {
        pad->sendSerial(_hex.setChannel(ofToInt(lpr_channel)), &_serial);
    } else if (key == 'c') {
        pad->sendSerial(_hex.setNode(ofToInt(lpr_node)), &_serial);
    } else if (key == 'v') {
    } else if (key == 'b') {
        pad->sendSerial(_hex.changeColor(color, 5000), &_serial);
    } else if (key == 'n') {
        pad->sendSerial(_hex.lightoff(), &_serial);
    } else if (key == 'm') {
        pad->sendSerial(_hex.setDirectAlpha(100), &_serial);
    } else if (key == 'a') {
        pad->sendSerial(_hex.changeGroupColor(1, ofColor(0, 255, 255), 1000), &_serial);
    } else if (key == 's') {
        pad->sendSerial(_hex.changeGroupColor(2, ofColor(0, 255, 255), 1000), &_serial);
    } else if (key == 'q') {
        pad->sendSerial(_hex.uartOverrunResend(), &_serial);
    } else if (key == 'w') {
        vector<bool> colorIndex;
        for (int i = 0; i < 16; i++) {
            colorIndex.push_back(false);
        }
        pad->sendSerial(_hex.selectRandomColor(colorIndex), &_serial);
    } else if (key == 'e') {
        pad->sendSerial(_hex.randomColor(1000), &_serial);
    }

    if (key == '1') {
        pad->sendSerial(_hex.setGroupId(1), &_serial);
    } else if (key == '2') {
        pad->sendSerial(_hex.setGroupId(2), &_serial);
    } else if (key == '3') {
        pad->sendSerial(_hex.setGroupId(3), &_serial);
    } else if (key == '4') {
        pad->sendSerial(_hex.setGroupId(4), &_serial);
    } else if (key == '5') {
        pad->sendSerial(_hex.setGroupId(5), &_serial);
    } else if (key == '6') {
        pad->sendSerial(_hex.setGroupId(6), &_serial);
    }

    if (key == 'p') {
        if (sound.isPlaying) {
            sound.pause(&scene);
        } else {
            sound.play();
        }
    } else if (key == OF_KEY_LEFT) {
        sound.goToStart();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) { pad->mouseEvent(x, y); }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
