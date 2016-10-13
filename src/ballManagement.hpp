//
//  ballManagement.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/07.

#ifndef ballManagement_hpp
#define ballManagement_hpp

#include "ofMain.h"
#include "DataReaderBall.hpp"
#include "easingManagement.hpp"

class BallManagement {
   public:
    void setup(int _index, int _ball_num) {
        ball_num = _ball_num;
        index = _index;
        ball = new DataReaderBall();
        ball->loadXml("xml/Ball.xml");
        total_ball_num = ball->ball_num;
        channel = ball->channel[index];
        _id = ball->_id[index];
        group_id = ball->group_id[index];
        color = ofColor(0, 0, 0);
        alpha = 255;
    }

    void update() {
        if (fadeIn || fadeOut) {
            easing.update();
            updateFade();
        }
    }

    void draw() {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / (ball_num + 1) * (index + 1), ofGetHeight() / 2 - 30);
        ofSetColor(color.r, color.g, color.b, alpha);
        ofDrawEllipse(0, 0, 50, 50);
        ofSetColor(0);
        ofDrawRectangle(-35, 30, 75, 45);

        ofSetColor(255);
        ofDrawBitmapString("group:" + ofToString(group_id), -25, 45);
        ofDrawBitmapString("ID:" + ofToString(_id), -25, 65);
        ofPopMatrix();
    }

    void fadeInOut(int fadeTime, bool isFadeIn) {
        int duration = fadeTime;
        int delay = 0;
        float begin, end;
        if (isFadeIn) {
            fadeIn = true;
            alpha = 0;
            begin = 0;
            end = 255;
        } else {
            fadeOut = true;
            begin = 255;
            end = 0;
        }
        fade_endTime = ofGetElapsedTimeMillis() + fadeTime;
        easing.setParam(duration, delay, begin, end);
        easing.start();
//        fade_val = 255 / fadeTime * ofGetFrameRate();
//        cout << "alpha fade_val " << alpha << " : " << fade_val << " : " << ofGetFrameRate() << " : " << fadeTime << endl;
    }

    void updateFade() {
        alpha = easing.getValue();

        int now = ofGetElapsedTimeMillis();
        if (now > fade_endTime) {
            fadeIn = false;
            fadeOut = false;
        }
    }

    int ball_num;
    int total_ball_num;
    int index;
    int channel;
    int _id;
    int group_id;
    ofColor color;
    bool fadeIn;
    bool fadeOut;
    int fade_endTime;
    float fade_val;
    float alpha;

   private:
    DataReaderBall *ball;
    easingManagement easing;
};

#endif /* ballManagement_hpp */
