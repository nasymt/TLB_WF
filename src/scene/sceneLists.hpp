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

class SceneLists {
   public:
    void setup(int index,SerialCommunication _serial){
        serial = _serial;
        switch (index) {
            case 0:
                scene1 = new BallScene1();
                scene1->setup(serial);
                break;
            
            case 1:
                scene2 = new BallScene2();
                scene2->setup(serial);
                break;
                
            case 2:
                scene3 = new BallScene3();
                scene3->setup(serial);
                break;
                
            default:
                break;
        }
    }
    
    void update(int index){
        switch (index) {
            case 0:
                scene1->update();
                break;
            case 1:
                scene2->update();
                break;
            case 2:
                scene3->update();
                break;

                
                
            default:
                break;
        }
    }

   private:
//    BallScene *scene;
    BallScene1 *scene1;
    BallScene2 *scene2;
    BallScene3 *scene3;
    SerialCommunication serial;
};

#endif /* sceneLists_hpp */
