//
//  sceneContents.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef sceneContents_hpp
#define sceneContents_hpp

#include "ofMain.h"
#include "serialCommunication.hpp"
#include "hex.hpp"

class BallScene1 {
   public:
    void setup(SerialCommunication _serial) {
        serial = _serial;
        _hex = new Hex();
//        serial = new SerialManagement();
        cout << "BallSCene1 setup" << endl;
    }

    void update() {
        if (scene_index == 0) {
            //serial->sendSerial(_hex->changeColor(ofColor(255,0,0)));
        }
    }

   private:
    int scene_index;
    SerialCommunication serial;
    Hex *_hex;
};

class BallScene2 {
   public:
    void setup(SerialCommunication _serial) {
        serial = _serial;
        cout << "BallSCene2 setup" << endl;
        
    }

    void update() {
        //        cout << "BallScene2 update" << endl;
    }

   private:
    SerialCommunication serial;
    
};

class BallScene3 {
   public:
    void setup(SerialCommunication _serial) {
        serial = _serial;
        cout << "BallScene3 setup" << endl;
    }
    
    void update() {
        //        cout << "BallScene3 update" << endl;
    }

   private:
    SerialCommunication serial;
    
};

#endif /* sceneContents_hpp */
