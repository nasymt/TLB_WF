//
//  DataReaderConfig.hpp
//  TLB_serialTest
//
//  Created by 松岡正 on 2016/10/06.
//
//

#ifndef DataReaderConfig_hpp
#define DataReaderConfig_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataReaderConfig {
   public:
    DataReaderConfig(){};
    ~DataReaderConfig(){};
    
    void loadXml(string path){
        xml = new ofxXmlSettings();
        xml->load("xml/config.xml");
        
        xml->pushTag("config");
        xml->pushTag("lpr_settings");
        lpr_node = xml->getValue("node","");
        lpr_channel = xml->getValue("channel","");
        cout << lpr_node << " : " << lpr_channel << endl;
        
        delete xml;
    };
    
    string lpr_node;
    string lpr_channel;
    
   private:
    ofxXmlSettings *xml;
};

#endif /* DataReaderConfig_hpp */
