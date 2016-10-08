//
//  sceneManagement.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef sceneManagement_hpp
#define sceneManagement_hpp

#include "ofMain.h"
#include "DataReaderScenes.hpp"
#include "DataReaderConfig.hpp"
#include "serialCommunication.hpp"
#include "hex.hpp"
#include "soundPlayer.hpp"
#include "sceneLists.hpp"

class SceneManagement {
   public:
    void setup(SerialCommunication _serial) {
        serial = _serial;
        scenes = new DataReaderScenes();
        scenes->loadXml("xml/scenes.xml");
        config = new DataReaderConfig();
        config->loadXml("xml/config.xml");
        threshold = config->threshold;

        scene_name = scenes->scene_name;
        startTime = scenes->startTime;
        scene_num = scenes->sceneNum;
        for (int i = 0; i < scene_num; i++) {
            isStart.push_back(false);
            _repeat.push_back(scenes->repeat[i]);
            fadeTime.push_back(scenes->fadeTime[i]);
        }

        delete scenes;
        delete config;
    }

    void update(int _absolute, int _relative, string _scene_name) {
        absoluteTime = _absolute;
        relativeTime = _relative;
        now_scene_name = _scene_name;

        for (int i = 0; i < scene_name.size(); i++) {
            if (scene_name[i] == now_scene_name) {
                if (startTime[i] > relativeTime - threshold && startTime[i] < relativeTime + threshold && !isStart[i]) {
                    isStart[i] = true;
                    if (i > 0 && isStart[i - 1]) isStart[i - 1] = false;
                    cout << " BANG! " << i << endl;
                    sceneLists.setup(i, serial);
                    timer_endTime = fadeTime[i] + ofGetElapsedTimeMillis();
                    if (timer_endTime > 0) {
                        timer = true;
                    }
                }
            }
            if (isStart[i]) {
                sceneLists.update(i);
            }
        }
        if (timer) {
            updateTimer();
        }
    }

    void updateTimer() {
        int now = ofGetElapsedTimeMillis();
        if (now > timer_endTime) {
            timer = false;
        }
    }
    
    

   private:
    DataReaderScenes *scenes;
    DataReaderConfig *config;
    SerialCommunication serial;
    SceneLists sceneLists;
    SoundPlayer sound;
    Hex _hex;
    int threshold;
    vector<string> scene_name;
    vector<int> startTime;
    vector<bool> _repeat;
    vector<int> fadeTime;
    int relativeTime;
    int absoluteTime;
    string now_scene_name;
    vector<bool> isStart;
    int scene_num;
    bool prepareFadeIn;
    bool prepareFadeOut;
    bool repeat;
    int timer_endTime;
    bool timer;
};

#endif /* sceneManagement_hpp */
