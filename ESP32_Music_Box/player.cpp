#include "player.h"
#include "audio.h"
#include "songs.h"
#include <Arduino.h>

MusicPlayer player;

const Melody* songList[] = { &happyBirthday, &furElise, &odeToJoy, &twinkleTwinkle };
const int totalSongs = 4;

void MusicPlayer::begin() {
    Serial.println("Single-Note Classical Player Ready");
}

void MusicPlayer::play(const Melody* melody) {
    stop();
    currentMelody = melody;
    currentNote = 0;
    state = PlayState::PLAYING;
    lastNoteTime = millis();
    Serial.printf("▶ Playing: %s\n", melody->name);
}

void MusicPlayer::playNext() {
    currentSongIndex = (currentSongIndex + 1) % totalSongs;
    play(songList[currentSongIndex]);
}

void MusicPlayer::playPrevious() {
    currentSongIndex = (currentSongIndex - 1 + totalSongs) % totalSongs;
    play(songList[currentSongIndex]);
}

void MusicPlayer::stop() {
    state = PlayState::STOPPED;
    currentNote = 0;
}

void MusicPlayer::update() {
    if (state != PlayState::PLAYING || !currentMelody) return;

    unsigned long now = millis();
    if (now - lastNoteTime >= (unsigned long)currentMelody->durations[currentNote]) {
        lastNoteTime = now;

        float freq = currentMelody->notes[currentNote];
        float bassFreq;

        if (currentMelody == &furElise) {
            int bassIndex = currentNote % 16;
            bassFreq = furEliseBass[bassIndex];
        } else {
            // No dedicated harmony written for this song - thicken the
            // tone with a soft octave-down instead of leaving it bare.
            bassFreq = freq * 0.5f;
        }

        playNote(freq, bassFreq, currentMelody->durations[currentNote]);

        currentNote = (currentNote + 1) % currentMelody->noteCount;
        if (currentNote == 0) {
            Serial.printf("Looping %s...\n", currentMelody->name);
        }
    }
}

const char* MusicPlayer::getCurrentSongName() const {
    return currentMelody ? currentMelody->name : "None";
}