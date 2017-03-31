/*
||
|| @file Button.h
|| @version 1.6
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making buttons
|| #
||
|| @license
|| | Copyright (c) 2009 Alexander Brevig. All rights reserved.
|| | This code is subject to AlphaLicence.txt
|| | alphabeta.alexanderbrevig.com/AlphaLicense.txt
|| #
||
*/

#ifndef bpBUTTON_H
#define bpBUTTON_H

#include "Arduino.h"
#include "bpTimer.h"

#define PULLUP HIGH
#define PULLDOWN LOW
#define NOT_PRESSED 0
#define SHORT_PRESSED 1
#define LONG_PRESSED 2

#define PUSHBUTTON_UP 0
#define PUSHBUTTON_DOWN 1

#define RAW 0
#define RAWOLD 1
#define DEBOUNCING 2
#define CURRENT 3
#define PREVIOUS 4
#define RISING 5
#define FALLING 6

#define DEBOUNCE_TIME 50 // 50 ms seems to work well...

class Button {
  public:
    Button();
    Button(uint8_t buttonPin, uint8_t buttonMode=PULLDOWN);
    bool read();
    bool isPressed();
    bool operated();
    bool released();
    bool hasChanged();
    bool rawValue();

  protected: 
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    Timer t_debounce = Timer::Timer(DEBOUNCE_TIME);
};


class Pushbutton : public Button::Button {
  public:
    Pushbutton();
    Pushbutton(uint8_t buttonPin, uint8_t buttonMode, unsigned long longTime);
    int read(void);
  protected:
    unsigned long longtime;
    Timer t_push;
    uint8_t push_state;
};


#endif

/*
|| @changelog
|| | 1.6 2009-05-05 - Alexander Brevig : Added uniquePress, it returns true if the state has changed AND the button is pressed
|| | 1.5 2009-04-24 - Alexander Brevig : Added stateChanged, @contribution http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=klickadiklick
|| | 1.4 2009-04-24 - Alexander Brevig : Added wasPressed, @contribution http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=klickadiklick
|| | 1.3 2009-04-12 - Alexander Brevig : Added constructor with one parameter Button(uint8_t buttonPin)
|| | 1.2 2009-04-10 - Alexander Brevig : Namechange from Switch to Button
|| | 1.1 2009-04-07 - Alexander Brevig : Altered API
|| | 1.0 2008-10-23 - Alexander Brevig : Initial Release
|| #
*/
