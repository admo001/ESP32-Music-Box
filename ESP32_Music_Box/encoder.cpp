#include "encoder.h"
#include "player.h"
#include "songs.h"

RotaryEncoder encoder;

byte RotaryEncoder::abOld = 0;
volatile int RotaryEncoder::count = 0;
int RotaryEncoder::isrPinA = 32;
int RotaryEncoder::isrPinB = 33;

RotaryEncoder::RotaryEncoder(int a, int b, int btn)
    : pinA(a), pinB(b), pinButton(btn) {}

void RotaryEncoder::begin() {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    pinMode(pinButton, INPUT_PULLUP);

    isrPinA = pinA;
    isrPinB = pinB;

    byte a = digitalRead(pinA);
    byte b = digitalRead(pinB);
    abOld = (a << 1) | b;
    count = 0;
    lastCount = 0;

    // Pin-change interrupts fire the instant a transition happens, even
    // while loop() is stuck inside a blocking i2s_write() call during
    // playNote(). That's what polling in update() could never do - it
    // was only ever able to check the pins in the short gap between notes.
    attachInterrupt(digitalPinToInterrupt(pinA), pinChangeISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinB), pinChangeISR, CHANGE);

    Serial.println("Rotary Encoder Initialized (Interrupt Quadrature Decoder)");
}

// Classic full-step quadrature decode via lookup mask, adapted to run as
// a static ISR. Every 2-bit state transition (00/01/11/10) is scored
// against upMask/downMask to determine direction without needing delays
// or timing-based debounce - the pin state itself is the debounce.
void IRAM_ATTR RotaryEncoder::pinChangeISR() {
    enum { upMask = 0x66, downMask = 0x99 };
    byte abNew = (digitalRead(isrPinA) << 1) | digitalRead(isrPinB);
    byte criterion = abNew ^ abOld;

    if (criterion == 1 || criterion == 2) {
        if (upMask & (1 << (2 * abOld + abNew / 2)))
            count++;
        else
            count--;   // upMask = ~downMask
    }
    abOld = abNew;
}

void RotaryEncoder::update() {
    // Snapshot the volatile count once, then just react to how far it's
    // moved since last time. Most encoders produce 4 count changes per
    // physical detent/click.
    int current = count;
    int delta = current - lastCount;

    while (delta >= 4) {
        onRotateRight();
        lastCount += 4;
        delta -= 4;
    }
    while (delta <= -4) {
        onRotateLeft();
        lastCount -= 4;
        delta += 4;
    }

    // The button is a simple mechanical switch, not a quadrature signal,
    // so plain time-based debounce is fine here.
    if (digitalRead(pinButton) == LOW && millis() - lastButtonPress > 200) {
        onButtonPress();
        lastButtonPress = millis();
    }
}

void RotaryEncoder::onRotateLeft() {
    Serial.println("← Previous Song");
    player.playPrevious();
}

void RotaryEncoder::onRotateRight() {
    Serial.println("→ Next Song");
    player.playNext();
}

void RotaryEncoder::onButtonPress() {
    Serial.println("🔘 Play/Pause");
    if (player.getState() == PlayState::PLAYING) {
        player.stop();
    } else {
        player.play(songList[player.getCurrentSongIndex()]);
    }
}