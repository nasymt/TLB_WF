//
//  oscSenderReceiver.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef oscSenderReceiver_hpp
#define oscSenderReceiver_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class OscSenderReceiver {
   public:
    void setup(int _receive_port) {
        sender.setup("127.0.0.1", 10000);
        receiver.setup(_receive_port);
    }
    
    void receiveOscMessage(){
        while (receiver.hasWaitingMessages()) {
            ofxOscMessage m;
            receiver.getNextMessage(m);
            if(m.getAddress() == "/sound/time"){
                scene_name = m.getArgAsString(0);
                relative_time = m.getArgAsInt(1);
                absolute_time = m.getArgAsInt(2);
            }
        }
    }
    
    int absolute_time;
    int relative_time;
    int beat;
    string scene_name;

   private:
    ofxOscSender sender;
    ofxOscReceiver receiver;
};

#endif /* oscSenderReceiver_hpp */
