#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "songs.h"

enum class PlayState { STOPPED, PLAYING, PAUSED };

class MusicPlayer {
private:
    PlayState state = PlayState::STOPPED;
    const Melody* currentMelody = nullptr;
    uint16_t currentNote = 0;
    unsigned long lastNoteTime = 0;
    int currentSongIndex = 0;

public:
    void begin();
    void update();
    void play(const Melody* melody);
    void playNext();
    void playPrevious();
    void stop();
    
    PlayState getState() const { return state; }
    int getCurrentSongIndex() const { return currentSongIndex; }  // Added this
    const char* getCurrentSongName() const;
};

extern MusicPlayer player;

#endif