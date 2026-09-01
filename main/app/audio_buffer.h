#pragma once

#include <stdint.h>

#define SYSTEM_CHANNEL 0
#define AUDIO_CHANNEL 1
#define AUDIO_BITS_PER_SAMPLE 16
#define AUDIO_CHANNELS 1

// Shared static buffer used by the S2S speaker ring buffer.
// Sized for ~2.7s of 24kHz 16-bit mono output to eliminate jitter and audio stutter.
#define AUDIO_BUFFER_SIZE (1024 * 128)

extern uint8_t audio_buffer[AUDIO_BUFFER_SIZE];
