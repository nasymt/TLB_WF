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

class DataReaderBall {
   public:
    DataReaderBall(){};
    ~DataReaderBall(){};

    void loadXml(string path) {
        xml = new ofxXmlSettings();
        xml->load("xml/ball.xml");

        xml->pushTag("Ball");
        ball_num = xml->getNumTags("ball");
        for (int i = 0; i < ball_num; i++) {
            channel.push_back(xml->getValue("ball:channel", 0, i));
            _id.push_back(xml->getValue("ball:id", 0, i));
            group_id.push_back(xml->getValue("ball:group_id", 0, i));
        }
    };

    int ball_num;
    vector<int> channel;
    vector<int> _id;
    vector<int> group_id;

   private:
    ofxXmlSettings *xml;
};

#endif /* DataReaderBall_hpp */
