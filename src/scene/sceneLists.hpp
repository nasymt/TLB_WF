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

class SceneLists {
   public:
    void setup(int index, SerialCommunication *_serial, vector<BallManagement> *_ball, int scene_num) {
        scenes = new DataReaderScenes();
        scenes->loadXml("xml/scenes.xml");
        fadeTime = scenes->fadeTime;
        color = scenes->color;
        color2 = scenes->color2;
        loop = scenes->loop;

        switch (scene_num) {
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

            default:
                break;
        }
    }

    void update(int index, SerialCommunication *_serial, vector<BallManagement> *_ball, int scene_num) {
        switch (scene_num) {
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
            case 8:
                scene8->update(_serial, _ball);

            default:
                break;
        }
    }

   private:
    //    BallScene *scene;
    DataReaderScenes *scenes;
    BallScene1 *scene1;
    BallScene2 *scene2;
    BallScene3 *scene3;
    BallScene4 *scene4;
    BallScene5 *scene5;
    BallScene6 *scene6;
    BallScene7 *scene7;
    BallScene8 *scene8;
    vector<ofColor> color;
    vector<ofColor> color2;
    vector<int> fadeTime;
    vector<bool> loop;
};

#endif /* sceneLists_hpp */
