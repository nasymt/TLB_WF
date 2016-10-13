//
//  selectPad.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/07.
//
//

#ifndef selectPad_hpp
#define selectPad_hpp

#include "ofMain.h"
#include "serialCommunication.hpp"
#include "hex.hpp"

class SelectPad {
   public:
    void setup(SerialCommunication &_serial) {
//        serial = _serial;
//        serial->setup();
        for (int i = 0; i < pad_num; i++) {
            isActive.push_back(false);
            color.push_back(ofColor(255, 0, 0));
        }
        translateX = 450;
        translateY = 20;
        edit_mode = false;
        play_mode = true;
        active_color = 255;
        active_color_dis = -1;
    }
    void update() {
        if (active_color <= 0) {
            active_color_dis = 1;
        } else if (active_color >= 255) {
            active_color_dis = -1;
        }
        active_color += 5 * active_color_dis;
    }

    void draw() {
        ofSetColor(200);
        ofPushMatrix();
        ofTranslate(translateX, translateY);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (isActive[j + i * 4]) {
                    ofSetColor(active_color, 0, active_color);
                } else {
                    ofSetColor(200);
                }
                ofDrawRectangle(j * 30, i * 30, 20, 20);
            }
        }
        if (edit_mode) {
            ofSetColor(0, 255, 255);
        } else {
            ofSetColor(100);
        }
        ofDrawRectangle(0, 120, 50, 20);
        if (play_mode) {
            ofSetColor(0, 255, 255);
        } else {
            ofSetColor(100);
        }
        ofDrawRectangle(60, 120, 50, 20);
        ofSetColor(0);
        ofDrawBitmapString("EDIT", 10, 135);
        ofDrawBitmapString("PLAY", 70, 135);
        ofPopMatrix();
    }

    void mouseEvent(int mouseX, int mouseY) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (mouseX > j * 30 + translateX && mouseX < j * 30 + 20 + translateX && mouseY > i * 30 + translateY && mouseY < i * 30 + 20 + translateY) {
                    if (isActive[j + i * 4]) {
                        isActive[j + i * 4] = false;
                    } else {
                        isActive[j + i * 4] = true;
                        //sendSerial(_hex.changeColor(ofColor(255, 0, 0)));
                    }
                }
            }
        }
        if (mouseX > translateX && mouseX < 50 + translateX && mouseY > 120 + translateY && mouseY < 140 + translateY) {
            if (!edit_mode) {
                edit_mode = true;
                play_mode = false;
            }
        } else if (mouseX > 60 + translateX && mouseX < 110 + translateX && mouseY > 120 + translateY && mouseY < 140 + translateY) {
            if (!play_mode) {
                play_mode = true;
                edit_mode = false;
                for (int i = 0; i < pad_num; i++) {
                    if (isActive[i]) isActive[i] = false;
                }
            }
        }
    }

    void sendSerial(vector<Byte> sendByte,SerialCommunication *_serial) {
        cout << _serial->test << endl;
        _serial->sendSerial(sendByte);
        cout << " send serial " << endl;
    }

    vector<bool> isActive;
    int pad_num = 16;
    vector<ofColor> color;

   private:
    int translateX;
    int translateY;

    bool play_mode;
    bool edit_mode;
    int active_color;
    int active_color_dis;
//    SerialCommunication *serial;
    Hex _hex;
};

#endif /* selectPad_hpp */
