/*
||
|| @file Button.cpp
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

//include the class definition
#include "bpButton.h"

/*
|| <<constructor>>
|| @parameter buttonPin sets the pin that this switch is connected to
|| @parameter buttonMode indicates PULLUP or PULLDOWN resistor
*/

//########################################
// class Button
//########################################


Button::Button() {
}

Button::Button(uint8_t buttonPin, uint8_t buttonMode) {
  pin = buttonPin;
  mode = buttonMode;
  pinMode(pin, INPUT);
  digitalWrite(pin, mode);
  state = 0;
  bitWrite(state, CURRENT, mode);
}

bool Button::read(void) {
  bool result = digitalRead(pin);
  bitWrite(state, RAWOLD, bitRead(state, RAW));
  bitWrite(state, RAW, result);
  if ((result != bitRead(state, RAWOLD)) ) {
    t_debounce.start();
    bitWrite(state, DEBOUNCING, 1);
    bitWrite(state, PREVIOUS, bitRead(state, CURRENT));
  } else if (bitRead(state, DEBOUNCING) && t_debounce.hasElapsed()) {
    bitWrite(state, DEBOUNCING, 0);
    bitWrite(state, CURRENT, bitRead(state, RAW));
    bitWrite(state, RISING, (!bitRead(state, PREVIOUS) && bitRead(state, CURRENT)));
    bitWrite(state, FALLING, (bitRead(state, PREVIOUS) && !bitRead(state, CURRENT)));
  } else {
    bitWrite(state, RISING, 0);
    bitWrite(state, FALLING, 0);
  }
  return (bitRead(state, CURRENT));
}

bool Button::isPressed(void) {
  return(bitRead(state, CURRENT));
}

bool Button::operated(void) {
  return(bitRead(state, RISING));
}

bool Button::released(void) {
  return(bitRead(state, FALLING));
}

bool Button::hasChanged(void) {
  return(bitRead(state, RISING) || bitRead(state, FALLING));
}

bool Button::rawValue(void) {
  return(bitRead(state, RAW));
}

//########################################
// class Pushbutton
//########################################

Pushbutton::Pushbutton(){
}

Pushbutton::Pushbutton(uint8_t buttonPin, uint8_t buttonMode, unsigned long longTime) {
//  Button::Button(buttonPin, buttonMode);
  pin = buttonPin;
  mode = buttonMode;
  pinMode(pin, INPUT);
  digitalWrite(pin, mode);
  state = 0;
  bitWrite(state, CURRENT, mode);

  longtime = longTime;
  push_state = PUSHBUTTON_UP;
  t_push = Timer::Timer(longtime);
}

int Pushbutton::read(void) {
  Button::read();
  if (operated()) {
    t_push.start();
  } else if (t_push.hasElapsed() && isPressed()) {
    t_push.stop();
    return(LONG_PRESSED);
  } else if (released()) {
	return(SHORT_PRESSED);
  }
  return(NOT_PRESSED);
}
