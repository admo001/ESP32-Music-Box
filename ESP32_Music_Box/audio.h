#ifndef AUDIO_H
#define AUDIO_H

void audioBegin();
void playNote(float freq, float bassFreq, int durationMs);
void audioUpdate();

#endif