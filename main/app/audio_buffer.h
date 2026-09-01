#pragma once

#include <stdint.h>

#define SYSTEM_CHANNEL 0
#define AUDIO_CHANNEL 1
#define AUDIO_BITS_PER_SAMPLE 16
#define AUDIO_CHANNELS 1

// Sized for ~2.0s of 24kHz 16-bit mono output (fits comfortably in SRAM without BSS overflow)
#define AUDIO_BUFFER_SIZE (1024 * 96)

extern uint8_t audio_buffer[AUDIO_BUFFER_SIZE];
