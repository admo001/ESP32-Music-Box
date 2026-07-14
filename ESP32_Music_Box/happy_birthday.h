#ifndef HAPPY_BIRTHDAY_H
#define HAPPY_BIRTHDAY_H

#include "songs.h"

const float happyBirthdayNotes[] = {
    262, 262, 294, 262, 349, 330,     
    262, 262, 294, 262, 392, 349,     
    262, 262, 523, 440, 349, 330, 294, 
    466, 466, 440, 349, 392, 349      
};

const int happyBirthdayDurations[] = {
    250, 250, 500, 500, 500, 750,
    250, 250, 500, 500, 500, 750,
    250, 250, 500, 500, 500, 500, 750,
    250, 250, 500, 500, 500, 750
};

const Melody happyBirthday = {
    "Happy Birthday",
    happyBirthdayNotes,
    happyBirthdayDurations,
    sizeof(happyBirthdayNotes)/sizeof(happyBirthdayNotes[0])
};

#endif