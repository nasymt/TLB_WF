//
//  DataReaderSoundScene.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef DataReaderSoundScene_hpp
#define DataReaderSoundScene_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataReaderSoundScene {
   public:
    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load("xml/soundScene.xml");

        xml->pushTag("soundScene");
        sceneNum = xml->getNumTags("scene");
        for (int i = 0; i < sceneNum; i++) {
            name.push_back(xml->getValue("scene:name", "", i));
            startTime.push_back(xml->getValue("scene:startTime", 0, i));
        }
        
        delete xml;
    };

    int sceneNum;
    vector<string> name;
    vector<int> startTime;
    

   private:
    ofxXmlSettings *xml;
};

#endif /* DataReaderSoundScene_hpp */
