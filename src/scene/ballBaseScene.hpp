//
//  ballBaseScene.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/09.
//
//

#ifndef ballBaseScene_hpp
#define ballBaseScene_hpp

#include "ofMain.h"
#include "ballManagement.hpp"

class BallBaseScene {
   public:
    void setup(vector<BallManagement> *_ball) { ball_num = (*_ball)[0].ball_num; }

    int getColorNum(){return 6;};
    ofColor getColorPattern(int index) {
        vector<ofColor> tmp;
        tmp.push_back(ofColor(255, 0, 0));
        tmp.push_back(ofColor(0, 255, 0));
        tmp.push_back(ofColor(0, 0, 255));
        tmp.push_back(ofColor(255, 255, 0));
        tmp.push_back(ofColor(255, 0, 255));
        tmp.push_back(ofColor(0, 255, 255));
        if(index >tmp.size()-1){
            index = 0;
        }
        return tmp[index];
    }
    
    

    int scene_index;
    int startTime;
    int ball_num;
    int fadeTime;
    bool completed;
    bool loop;
    vector<ofColor> color;
    vector<ofColor> color2;
    vector<ofColor> color3;

   private:
};

#endif /* ballBaseScene_hpp */
