#ifndef TWINKLE_TWINKLE_H
#define TWINKLE_TWINKLE_H
 
#include "songs.h"
 

const float twinkleTwinkleNotes[] = {
    261.63,261.63,392.00,392.00,440.00,440.00,392.00,
    349.23,349.23,329.63,329.63,293.66,293.66,261.63,
    392.00,392.00,349.23,349.23,329.63,329.63,293.66,
    392.00,392.00,349.23,349.23,329.63,329.63,293.66,
    261.63,261.63,392.00,392.00,440.00,440.00,392.00,
    349.23,349.23,329.63,329.63,293.66,293.66,261.63
};
 
const int twinkleTwinkleDurations[] = {
    400,400,400,400,400,400,700,
    400,400,400,400,400,400,700,
    400,400,400,400,400,400,700,
    400,400,400,400,400,400,700,
    400,400,400,400,400,400,700,
    400,400,400,400,400,400,700
};
 
const Melody twinkleTwinkle = {
    "Twinkle Twinkle",
    twinkleTwinkleNotes,
    twinkleTwinkleDurations,
    sizeof(twinkleTwinkleNotes)/sizeof(twinkleTwinkleNotes[0])
};
 
#endif
 
