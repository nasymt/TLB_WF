//
//  sceneManagement.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef sceneManagement_hpp
#define sceneManagement_hpp

#include "DataReaderConfig.hpp"
#include "DataReaderScenes.hpp"
#include "ofMain.h"
#include "sceneLists.hpp"
#include "serialCommunication.hpp"
#include "padManagement.hpp"
#include "soundPlayer.hpp"
#include "oscSenderReceiver.hpp"

class SceneManagement {
   public:
    void setup() {
        scenes = new DataReaderScenes();
        scenes->loadXml("xml/scenes.xml");
        config = new DataReaderConfig();
        config->loadXml("xml/config.xml");
        threshold = config->threshold;
        osc_receive_enabled = config->osc_receive_enabled;
        scene_name = scenes->scene_name;
        startTime = scenes->startTime;
        total_scene_num = scenes->sceneNum;
        scene_num = scenes->scene_num;
        for (int i = 0; i < total_scene_num; i++) {
            isStart.push_back(false);
        }
        delete scenes;
        delete config;
        pad.setup();
        padActive = 0;
        receive_port = config->receive_port;
        osc.setup(receive_port);
        mouseReaction = true;
    }

    void update(int _absolute, int _relative, string _scene_name, SerialCommunication *_serial, vector<BallManagement> *_ball, bool soundPlaying) {
        int now = ofGetElapsedTimeMillis();
        pad.update();

        if (ofGetMousePressed() && mouseReaction) {
            mouseReaction = false;
            pad.mouseEvent(ofGetMouseX(), ofGetMouseY());
            mouseReactTime = now + 500;
        }
        if (!mouseReaction && now > mouseReactTime) {
            mouseReaction = true;
        }

        if (osc_receive_enabled) {
            osc.receiveOscMessage();
            absoluteTime = osc.absolute_time;
            relativeTime = osc.relative_time;
            now_scene_name = osc.scene_name;
        } else {
            absoluteTime = _absolute;
            relativeTime = _relative;
            now_scene_name = _scene_name;
        }

        for (int i = 0; i < pad.pad_num; i++) {
            if (pad.bang[i]) {
                sceneLists.setup(i, _serial, _ball, scene_num[i], true);
                cout << i << " : " << scene_num[i] << " : " << endl;
                padActive = 1;
                padEndTime = now + 2000;
                padCurrentIndex = i;
                padCurrentSceneNum = scene_num[i];
                pad.bang[i] = false;
                for (int j = 0; j < scene_name.size(); j++) {
                    isStart[j] = false;
                }
                break;
            }
        }

        if (padActive > 0) {
            sceneLists.update(padCurrentIndex, _serial, _ball, padCurrentSceneNum, true);
            if (now > padEndTime) {
                padActive = 2;
            }
            if (pad.stop) {
                cout << "pad Stop " << endl;
                padActive = 0;
            }
        }

        if ((soundPlaying || osc_receive_enabled) && padActive == 0) {
            for (int i = 0; i < scene_name.size(); i++) {
                if (scene_name[i] == now_scene_name) {
                    if (startTime[i] > relativeTime - threshold && startTime[i] < relativeTime + threshold && !isStart[i]) {
                        isStart[i] = true;
                        if (i > 0 && isStart[i - 1]) isStart[i - 1] = false;
                        cout << " BANG! " << i << endl;
                        sceneLists.setup(i, _serial, _ball, scene_num[i], false);
                        padActive = 0;
                    }
                }
                if (isStart[i]) {
                    sceneLists.update(i, _serial, _ball, scene_num[i], false);
                }
            }
        }
    }

    void draw() {
        pad.draw();
        if (osc_receive_enabled) {
            ofPushMatrix();
            ofTranslate(30, 400);
            ofSetColor(255);
            ofDrawBitmapString("[receive_port] " + ofToString(receive_port), 0, -60);
            ofDrawBitmapString("[scene_name] " + now_scene_name, 0, -45);
            ofDrawBitmapString("[relativeTime] " + ofToString(relativeTime), 0, -30);
            ofDrawBitmapString("[absoluteTime] " + ofToString(absoluteTime), 0, -15);
            ofDrawBitmapString("[adjust]" + ofToString(sound.adjust_position), 200, -15);
            ofPopMatrix();
        }
    }

    void keyEvent(int key) {
        //        char tmp = key;
        switch (key) {
            case '1':
                if(!pad.isActive[0])pad.on(0);
                else pad.off(0);
                break;
            case '2':
                if(!pad.isActive[1])pad.on(1);
                else pad.off(1);
                break;
            case '3':
                if(!pad.isActive[2])pad.on(2);
                else pad.off(2);
                break;
            case '4':
                if(!pad.isActive[3])pad.on(3);
                else pad.off(3);
                break;
            case 'q':
                if(!pad.isActive[4])pad.on(4);
                else pad.off(4);
                break;
            case 'w':
                if(!pad.isActive[5])pad.on(5);
                else pad.off(5);
                break;
            case 'e':
                if(!pad.isActive[6])pad.on(6);
                else pad.off(6);
                break;
            case 'r':
                if(!pad.isActive[7])pad.on(7);
                else pad.off(7);
                break;
            case 'a':
                if(!pad.isActive[8])pad.on(8);
                else pad.off(8);
                break;
            case 's':
                if(!pad.isActive[9])pad.on(9);
                else pad.off(9);
                break;
            case 'd':
                if(!pad.isActive[10])pad.on(10);
                else pad.off(10);
                break;
            case 'f':
                if(!pad.isActive[11])pad.on(11);
                else pad.off(11);
                break;
            case 'z':
                if(!pad.isActive[12])pad.on(12);
                else pad.off(12);
                break;
            case 'x':
                if(!pad.isActive[13])pad.on(13);
                else pad.off(13);
                break;
            case 'c':
                if(!pad.isActive[14])pad.on(14);
                else pad.off(14);
                break;
            case 'v':
                if(!pad.isActive[15])pad.on(15);
                else pad.off(15);
                break;
        }
    }

    vector<bool> isStart;

   private:
    DataReaderScenes *scenes;
    DataReaderConfig *config;
    SceneLists sceneLists;
    PadManagement pad;
    SoundPlayer sound;
    OscSenderReceiver osc;

    int threshold;
    vector<string> scene_name;
    vector<int> startTime;
    vector<int> scene_num;
    int relativeTime;
    int absoluteTime;
    string now_scene_name;
    int total_scene_num;
    int padActive;
    int padEndTime;
    int padCurrentIndex;
    int padCurrentSceneNum;
    bool mouseReaction;
    int mouseReactTime;
    bool osc_receive_enabled;
    int receive_port;
};

#endif /* sceneManagement_hpp */
