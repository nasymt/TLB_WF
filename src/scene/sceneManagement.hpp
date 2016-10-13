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
#include "hex.hpp"
#include "ofMain.h"
#include "sceneLists.hpp"
#include "serialCommunication.hpp"
//#include "soundPlayer.hpp"

class SceneManagement {
   public:
    void setup() {
        scenes = new DataReaderScenes();
        scenes->loadXml("xml/scenes.xml");
        config = new DataReaderConfig();
        config->loadXml("xml/config.xml");
        threshold = config->threshold;

        scene_name = scenes->scene_name;
        startTime = scenes->startTime;
        total_scene_num = scenes->sceneNum;
        scene_num = scenes->scene_num;
        fadeTime = scenes->fadeTime;
        color = scenes->color;
        color2 = scenes->color2;
        for (int i = 0; i < total_scene_num; i++) {
            isStart.push_back(false);
            loop.push_back(scenes->loop[i]);
        }
        delete scenes;
        delete config;
    }

    void update(int _absolute, int _relative, string _scene_name, SerialCommunication *_serial, vector<BallManagement> *_ball) {
        absoluteTime = _absolute;
        relativeTime = _relative;
        now_scene_name = _scene_name;

        for (int i = 0; i < scene_name.size(); i++) {
            if (scene_name[i] == now_scene_name) {
                if (startTime[i] > relativeTime - threshold && startTime[i] < relativeTime + threshold && !isStart[i]) {
                    isStart[i] = true;
                    if (i > 0 && isStart[i - 1]) isStart[i - 1] = false;
                    cout << " BANG! " << i << endl;
                    sceneLists.setup(i, _serial, _ball, scene_num[i]);
                }
            }
            if (isStart[i]) {
                sceneLists.update(i, _serial, _ball, scene_num[i]);
            }
        }
    }

    //    void updateTimer() {
    //        int now = ofGetElapsedTimeMillis();
    //        if (now > timer_endTime) {
    //            timer = false;
    //        }
    //    }
    vector<bool> isStart;

   private:
    DataReaderScenes *scenes;
    DataReaderConfig *config;
    SceneLists sceneLists;
    //    SoundPlayer sound;
    Hex _hex;
    int threshold;
    vector<string> scene_name;
    vector<int> startTime;
    vector<bool> loop;
    vector<int> fadeTime;
    vector<int> scene_num;
    vector<ofColor> color;
    vector<ofColor> color2;
    int relativeTime;
    int absoluteTime;
    string now_scene_name;
    int total_scene_num;
};

#endif /* sceneManagement_hpp */
