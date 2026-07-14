#include "audio.h"
#include "player.h"
#include "songs.h"
#include "encoder.h"

void setup() {
    Serial.begin(115200);
    audioBegin();
    player.begin();
    encoder.begin();
    
    Serial.println("ESP32 Classical Music Box Ready!");
    Serial.println("Press the encoder button to start playback.");
}

void loop() {
    player.update();
    encoder.update();
    audioUpdate();
}