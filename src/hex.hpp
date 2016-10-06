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
    
    vector<Byte> readProfile(){
        vector<Byte> tmp_byte;
        tmp_byte.push_back(0x5A);
        tmp_byte.push_back(0xA5);
        tmp_byte.push_back(0x07);  // command
        tmp_byte.push_back(0x01);  // length
        tmp_byte.push_back(0x01);
        return tmp_byte;
    }

    vector<Byte> randomColor() {
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
        tmp_byte.push_back(0x01);  //
        tmp_byte.push_back(0x00);  //R
        tmp_byte.push_back(0x00);  //G
        tmp_byte.push_back(0xFF);  //B
        tmp_byte.push_back(0x01);  //fade time (high)
        tmp_byte.push_back(0xF4);  //fade time (low)
        
        return tmp_byte;
    }
    
    vector<Byte> setNode(int node){
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
    
    vector<Byte> lightoff(){
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
        tmp_byte.push_back(0x00);//R
        tmp_byte.push_back(0x00);//G
        tmp_byte.push_back(0x00);//B
        
        return tmp_byte;
    }
    
    vector<Byte> setBreathMode(){
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
    
    vector<Byte> changeColor(int r,int g,int b){
        vector<Byte> tmp_byte;
        
        
        
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
