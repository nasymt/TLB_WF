//
//  sceneLists.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef sceneLists_hpp
#define sceneLists_hpp

#include "ofMain.h"
#include "sceneContents.hpp"
#include "serialCommunication.hpp"
#include "DataReaderScenes.hpp"
#include "DataReaderPad.hpp"

class SceneLists {
   public:
    void setup(int index, SerialCommunication *_serial, vector<BallManagement> *_ball, int _scene_num, bool isPad) {
        if (isPad) {
            pad = new DataReaderPad();
            pad->loadXml("xml/pad.xml");
            fadeTime = pad->fadeTime;
            scene_num = pad->scene_num;
            color = pad->color;
            color2 = pad->color2;
            color3 = pad->color3;
            loop = pad->loop;
            delete pad;
        }else {
            scenes = new DataReaderScenes();
            scenes->loadXml("xml/scenes.xml");
            scene_num = scenes->scene_num;
            fadeTime = scenes->fadeTime;
            color = scenes->color;
            color2 = scenes->color2;
            color3 = scenes->color3;
            loop = scenes->loop;
            delete scenes;
        }
        cout <<" sceneLists index " << index << " : " << _scene_num << endl;

        switch (scene_num[index]) {
            case 1:
                scene1 = new BallScene1();
                scene1->setup(_serial, color[index], fadeTime[index], loop[index]);
                break;

            case 2:
                scene2 = new BallScene2();
                scene2->setup(_serial, _ball, fadeTime[index], loop[index]);
                break;

            case 3:
                scene3 = new BallScene3();
                scene3->setup(_serial, color[index], fadeTime[index]);

            case 4:
                scene4 = new BallScene4();
                scene4->setup(_serial, _ball, fadeTime[index], loop[index]);
                break;
            case 5:
                scene5 = new BallScene5();
                scene5->setup(_serial, _ball, fadeTime[index], loop[index]);
                break;
            case 6:
                scene6 = new BallScene6();
                scene6->setup(_serial, color[index], color2[index], fadeTime[index], loop[index]);
                break;
            case 7:
                scene7 = new BallScene7();
                scene7->setup(_serial, _ball, fadeTime[index]);
                break;
            case 8:
                scene8 = new BallScene8();
                scene8->setup(_serial, color[index], fadeTime[index]);
                break;
            case 9:
                scene9 = new BallScene9();
                scene9->setup(_serial, color[index], color2[index], color3[index], fadeTime[index], loop[index]);
                break;
            case 10:
                scene10 = new BallScene10();
                scene10->setup(_serial, _ball, fadeTime[index], loop[index]);
                break;

            default:
                break;
        }
    }

    void update(int index, SerialCommunication *_serial, vector<BallManagement> *_ball, int _scene_num,bool isPad) {
        if (isPad) {
            pad = new DataReaderPad();
            pad->loadXml("xml/pad.xml");
            scene_num = pad->scene_num;
            delete pad;
        }else {
            scenes = new DataReaderScenes();
            scenes->loadXml("xml/scenes.xml");
            scene_num = scenes->scene_num;
            delete scenes;
        }
        
        switch (scene_num[index]) {
            case 1:
                scene1->update(_serial, _ball);
                break;
            case 2:
                scene2->update(_serial, _ball);
                break;
            case 3:
                scene3->update(_serial, _ball);
                break;
            case 4:
                scene4->update(_serial, _ball);
                break;
            case 5:
                scene5->update(_serial, _ball);
                break;
            case 6:
                scene6->update(_serial, _ball);
                break;
            case 7:
                scene7->update(_serial, _ball);
                break;
            case 8:
                scene8->update(_serial, _ball);
                break;
            case 9:
                scene9->update(_serial, _ball);
                break;
            case 10:
                scene10->update(_serial, _ball);
                break;

            default:
                break;
        }
    }

   private:
    //    BallScene *scene;
    DataReaderScenes *scenes;
    DataReaderPad *pad;
    BallScene1 *scene1;
    BallScene2 *scene2;
    BallScene3 *scene3;
    BallScene4 *scene4;
    BallScene5 *scene5;
    BallScene6 *scene6;
    BallScene7 *scene7;
    BallScene8 *scene8;
    BallScene9 *scene9;
    BallScene10 *scene10;
    vector<ofColor> color;
    vector<ofColor> color2;
    vector<ofColor> color3;
    vector<int> scene_num;
    vector<int> fadeTime;
    vector<bool> loop;
};

#endif /* sceneLists_hpp */
