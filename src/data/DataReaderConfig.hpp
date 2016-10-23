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
        xml->popTag();
        auto_setup = xml->getValue("auto_setup",0);
        scene_path = xml->getValue("scene_path","");
        sound_path = xml->getValue("sound_path","");
        threshold = xml->getValue("scene_threshold",0);
        mute = xml->getValue("sound_mute",0);
        receive_port = xml->getValue("osc_receive_port",0);
        osc_receive_enabled = xml->getValue("osc_receive_enabled",0);
        delete xml;
    };
    
    string lpr_node;
    string lpr_channel;
    string sound_path;
    string scene_path;
    bool auto_setup;
    int threshold;
    bool mute;
    int receive_port;
    bool osc_receive_enabled;
    
   private:
    ofxXmlSettings *xml;
};

#endif /* DataReaderConfig_hpp */
