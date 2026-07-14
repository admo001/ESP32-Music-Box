#ifndef SONGS_H
#define SONGS_H

#include <Arduino.h>

struct Melody {
    const char* name;
    const float* notes;
    const int* durations;
    uint16_t noteCount;
};

// Songs
#include "fur_elise.h"
#include "ode_to_joy.h"
#include "happy_birthday.h"
#include "twinkle.h"

extern const Melody furElise;
extern const Melody odeToJoy;
extern const Melody happyBirthday;
extern const Melody twinkleTwinkle;

extern const Melody* songList[];
extern const int totalSongs;

#endif