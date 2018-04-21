/*
  ESP32_Button_Switch.h - for Arduino core for the ESP32.
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

#ifndef _ESP32_BUTTON_SWITCH_H_INCLUDED
#define _ESP32_BUTTON_SWITCH_H_INCLUDED

#include <Arduino.h>

enum BTN_STATUS { _Release, _ON_start, _MomentPress, _LongPress, _ContPress };

class ESP32_Button_Switch
{
private:
  #define BUTTON_MAX_NUM 5
  uint32_t _button_start_time[ BUTTON_MAX_NUM ] = {};
  uint8_t _button_status[ BUTTON_MAX_NUM ] = {};

  uint32_t Time_Mesure( uint32_t st_time );

public:
  ESP32_Button_Switch();

  uint8_t Button(uint8_t num, const uint8_t gpio, boolean continuous_set, uint32_t chatter_time, uint32_t long_press_time);

};

#endif
