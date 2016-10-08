//
//  DataReaderScenes.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef DataReaderScenes_hpp
#define DataReaderScenes_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class DataReaderScenes {
   public:
    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load("xml/scenes.xml");

        xml->pushTag("scenes");
        sceneNum = xml->getNumTags("scene");
        for (int i = 0; i < sceneNum; i++) {
            scene_name.push_back(xml->getValue("scene:scene_name", "", i));
            startTime.push_back(xml->getValue("scene:startTime", 0, i));
            pattern.push_back(xml->getValue("scene:pattern", 0, i));
            repeat.push_back(xml->getValue("scene:repeat", 0, i));
            int r, g, b;
            r = xml->getValue("scene:color_r", 0, i);
            g = xml->getValue("scene:color_g", 0, i);
            b = xml->getValue("scene:color_b", 0, i);
            color.push_back(ofColor(r, g, b));
            fadeTime.push_back(xml->getValue("scene:fadeTime", 0, i));
            cout << scene_name[i] << " : " << startTime[i] << endl;
        }
    };

    int sceneNum;
    vector<string> scene_name;
    vector<int> startTime;
    vector<int> pattern;
    vector<ofColor> color;
    vector<int> fadeTime;
    vector<bool> repeat;

   private:
    ofxXmlSettings *xml;
};

#endif /* DataReaderScenes_hpp */
