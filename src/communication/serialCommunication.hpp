//
//  LPR9201.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/07.
//
//

#ifndef sendOscLPR9201_hpp
#define sendOscLPR9201_hpp

#include "ofMain.h"

class SerialCommunication {
   public:
    void setup(int i){
        test = i;
        serial.listDevices();
        vector<ofSerialDeviceInfo> deviceList = serial.getDeviceList();
        int baud = 9600;
        serial.setup(0, baud);  // open the first device
    }
    
    void sendSerial(vector<Byte> sendByte) {
        cout << "ok" << endl;
        for (int i = 0; i < sendByte.size(); i++) {
            serial.writeByte(sendByte[i]);
        }
        Byte checksum = checkSum(sendByte);
        serial.writeByte(checksum);
        recvSerial();
    }

    void recvSerial() {
        while (serial.available() > 0) {
            int readByte = serial.readByte();
            if( readByte == 82 || readByte == 130){
                cout << "==get serial error==  " <<  readByte << endl;
            }
            cout << "[read] " << hex << readByte << endl;
        }
    }

    Byte checkSum(vector<Byte> _checksum) {
        Byte tmp = 0x00;
        for (int i = 0; i < _checksum.size(); i++) {
            tmp = tmp ^ _checksum[i];
        }
        return tmp;
    }

    int test = 0;
    
   private:
    ofSerial serial;
};

#endif /* sendOscLPR9201_hpp */
