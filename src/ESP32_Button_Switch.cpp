/*
  ESP32_Button_Switch.cpp - for Arduino core for the ESP32.
  Beta version 1.0
  
The MIT License (MIT)

Copyright (c) 2018 Mgo-tec. All rights reserved.
Blog URL ---> https://www.mgo-tec.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ESP32_Button_Switch.h"

ESP32_Button_Switch::ESP32_Button_Switch(){};

//****************************************
uint8_t ESP32_Button_Switch::Button(uint8_t num, const uint8_t gpio, boolean continuous_set, uint32_t chatter_time, uint32_t long_press_time){
  uint8_t ret_state = _Release;
  switch( digitalRead(gpio) ){
    case 0: // LOW = 0
      switch ( _button_status[num] ){
        case _Release:
          _button_status[num] = _ON_start;
          _button_start_time[num] = millis(); //reset start_time
          break;
        case _ON_start:
          if( continuous_set ){             
            if( Time_Mesure(_button_start_time[num]) > long_press_time ){
              _button_status[num] = _ContPress;
            }
          }else{
            if( Time_Mesure(_button_start_time[num]) > long_press_time ){
              _button_status[num] = _LongPress;
              ret_state = _LongPress;
            }
          }
          break;
        case _ContPress:
          if( Time_Mesure(_button_start_time[num]) > long_press_time ){
            _button_start_time[num] = millis(); //reset start_time
            return _ContPress;
          }
          break;
        default:
          break;
      }
      break;
    case 1: // HIGH = 1
      if( _button_status[num] == _ON_start ){
        if( Time_Mesure(_button_start_time[num]) > chatter_time ){
          ret_state = _MomentPress;
        }
      }
      _button_status[num] = _Release;
      break;
    default:
      break;
  }
  return ret_state;
}
//******************************************
uint32_t ESP32_Button_Switch::Time_Mesure( uint32_t st_time ){
  return millis() - st_time;
}
