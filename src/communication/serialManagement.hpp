//
//  serialManagement.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef serialManagement_hpp
#define serialManagement_hpp

#include "ofMain.h"
#include "serialCommunication.hpp"

class SerialManagement {
   public:
    void setup(){
        serial = new SerialCommunication();
        serial->setup();
    }
    
    void sendSerial(vector<Byte> sendByte){
        serial->sendSerial(sendByte);
    }
    
   private:
    SerialCommunication *serial;
};

#endif /* serialManagement_hpp */
