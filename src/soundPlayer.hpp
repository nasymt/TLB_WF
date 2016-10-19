//
//  soundPlayer.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef soundPlayer_hpp
#define soundPlayer_hpp

#include "ofMain.h"
#include "DataReaderConfig.hpp"
#include "DataReaderSoundScene.hpp"
//#include "SceneManagement.hpp"

class SoundPlayer {
   public:
    void setup() {
        config = new DataReaderConfig();
        config->loadXml("xml/config.xml");
        sound_path = config->sound_path;
        bool mute = config->mute;
        osc_receive_enabled = config->osc_receive_enabled;
        delete config;

        sound_xml = new DataReaderSoundScene();
        sound_xml->loadXml("xml/soundScene.xml");
        scene_name = sound_xml->name;
        startTime = sound_xml->startTime;
        scene_num = sound_xml->sceneNum;
        delete sound_xml;

        sound.load(sound_path, true);
        sound.play();
        sound.setPosition(0.99999f);
        duration = sound.getPositionMS();
        sound.setPosition(0);
        sound.setPaused(true);
        if (mute) {
            sound.setVolume(0);
        }
        cout << "sound duration :" << duration << endl;
        start_x = 30;
        end_x = ofGetWidth() - 60;
        isPlaying = false;
        scene_index = 0;
        scene_endTime = startTime[scene_index + 1] - startTime[scene_index];
        set_x = start_x;
    }

    void update() {
        int x = ofGetMouseX();
        int y = ofGetMouseY();
        if (y > 300 && y < 500 && x > start_x && x < end_x) {
            if (ofGetMousePressed()) {
                int tmp = ofMap(set_x, start_x, ofGetWidth() - start_x, 0, duration);
                sound.setPaused(true);
                if (isPlaying) isPlaying = false;
                sound.setPositionMS(tmp);
                for (int i = 0; i < scene_name.size(); i++) {
                    int now = sound.getPositionMS();
                    if (i < scene_name.size() - 1 && now > startTime[i] && now < startTime[i + 1]) {
                        scene_index = i;
                        break;
                    }
                }
            }
            set_x = x;
        }

        absoluteTime = sound.getPositionMS() + adjust_position;
        now_x = (int)ofMap(absoluteTime, 0, duration, start_x, ofGetWidth() - start_x);
        if (absoluteTime > startTime[scene_index + 1] && scene_index < scene_num - 1) {
            scene_index++;
            if (scene_index >= scene_num - 1) {
                scene_endTime = duration - startTime[scene_index];
            } else {
                scene_endTime = startTime[scene_index + 1] - startTime[scene_index];
            }
        }
        relativeTime = absoluteTime - startTime[scene_index];
        now_scene = scene_name[scene_index];
        if (scene_index == scene_num - 1 && relativeTime > scene_endTime - 100) {
            sound.setPaused(true);
        }
    }

    void draw() {
        if (!osc_receive_enabled) {
            ofPushMatrix();
            ofTranslate(0, 400);
            ofSetColor(255);
            ofDrawBitmapString("[duration] " + ofToString(duration), start_x, -60);
            ofDrawBitmapString("[scene] " + scene_name[scene_index], start_x, -45);
            ofDrawBitmapString("[time] " + ofToString(absoluteTime), start_x, -30);
            ofDrawBitmapString("[sceneTime] " + ofToString(relativeTime) + " / " + ofToString(scene_endTime), start_x, -15);
            ofDrawBitmapString("[adjust]" + ofToString(adjust_position), start_x + 200, -15);
            ofDrawRectangle(start_x, 0, end_x, 1);
            ofDrawLine(set_x, -10, set_x + 1, 10);
            ofNoFill();
            ofDrawEllipse(now_x, 0, 10, 10);

            for (int i = 0; i < scene_name.size(); i++) {
                ofSetColor(200);
                int tmp = ofMap(startTime[i], 0, duration, start_x, end_x + 30);
                ofDrawEllipse(tmp, 0, 8, 8);
            }
            ofFill();
            ofPopMatrix();
        }
    }

    void play() {
        sound.setPaused(false);
        isPlaying = true;
    }

    void pause() {
        sound.setPaused(true);
        isPlaying = false;
    }

    void goToStart() {
        sound.setPaused(true);
        sound.setPosition(0);
        scene_index = 0;
        absoluteTime = 0;
        relativeTime = 0;
        now_scene = scene_name[0];
    }

    bool isPlaying;
    int relativeTime;
    int absoluteTime;
    string now_scene;
    int adjust_position;

   private:
    DataReaderConfig *config;
    DataReaderSoundScene *sound_xml;
    string sound_path;
    ofSoundPlayer sound;
    int start_x;
    int end_x;
    int now_x;
    int set_x;
    int duration;
    int scene_index;
    int scene_endTime;
    int scene_num;
    vector<string> scene_name;
    vector<int> startTime;
    int sceneNum;
    bool osc_receive_enabled;
};

#endif /* soundPlayer_hpp */
