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
#include "DataReaderConfig.hpp"

class DataReaderScenes {
   public:
    void loadXml(string path) {
        config = new DataReaderConfig();
        config->loadXml("xml/config.xml");
        string scene_path = config->scene_path;
        //cout << scene_path << endl;
        xml = new ofxXmlSettings();
        // xml->load("xml/scenes.xml");
        xml->load(scene_path);

        xml->pushTag("scenes");
        sceneNum = xml->getNumTags("scene");
        for (int i = 0; i < sceneNum; i++) {
            scene_name.push_back(xml->getValue("scene:scene_name", "", i));
            startTime.push_back(xml->getValue("scene:startTime", 0, i));
            scene_num.push_back(xml->getValue("scene:scene_num", 0, i));
            loop.push_back(xml->getValue("scene:loop", 0, i));
            int r, g, b;
            r = xml->getValue("scene:color_r", 0, i);
            g = xml->getValue("scene:color_g", 0, i);
            b = xml->getValue("scene:color_b", 0, i);
            color.push_back(ofColor(r, g, b));
            r = xml->getValue("scene:color2_r", 0, i);
            g = xml->getValue("scene:color2_g", 0, i);
            b = xml->getValue("scene:color2_b", 0, i);
            color2.push_back(ofColor(r, g, b));
            r = xml->getValue("scene:color3_r", 0, i);
            g = xml->getValue("scene:color3_g", 0, i);
            b = xml->getValue("scene:color3_b", 0, i);
            color3.push_back(ofColor(r, g, b));

            fadeTime.push_back(xml->getValue("scene:fadeTime", 0, i));
            //            cout << scene_name[i] << " : " << startTime[i] << endl;

            //            delete config;
        }
        delete config;
        delete xml;
    };

    int sceneNum;
    vector<string> scene_name;
    vector<int> startTime;
    vector<int> scene_num;
    vector<ofColor> color;
    vector<ofColor> color2;
    vector<ofColor> color3;
    vector<int> fadeTime;
    vector<bool> loop;

   private:
    DataReaderConfig *config;
    ofxXmlSettings *xml;
};

#endif /* DataReaderScenes_hpp */
