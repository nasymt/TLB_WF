//
//  ballManagement.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/07.

#ifndef ballManagement_hpp
#define ballManagement_hpp

#include "ofMain.h"
#include "DataReaderBall.hpp"

class BallManagement {
   public:
    void setup(int _index, int _ball_num) {
        ball_num = _ball_num;
        index = _index;
        ball = new DataReaderBall();
        ball->loadXml("xml/Ball.xml");
        channel = ball->channel[index];
        id = ball->id[index];
        group_id = ball->group_id[index];
    }

    void update() {}

    void draw() {
        ofSetColor(255, 0, 0);
        ofPushMatrix();
        ofTranslate(ofGetWidth() / (ball_num + 1) * (index + 1), ofGetHeight() / 2-30);
        ofDrawEllipse(0, 0, 50, 50);
        ofSetColor(0);
        //        ofDrawRectangle(-25,30,50,20);
        ofDrawRectangle(-35, 30, 75, 45);

        ofSetColor(255);
        ofDrawBitmapString("group:" + ofToString(group_id), -25, 45);
        ofDrawBitmapString("ID:" + ofToString(id), -25, 65);
        ofPopMatrix();
    }

    int ball_num;
    int index;
    int channel;
    int id;
    int group_id;

   private:
    DataReaderBall *ball;
};

#endif /* ballManagement_hpp */
