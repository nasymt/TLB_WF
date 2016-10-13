//
//  easingManagement.hpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/09.
//
//

#ifndef easingManagement_hpp
#define easingManagement_hpp

#include "ofMain.h"
#include "ofxEasing.h"

enum E_EASING {
    easingInLINEAR = 0,
    easingInQUAD = 1,
    easingInCUBIC = 2,
    easingInQUART = 3,
    easingInQUINT = 4,
    easingInCIRC = 5,
    easingInSINE = 6,
    easingInEXP = 7,
    easingInELASTIC = 8,
    easingInBOUNCE = 9,
    easingInBACK = 10,
    easingOutLINEAR = 11,
    easingOutQUAD = 12,
    easingOutCUBIC = 13,
    easingOutQUART = 14,
    easingOutQUINT = 15,
    easingOutCIRC = 16,
    easingOutSINE = 17,
    easingOutEXP = 18,
    easingOutELASTIC = 19,
    easingOutBOUNCE = 20,
    easingOutBACK = 21
};

class easingManagement {
public:
    inline float getProgress() {
        _progress = ofMap(_val, _val_begin, _val_end, 0.0, 1.0);
        return _progress;
    };
    inline float getValue() { return _val; };
    inline float getValueVirtual(int millis) { return tweenVirtual(millis); };
    inline bool completed() { return _tweenCompleted; };
    inline void start() {
        _tweenUpdateEnabled = true;
        _tweenCompleted = false;
        _beginTimeMillis = ofGetElapsedTimeMillis();
    };
    inline void stop() { _tweenUpdateEnabled = false; };
    inline void pause(bool flag) {
        if (flag) {
            _tweenUpdateEnabled = false;
            _pauseAjustTimeMillis = ofGetElapsedTimeMillis() - _beginTimeMillis;
        } else {
            _tweenUpdateEnabled = true;
            _tweenCompleted = false;
            _beginTimeMillis = ofGetElapsedTimeMillis() - _pauseAjustTimeMillis;
        }
    };
    
    void setParam(int durationTimeMillis, int delayTimeMillis, float begin, float end);
    void setParam(int durationTimeMillis, int delayTimeMillis, float begin, float end, E_EASING easing);
    
    void update();
    
private:
    E_EASING _currentEasing;
    
    float _val;
    bool _tweenUpdateEnabled = false;
    bool _tweenCompleted = false;
    
    int _beginTimeMillis = 0;
    int _durationTimeMillis = 0;
    int _delayTimeMillis = 0;
    int _pauseAjustTimeMillis = 0;
    float _val_begin = 0;
    float _val_end = 0;
    float _progress = 0;
    
    float tween(int beginTimeMillis, int durationMillis, int delayTimeMillis, float valBegin, float valEnd, E_EASING easing);
    float tweenVirtual(int millis);
};

#endif /* easingManagement_hpp */
