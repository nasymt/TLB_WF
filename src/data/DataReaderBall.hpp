//
//  DataReaderBall.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/06.
//
//

#ifndef DataReaderBall_hpp
#define DataReaderBall_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataReaderHex {
public:
    DataReaderHex(){};
    ~DataReaderHex(){};
    
    void loadXml(string path){
        xml = new ofxXmlSettings();
        xml->load("xml/hex.xml");
        
        xml->pushTag("serial");
        string hexMessage = xml->getValue("hex","");
        for(int i=0;i<hexMessage.size();i++){
            if(hexMessage[i]==' '){
                char tmp = ofToChar(hexMessage.substr(i-4,4));
                sendSerial.push_back(tmp);
            }
        }
    };
    
    vector<Byte> sendSerial;
    
private:
    ofxXmlSettings *xml;
};

#endif /* DataReaderBall_hpp */
