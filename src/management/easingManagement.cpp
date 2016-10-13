//
//  easingManagement.cpp
//  teamLabBall_worldForum
//
//  Created by 松岡正 on 2016/10/09.
//
//

#include "easingManagement.hpp"

//--------------------------------------------------------------
void easingManagement::setParam(int durationTimeMillis, int delayTimeMillis, float begin, float end) {
    _durationTimeMillis = durationTimeMillis;
    _delayTimeMillis = delayTimeMillis;
    _val_begin = begin;
    _val_end = end;
    
    _currentEasing = easingOutSINE;
}

//--------------------------------------------------------------
void easingManagement::setParam(int durationTimeMillis, int delayTimeMillis, float begin, float end, E_EASING easing) {
    _durationTimeMillis = durationTimeMillis;
    _delayTimeMillis = delayTimeMillis;
    _val_begin = begin;
    _val_end = end;
    
    _currentEasing = easing;
}

//--------------------------------------------------------------
void easingManagement::update() {
    if (_tweenUpdateEnabled) {
        _val = tween(_beginTimeMillis, _durationTimeMillis, _delayTimeMillis, _val_begin, _val_end, _currentEasing);
        
        int currentTime = ofGetElapsedTimeMillis() - _beginTimeMillis - _delayTimeMillis;
        
        if (currentTime > _durationTimeMillis) {
            _tweenUpdateEnabled = false;
            _tweenCompleted = true;
        }
    }
}

//--------------------------------------------------------------
float easingManagement::tween(int beginTimeMillis, int durationMillis, int delayTimeMillis, float valBegin, float valEnd, E_EASING easing) {
    switch (easing) {
        case easingInLINEAR:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::linear::easeIn);
            break;
        case easingInQUAD:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::quad::easeIn);
            break;
        case easingInCUBIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::cubic::easeIn);
            break;
        case easingInQUART:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::quart::easeIn);
            break;
        case easingInQUINT:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::quint::easeIn);
            break;
        case easingInCIRC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::circ::easeIn);
            break;
        case easingInSINE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::sine::easeIn);
            break;
        case easingInEXP:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::exp::easeIn);
            break;
        case easingInELASTIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::elastic::easeIn);
            break;
        case easingInBOUNCE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::bounce::easeIn);
            break;
        case easingInBACK:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::back::easeIn);
            break;
        case easingOutLINEAR:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::linear::easeOut);
            break;
        case easingOutQUAD:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::quad::easeOut);
            break;
        case easingOutCUBIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::cubic::easeOut);
            break;
        case easingOutQUART:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::quart::easeOut);
            break;
        case easingOutQUINT:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::quint::easeOut);
            break;
        case easingOutCIRC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::circ::easeOut);
            break;
        case easingOutSINE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::sine::easeOut);
            break;
        case easingOutEXP:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::exp::easeOut);
            break;
        case easingOutELASTIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::elastic::easeOut);
            break;
        case easingOutBOUNCE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::bounce::easeOut);
            break;
        case easingOutBACK:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() - beginTimeMillis, delayTimeMillis, durationMillis + delayTimeMillis, valBegin, valEnd, &ofxeasing::back::easeOut);
            break;
    }
}

//--------------------------------------------------------------
float easingManagement::tweenVirtual(int millis)
{
    switch (_currentEasing) {
        case easingInLINEAR:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::linear::easeIn);
            break;
        case easingInQUAD:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::quad::easeIn);
            break;
        case easingInCUBIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::cubic::easeIn);
            break;
        case easingInQUART:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::quart::easeIn);
            break;
        case easingInQUINT:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::quint::easeIn);
            break;
        case easingInCIRC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::circ::easeIn);
            break;
        case easingInSINE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::sine::easeIn);
            break;
        case easingInEXP:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::exp::easeIn);
            break;
        case easingInELASTIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::elastic::easeIn);
            break;
        case easingInBOUNCE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::bounce::easeIn);
            break;
        case easingInBACK:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::back::easeIn);
            break;
        case easingOutLINEAR:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::linear::easeOut);
            break;
        case easingOutQUAD:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::quad::easeOut);
            break;
        case easingOutCUBIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::cubic::easeOut);
            break;
        case easingOutQUART:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::quart::easeOut);
            break;
        case easingOutQUINT:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::quint::easeOut);
            break;
        case easingOutCIRC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::circ::easeOut);
            break;
        case easingOutSINE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::sine::easeOut);
            break;
        case easingOutEXP:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::exp::easeOut);
            break;
        case easingOutELASTIC:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::elastic::easeOut);
            break;
        case easingOutBOUNCE:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::bounce::easeOut);
            break;
        case easingOutBACK:
            return ofxeasing::map_clamp(ofGetElapsedTimeMillis() + millis - _beginTimeMillis, _delayTimeMillis, _durationTimeMillis + _delayTimeMillis, _val_begin, _val_end, &ofxeasing::back::easeOut);
            break;
    }
}
