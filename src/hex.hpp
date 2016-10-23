//
//  hex.hpp
//  TLB_serialTest
//
//  Created by 松岡正 on 2016/10/06.
//
//

#ifndef hex_hpp
#define hex_hpp

#include "ofMain.h"

class Hex {
   public:
    vector<Byte> setChannel(int channel) {
        vector<Byte> tmp_byte;
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        tmp_byte.push_back(0x02);     // command
        tmp_byte.push_back(0x02);     // length
        tmp_byte.push_back(0x03);     // param No.
        tmp_byte.push_back(channel);  // channel
        return tmp_byte;
    }

    vector<Byte> connect() {
        vector<Byte> tmp_byte;
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        tmp_byte.push_back(0x0B);  // command
        tmp_byte.push_back(0x00);  // length
        return tmp_byte;
    }

    vector<Byte> readProfile() {
        vector<Byte> tmp_byte;
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        tmp_byte.push_back(0x07);  // command
        tmp_byte.push_back(0x01);  // length
        tmp_byte.push_back(0x01);
        return tmp_byte;
    }

    vector<Byte> changeColor(ofColor _color) {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);  // command
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x08);  // length
        //-----send option------
        tmp_byte.push_back(0x04);  //
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        //---ball send type-----
        tmp_byte.push_back(0xFF);  //
        //---ball send func-----
        tmp_byte.push_back(0x01);      //
        tmp_byte.push_back(_color.r);  // R
        tmp_byte.push_back(_color.g);  // G
        tmp_byte.push_back(_color.b);  // B
        return tmp_byte;
    }

    vector<Byte> changeColor(ofColor _color, int fade) {
        vector<int> fadeTime;
        fadeTime = convertHex(fade);

        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);  // command
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x0A);  // length
        //-----send option------
        tmp_byte.push_back(0x04);  //
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        //---ball send type-----
        tmp_byte.push_back(0xFF);  //
        //---ball send func-----
        tmp_byte.push_back(0x01);         //
        tmp_byte.push_back(_color.r);     // R
        tmp_byte.push_back(_color.g);     // G
        tmp_byte.push_back(_color.b);     // B
        tmp_byte.push_back(fadeTime[0]);  // fade time (high)
        tmp_byte.push_back(fadeTime[1]);  // fade time (low)
        return tmp_byte;
    }

    vector<Byte> changeColor(int _id, ofColor _color, int fade) {
        vector<int> fadeTime;
        fadeTime = convertHex(fade);
        vector<int> id_;
        id_ = convertHex(_id);

        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);  // command
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x0A);  // length
        //-----send option------
        tmp_byte.push_back(0x04);  //
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        //---ball send type-----
        tmp_byte.push_back(0xFE);  //
        tmp_byte.push_back(id_[0]);
        tmp_byte.push_back(id_[1]);
        //---ball send func-----
        tmp_byte.push_back(0x01);         //
        tmp_byte.push_back(_color.r);     // R
        tmp_byte.push_back(_color.g);     // G
        tmp_byte.push_back(_color.b);     // B
        tmp_byte.push_back(fadeTime[0]);  // fade time (high)
        tmp_byte.push_back(fadeTime[1]);  // fade time (low)
        return tmp_byte;
    }

    vector<Byte> changeGroupColor(int group_id, ofColor _color, int fade) {
        vector<int> fadeTime;
        fadeTime = convertHex(fade);
        vector<int> id_;
        id_ = convertHex(group_id);

        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);  // command
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x0B);  // length
        //-----send option------
        tmp_byte.push_back(0x04);  //
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        //---ball send type-----
        tmp_byte.push_back(group_id);  //
        tmp_byte.push_back(group_id);
        //---ball send func-----
        tmp_byte.push_back(0x01);         //
        tmp_byte.push_back(_color.r);     // R
        tmp_byte.push_back(_color.g);     // G
        tmp_byte.push_back(_color.b);     // B
        tmp_byte.push_back(fadeTime[0]);  // fade time (high)
        tmp_byte.push_back(fadeTime[1]);  // fade time (low)
        return tmp_byte;
    }

    vector<Byte> randomColor(int fade) {
        vector<int> fadeTime;
        fadeTime = convertHex(fade);

        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);  // command
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x07);  // length
        //-----send option------
        tmp_byte.push_back(0x04);  //
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        //---ball send type-----
        tmp_byte.push_back(0xFF);  //
        //---ball send func-----
        tmp_byte.push_back(0x01);         //
        tmp_byte.push_back(fadeTime[0]);  // fade time (high)
        tmp_byte.push_back(fadeTime[1]);  // fade time (low)

        return tmp_byte;
    }

    vector<Byte> randomColor(int _id, int fade) {
        vector<int> fadeTime;
        fadeTime = convertHex(fade);
        vector<int> id_;
        id_ = convertHex(_id);

        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);  // command
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x07);  // length
        //-----send option------
        tmp_byte.push_back(0x04);  //
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        tmp_byte.push_back(0xFF);  // send address(broadcast)
        //---ball send type-----
        tmp_byte.push_back(0xFE);
        tmp_byte.push_back(id_[0]);
        tmp_byte.push_back(id_[1]);
        //---ball send func-----
        tmp_byte.push_back(0x01);         //
        tmp_byte.push_back(fadeTime[0]);  // fade time (high)
        tmp_byte.push_back(fadeTime[1]);  // fade time (low)
        return tmp_byte;
    }

    vector<Byte> setNode(int node) {
        vector<Byte> tmp_byte;
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        tmp_byte.push_back(0x02);
        tmp_byte.push_back(0x03);
        tmp_byte.push_back(0x02);
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(node);
        return tmp_byte;
    }

    vector<Byte> lightoff() {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x08);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x01);
        tmp_byte.push_back(0x00);  // R
        tmp_byte.push_back(0x00);  // G
        tmp_byte.push_back(0x00);  // B

        return tmp_byte;
    }

    vector<Byte> setBreathMode() {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x06);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x0B);
        tmp_byte.push_back(0x01);

        return tmp_byte;
    }

    vector<Byte> setDirectAlpha(int alpha) {
        vector<Byte> tmp_byte;
        cout << "set Direct Alpha " << alpha << endl;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x08);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x09);
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x06);
//        tmp_byte.push_back(0x00);
        tmp_byte.push_back(alpha);

        return tmp_byte;
    }

    vector<int> convertHex(int val) {
        int tmp[5];
        int amari[4];
        tmp[0] = val;

        int hexnum[4];
        for (int i = 0; i < 4; i++) {
            tmp[i + 1] = (int)tmp[i] / 16;
            amari[i] = (int)tmp[i] % 16;
            hexnum[i] = amari[i];

            if (tmp[3] == 0) {
                hexnum[2] = amari[2];
            } else if (tmp[4] == 0 && tmp[3] > 0) {
                hexnum[3] = amari[3];
            }
        }

        int num_hi = hexnum[3] * 16 + hexnum[2];
        int num_low = hexnum[1] * 16 + hexnum[0];
        vector<int> _tmp;
        _tmp.push_back(num_hi);
        _tmp.push_back(num_low);
        return _tmp;
    }

    vector<Byte> setGroupId(int group_id) {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x11);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x09);
        tmp_byte.push_back(0x01);
        tmp_byte.push_back(0x21);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);
        tmp_byte.push_back(group_id);

        return tmp_byte;
    }

    vector<Byte> uartOverrunResend() {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x08);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x09);
        tmp_byte.push_back(0x01);
        tmp_byte.push_back(0x3f);
        tmp_byte.push_back(0x01);

        return tmp_byte;
    }

    vector<Byte> selectRandomColor(vector<bool> colorIndex) {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x09);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x09);
        tmp_byte.push_back(0x01);
        tmp_byte.push_back(0x09);
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x1E);

        return tmp_byte;
    }

    vector<Byte> sensorThreshold(int threshold) {
        vector<Byte> tmp_byte;
        //-----header-----------
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        //-----command----------
        tmp_byte.push_back(0x01);
        //-----length-----------
        tmp_byte.push_back(0x00);
        tmp_byte.push_back(0x09);
        //-----send option------
        tmp_byte.push_back(0x04);
        tmp_byte.push_back(0xFF);
        tmp_byte.push_back(0xFF);
        //---ball send type-----
        tmp_byte.push_back(0xFF);
        //---ball send func-----
        tmp_byte.push_back(0x09);
        tmp_byte.push_back(0x01);
        tmp_byte.push_back(0x13);
        tmp_byte.push_back(threshold);
        tmp_byte.push_back(0x00);

        return tmp_byte;
    }

    Byte checkSum(vector<Byte> _checksum) {
        Byte tmp = 0x00;
        for (int i = 0; i < _checksum.size(); i++) {
            tmp = tmp ^ _checksum[i];
        }
        return tmp;
    }

   private:
};

#endif /* hex_hpp */
