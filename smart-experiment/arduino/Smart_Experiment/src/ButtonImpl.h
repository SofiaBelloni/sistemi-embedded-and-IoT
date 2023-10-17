#ifndef __BUTTON_IMPL__
#define __BUTTON_IMPL__

#include "Button.h"

class ButtonImpl: public Button {
public: 
  ButtonImpl(int pin);
  bool isPressed();
private:
  int pin;
};

#endif
