#include "audio.h"
#include "driver/i2s.h"
#include <math.h>
#include <Arduino.h>

#define BCLK 26
#define LRC 25
#define DIN 27
#define SAMPLE_RATE 22050
#define BUFFER_SIZE 128

int16_t buffer[BUFFER_SIZE];
float MASTER_VOLUME = 0.55f;   // Overall output level

const float MELODY_LEVEL = 0.75f;  // mix weight of the melody voice
const float BASS_LEVEL   = 0.45f;  // mix weight of the bass/harmony voice

float envelope(int sample, int total) {
    float t = (float)sample / total;
    if (t < 0.08f) return t / 0.08f;           // Fast attack
    if (t < 0.45f) return 1.0f - ((t - 0.08f) * 1.8f); // Decay
    return 0.45f * (1.0f - t);                    // Gentle release
}


float bassEnvelope(int sample, int total) {
    float t = (float)sample / total;
    const float fade = 0.06f;
    if (t < fade) return t / fade;
    if (t > 1.0f - fade) return (1.0f - t) / fade;
    return 1.0f;
}

float pianoWave(float phase) {
    // Simple but nice piano-like tone
    return sinf(phase) * 0.82f + sinf(phase * 2.01f) * 0.18f;
}

float bassWave(float phase) {
    return sinf(phase) * 0.9f + sinf(phase * 2.0f) * 0.1f;
}

void audioBegin() {
    i2s_config_t config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pins = {
        .bck_io_num = BCLK,
        .ws_io_num = LRC,
        .data_out_num = DIN,
        .data_in_num = -1
    };

    i2s_driver_install(I2S_NUM_0, &config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pins);
    Serial.println("I2S Audio Initialized - Polyphonic Piano Mode");
}

void playNote(float freq, float bassFreq, int durationMs) {
    int totalSamples = SAMPLE_RATE * durationMs / 1000;
    float melodyPhase = 0.0f;
    float bassPhase = 0.0f;
    bool hasBass = bassFreq > 1.0f;   // 0 (or negative) means "no harmony note this beat"

    for (int i = 0; i < totalSamples; ) {
        int count = min(BUFFER_SIZE, totalSamples - i);
        for (int j = 0; j < count; j++) {
            int s = i + j;

            float melody = pianoWave(melodyPhase) * envelope(s, totalSamples) * MELODY_LEVEL;

            float bass = 0.0f;
            if (hasBass) {
                bass = bassWave(bassPhase) * bassEnvelope(s, totalSamples) * BASS_LEVEL;
            }

            float output = (melody + bass) * MASTER_VOLUME;


            if (output > 1.0f) output = 1.0f;
            if (output < -1.0f) output = -1.0f;

            buffer[j] = (int16_t)(output * 20000.0f);

            melodyPhase += 2.0f * M_PI * freq / SAMPLE_RATE;
            if (melodyPhase > 2.0f * M_PI) melodyPhase -= 2.0f * M_PI;

            if (hasBass) {
                bassPhase += 2.0f * M_PI * bassFreq / SAMPLE_RATE;
                if (bassPhase > 2.0f * M_PI) bassPhase -= 2.0f * M_PI;
            }
        }
        size_t written;
        i2s_write(I2S_NUM_0, buffer, count * sizeof(int16_t), &written, portMAX_DELAY);
        i += count;
    }
    delay(35);  // Short gap between notes
}

void audioUpdate() {
    // Future use
}