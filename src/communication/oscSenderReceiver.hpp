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
    void setup() { sender.setup("127.0.0.1", 10000); }
    
    

   private:
    ofxOscSender sender;
};

#endif /* oscSenderReceiver_hpp */
