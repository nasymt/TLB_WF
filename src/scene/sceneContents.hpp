//
//  sceneContents.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/08.
//
//

#ifndef sceneContents_hpp
#define sceneContents_hpp

#include "hex.hpp"
#include "ofMain.h"
#include "serialCommunication.hpp"
#include "ballManagement.hpp"
#include "ballBaseScene.hpp"

//====================================================================
//
// BallScene1 -> selectColorChange
//
//====================================================================
class BallScene1 : public BallBaseScene {
   public:
    void setup(SerialCommunication *_serial, ofColor _color, int _fadeTime, bool _loop) {
        fadeTime = _fadeTime;
        loop = _loop;
        color = _color;
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene1 setup" << _serial->test << endl;
        scene_index = 0;
    }

    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        ball_num = (*_ball)[0].total_ball_num;
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            for (int i = 0; i < ball_num; i++) {
                (*_ball)[i].color = color;
                (*_ball)[i].fadeInOut(fadeTime, true);
            }

            _serial->sendSerial(_hex->changeColor(ofColor(color), fadeTime));
            cout << " ballscene1 fadein" << endl;
            scene_index = 1;
        } else if (scene_index == 1) {
            if (now > fadeTime - 30) {
                _serial->sendSerial(_hex->changeColor(ofColor(0, 0, 0), fadeTime));
                for (int i = 0; i < ball_num; i++) {
                    (*_ball)[i].color = ofColor(color);
                    (*_ball)[i].fadeInOut(fadeTime, false);
                }
                cout << " ballscene1 fadeout" << endl;
                scene_index = 2;
            }
        } else if (scene_index == 2 && loop) {
            if (now > fadeTime * 2 - 30) {
                scene_index = 0;
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }

   private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    ofColor color;
    int fadeTime;
    bool loop;
};

//====================================================================
//
// BallScene2 -> randomColorChange
//
//====================================================================
class BallScene2 : public BallBaseScene {
   public:
    void setup(SerialCommunication *_serial, vector<BallManagement> *_ball, int _fadeTime, bool _loop) {
        fadeTime = _fadeTime;
        loop = _loop;
        cout << "FADE TIME : " << fadeTime << endl;
        ball_num = (*_ball)[0].total_ball_num;
        for (int i = 0; i < ball_num; i++) {
            randomIndex.push_back(i);
            color.push_back(getColorPattern(i));
        }
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene2 setup" << _serial->test << endl;
        scene_index = 0;
    }

    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            doIndexRandom();
            for (int i = 0; i < ball_num; i++) {
                (*_ball)[i].color = color[randomIndex[i]];
                (*_ball)[i].fadeInOut(fadeTime, true);
            }
            _serial->sendSerial(_hex->randomColor(fadeTime));
            cout << " ballscene1 fadein" << endl;
            scene_index = 1;
        } else if (scene_index == 1) {
            if (now > fadeTime - 30) {
                _serial->sendSerial(_hex->changeColor(ofColor(0, 0, 0), fadeTime));
                for (int i = 0; i < ball_num; i++) {
                    //                    (*_ball)[i].color = ofColor(color[i]);
                    (*_ball)[i].fadeInOut(fadeTime, false);
                }
                cout << " ballscene1 fadeout" << endl;
                scene_index = 2;
            }
        } else if (scene_index == 2 && loop) {
            if (now > fadeTime * 2 - 30) {
                scene_index = 0;
                startTime = ofGetElapsedTimeMillis();
/*                for (int i = 0; i < ball_num; i++) {
                    int color_num = (int)ofRandom(getColorNum());
                    (*_ball)[i].color = ofColor(color[i]);
                    color[i] = getColorPattern(color_num);
                }*/
            }
        }
    }

    void doIndexRandom() {
        for(int i=0;i<ball_num;i++){
            int random = (int)ofRandom(ball_num);
            int tmp = randomIndex[i];
            randomIndex[i] = randomIndex[random];
            randomIndex[random] = tmp;
        }
    }

   private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    vector<ofColor> color;
    vector<int> randomIndex;
    int fadeTime;
    bool loop;
};

//====================================================================
//
// BallScene3 -> selectColorChange : only fade in
//
//====================================================================
class BallScene3 : public BallBaseScene {
   public:
    void setup(SerialCommunication *_serial, ofColor _color, int _fadeTime) {
        fadeTime = _fadeTime;
        color = _color;
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene3 setup" << endl;
        scene_index = 0;
    }

    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        ball_num = (*_ball)[0].total_ball_num;
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            for (int i = 0; i < ball_num; i++) {
                (*_ball)[i].color = color;
                (*_ball)[i].fadeInOut(fadeTime, true);
            }

            _serial->sendSerial(_hex->changeColor(ofColor(color), fadeTime));
            cout << " ballscene1 fadein" << endl;
            scene_index = 1;
        }
    }

   private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    ofColor color;
    int fadeTime;
    bool loop;
};

//====================================================================
//
// BallScene4 -> randomChange : no blackout
//
//====================================================================
class BallScene4 : public BallBaseScene {
   public:
    void setup(SerialCommunication *_serial, vector<BallManagement> *_ball, int _fadeTime, bool _loop) {
        fadeTime = _fadeTime;
        loop = _loop;
        cout << "FADE TIME : " << fadeTime << endl;
        ball_num = (*_ball)[0].total_ball_num;
        for (int i = 0; i < ball_num; i++) {
            randomIndex.push_back(i);
            color.push_back(getColorPattern(i));
        }
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene2 setup" << _serial->test << endl;
        scene_index = 0;
    }

    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            doIndexRandom();
            for (int i = 0; i < ball_num; i++) {
                (*_ball)[i].color = color[randomIndex[i]];
                (*_ball)[i].fadeInOut(fadeTime, true);
            }

            _serial->sendSerial(_hex->randomColor(fadeTime));
            cout << " ballscene1 fadein" << endl;
            scene_index = 1;
        } else if (scene_index == 1) {
            if (now > fadeTime - 30) {
                doIndexRandom();
                _serial->sendSerial(_hex->randomColor(fadeTime));
                for (int i = 0; i < ball_num; i++) {
                    (*_ball)[i].color = ofColor(color[randomIndex[i]]);
                    (*_ball)[i].fadeInOut(fadeTime, true);
                }
                cout << " ballscene1 fadeout" << endl;
                scene_index = 2;
            }
        } else if (scene_index == 2 && loop) {
            if (now > fadeTime * 2 - 30) {
                scene_index = 0;
                startTime = ofGetElapsedTimeMillis();
//                for (int i = 0; i < ball_num; i++) {
//                    int color_num = (int)ofRandom(getColorNum());
//                    color[i] = getColorPattern(color_num);
//                    (*_ball)[i].color = ofColor(color[i]);
//                }
            }
        }
    }
    
    void doIndexRandom() {
        for(int i=0;i<ball_num;i++){
            int random = (int)ofRandom(ball_num);
            int tmp = randomIndex[i];
            randomIndex[i] = randomIndex[random];
            randomIndex[random] = tmp;
        }
    }


   private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    vector<ofColor> color;
    vector<int> randomIndex;
    int fadeTime;
    bool loop;
};

//====================================================================
//
// BallScene5 -> randomColorChange : random unicast
//
//====================================================================
class BallScene5 : public BallBaseScene {
   public:
    void setup(SerialCommunication *_serial, vector<BallManagement> *_ball, int _fadeTime, bool _loop) {
        fadeTime = _fadeTime;
        loop = _loop;
        cout << "FADE TIME : " << fadeTime << endl;
        ball_num = (*_ball)[0].total_ball_num;
        for (int i = 0; i < ball_num; i++) {
            int color_num = (int)ofRandom(getColorNum());
            color.push_back(getColorPattern(color_num));
            _id.push_back((*_ball)[i]._id);
        }
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene5 setup" << _serial->test << endl;
        scene_index = 0;
    }

    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            doIndexRandom();
            int select_id = (int)ofRandom(ball_num);
            for (int i = 0; i < ball_num; i++) {
                if (i == select_id) {
                    (*_ball)[i].color = color[randomIndex[i]];
                    (*_ball)[i].fadeInOut(fadeTime, true);
                } else {
                    (*_ball)[i].color = ofColor(0, 0, 0);
                }
            }
            _serial->sendSerial(_hex->randomColor(select_id, fadeTime));
            cout << " ballscene5 fadein" << endl;
            scene_index = 1;
        } else if (scene_index == 1) {
            if (now > fadeTime - 30) {
                _serial->sendSerial(_hex->changeColor(select_id, ofColor(0, 0, 0), fadeTime));
                for (int i = 0; i < ball_num; i++) {
                    if (i == select_id) {
                        (*_ball)[i].fadeInOut(fadeTime, false);
                    }
                }
                cout << " ballscene5 fadeout" << endl;
                scene_index = 2;
            }
        } else if (scene_index == 2 && loop) {
            if (now > fadeTime * 2 - 30) {
                scene_index = 0;
                startTime = ofGetElapsedTimeMillis();
//                for (int i = 0; i < ball_num; i++) {
//                    int color_num = (int)ofRandom(getColorNum());
//                    color[i] = getColorPattern(color_num);
//                }
            }
        }
    }

    void doIndexRandom() {
        for(int i=0;i<ball_num;i++){
            int random = (int)ofRandom(ball_num);
            int tmp = randomIndex[i];
            randomIndex[i] = randomIndex[random];
            randomIndex[random] = tmp;
        }
    }
    
   private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    vector<ofColor> color;
    vector<int> randomIndex;
    vector<int> _id;
    int fadeTime;
    bool loop;
    int select_id;
};

//====================================================================
//
// BallScene6 -> selectColorChange : group only fade in
//
//====================================================================
class BallScene6 : public BallBaseScene {
   public:
    void setup(SerialCommunication *_serial, ofColor _color, ofColor _color2, int _fadeTime, bool _loop) {
        fadeTime = _fadeTime;
        loop = _loop;
        color = _color;
        color2 = _color2;
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene1 setup" << _serial->test << endl;
        scene_index = 0;
        count = 0;
    }

    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        ball_num = (*_ball)[0].total_ball_num;
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            if (count == 0) {
                for (int i = 0; i < ball_num; i++) {
                    if (i % 2 == 0) {
                        (*_ball)[i].color = color;
                    } else {
                        (*_ball)[i].color = color2;
                    }
                    (*_ball)[i].fadeInOut(fadeTime, true);
                }
                cout << " ballscene1 fadein" << endl;
            }
            if (count % 2 == 0) {
                _serial->sendSerial(_hex->changeGroupColor(1, ofColor(color), fadeTime));
            } else {
                _serial->sendSerial(_hex->changeGroupColor(2, ofColor(color2), fadeTime));
            }
            count++;
            if (count > 3) {
                scene_index = 1;
                count = 0;
            }
        } else if (scene_index == 1) {
            if (now > fadeTime - 30) {
                _serial->sendSerial(_hex->changeColor(ofColor(0, 0, 0), fadeTime));
                for (int i = 0; i < ball_num; i++) {
                    if (i % 2 == 0) {
                        (*_ball)[i].color = color;
                    } else {
                        (*_ball)[i].color = color2;
                    }
                    (*_ball)[i].fadeInOut(fadeTime, false);
                }
                cout << " ballscene1 fadeout" << endl;
                scene_index = 2;
            }
        } else if (scene_index == 2 && loop) {
            if (now > fadeTime * 2 - 30) {
                ofColor tmp;
                tmp = color;
                color = color2;
                color2 = tmp;
                scene_index = 0;
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }

   private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    ofColor color;
    ofColor color2;
    int fadeTime;
    bool loop;
    int count;
};

//====================================================================
//
// BallScene7 -> randomColorChange : only fade out
//
//====================================================================
class BallScene7 : public BallBaseScene {
public:
    void setup(SerialCommunication *_serial, vector<BallManagement> *_ball, int _fadeTime) {
        fadeTime = _fadeTime;
        cout << "FADE TIME : " << fadeTime << endl;
        ball_num = (*_ball)[0].total_ball_num;
        for (int i = 0; i < ball_num; i++) {
            randomIndex.push_back(i);
            color.push_back(getColorPattern(i));
        }
        _hex = new Hex();
        cout << "BallScene7 setup" << _serial->test << endl;
        scene_index = 0;
    }
    
    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        if (scene_index == 0) {
            doIndexRandom();
            for (int i = 0; i < ball_num; i++) {
                (*_ball)[i].color = color[randomIndex[i]];
                (*_ball)[i].fadeInOut(fadeTime, false);
            }
            _serial->sendSerial(_hex->randomColor(fadeTime));
            cout << " ballscene7 fadeout" << endl;
            scene_index = 1;
        }
    }
    
    void doIndexRandom() {
        for(int i=0;i<ball_num;i++){
            int random = (int)ofRandom(ball_num);
            int tmp = randomIndex[i];
            randomIndex[i] = randomIndex[random];
            randomIndex[random] = tmp;
        }
    }
    
private:
    int scene_index;
    Hex *_hex;
    int ball_num;
    vector<ofColor> color;
    vector<int> randomIndex;
    int fadeTime;
};

//====================================================================
//
// BallScene8 -> selectColorChange : onlyFadeOut
//
//====================================================================
class BallScene8 : public BallBaseScene {
public:
    void setup(SerialCommunication *_serial, ofColor _color, int _fadeTime) {
        fadeTime = _fadeTime;
        color = _color;
        _hex = new Hex();
        startTime = ofGetElapsedTimeMillis();
        cout << "BallSCene8 setup" << _serial->test << endl;
        scene_index = 0;
    }
    
    void update(SerialCommunication *_serial, vector<BallManagement> *_ball) {
        ball_num = (*_ball)[0].total_ball_num;
        int now = ofGetElapsedTimeMillis() - startTime;
        if (scene_index == 0) {
            for (int i = 0; i < ball_num; i++) {
                (*_ball)[i].color = color;
//                (*_ball)[i].fadeInOut(fadeTime, true);
            }
            _serial->sendSerial(_hex->changeColor(ofColor(color)));
            cout << " ballscene8 fadein" << endl;
            scene_index = 1;
        } else if (scene_index == 1) {
            if (now > 150) {
                _serial->sendSerial(_hex->changeColor(ofColor(0, 0, 0), fadeTime));
                for (int i = 0; i < ball_num; i++) {
                    (*_ball)[i].color = ofColor(color);
                    (*_ball)[i].fadeInOut(fadeTime, false);
                }
                cout << " ballscene8 fadeout" << endl;
                scene_index = 2;
            }
        }
    }
    
private:
    int scene_index;
    int startTime;
    Hex *_hex;
    int ball_num;
    ofColor color;
    int fadeTime;
};




#endif /* sceneContents_hpp */
