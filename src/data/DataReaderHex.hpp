//
//  DataReaderHex.hpp
//  TLB_serialTest
//
//  Created by 松岡正 on 2016/10/05.
//
//

#ifndef DataReaderHex_hpp
#define DataReaderHex_hpp

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

#endif /* DataReaderHex_hpp */
