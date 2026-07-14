#ifndef ODE_TO_JOY_H
#define ODE_TO_JOY_H

#include "songs.h"

const float odeToJoyNotes[] = {
    329.63, 329.63, 349.23, 392.00, 392.00, 349.23, 329.63, 293.66,
    261.63, 261.63, 293.66, 329.63, 329.63, 293.66, 293.66,
    
    329.63, 329.63, 349.23, 392.00, 392.00, 349.23, 329.63, 293.66,
    261.63, 261.63, 293.66, 329.63, 293.66, 261.63, 261.63
};

const int odeToJoyDurations[] = {
    300, 300, 300, 300, 300, 300, 300, 300,
    300, 300, 300, 300, 450, 150, 600,
    
    300, 300, 300, 300, 300, 300, 300, 300,
    300, 300, 300, 300, 450, 150, 600
};

const Melody odeToJoy = {
    "Ode to Joy",
    odeToJoyNotes,
    odeToJoyDurations,
    sizeof(odeToJoyNotes)/sizeof(odeToJoyNotes[0])
};

#endif