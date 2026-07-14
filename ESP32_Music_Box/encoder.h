#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class RotaryEncoder {
private:
    int pinA, pinB, pinButton;
    unsigned long lastButtonPress = 0;
    int lastCount = 0;

    // ISR state has to be static: attachInterrupt needs a plain function
    // pointer, so it can't be a normal (non-static) member function.
    static byte abOld;
    static volatile int count;
    static int isrPinA, isrPinB;

    static void IRAM_ATTR pinChangeISR();

public:
    RotaryEncoder(int a = 32, int b = 33, int btn = 14);
    void begin();
    void update();

    void onRotateLeft();
    void onRotateRight();
    void onButtonPress();
};

extern RotaryEncoder encoder;

#endif