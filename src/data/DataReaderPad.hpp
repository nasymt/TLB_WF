//
//  DataReaderPad.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/14.
//
//

#ifndef DataReaderPad_hpp
#define DataReaderPad_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataReaderPad {
   public:
    DataReaderPad(){};
    ~DataReaderPad(){};
    
    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load("xml/pad.xml");
        
        xml->pushTag("pad");
        sceneNum = xml->getNumTags("scene");
        for (int i = 0; i < sceneNum; i++) {
            scene_num.push_back(xml->getValue("scene:scene_num",0,i));
            int r, g, b;
            r = xml->getValue("scene:color_r", 0, i);
            g = xml->getValue("scene:color_g", 0, i);
            b = xml->getValue("scene:color_b", 0, i);
            color.push_back(ofColor(r, g, b));
            r = xml->getValue("scene:color2_r",0,i);
            g = xml->getValue("scene:color2_g",0,i);
            b = xml->getValue("scene:color2_b",0,i);
            color2.push_back(ofColor(r,g,b));
            r = xml->getValue("scene:color3_r",0,i);
            g = xml->getValue("scene:color3_g",0,i);
            b = xml->getValue("scene:color3_b",0,i);
            color3.push_back(ofColor(r,g,b));
            
            fadeTime.push_back(xml->getValue("scene:fadeTime",0,i));
            loop.push_back(xml->getValue("scene:loop",0,i));
            absolute.push_back(xml->getValue("scene:absolute",0,i));
            string tmp = xml->getValue("scene:mode","",i);
            if(tmp == "trigger"){
                isTrigger.push_back(true);
            }else {
                isTrigger.push_back(false);
            }
            
        }
    };
    
    int sceneNum;
    vector<int> scene_num;
    vector<ofColor> color;
    vector<ofColor> color2;
    vector<ofColor> color3;
    vector<int> fadeTime;
    vector<bool> loop;
    vector<bool> absolute;
    vector<bool> isTrigger;
    
   private:
    ofxXmlSettings *xml;
    
};

#endif /* DataReaderPad_hpp */
