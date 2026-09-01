#pragma once

#include "hal/hal.h"
#include <cstdint>

// Adventure Time BMO Authentic Color Palette
// Background: Teal/Mint Green (#82D2BA / RGB 130, 210, 186)
#define BMO_COLOR_BG       0x8697  // 16-bit RGB565 for #82D2BA
// Facial Features: Dark Cyan/Teal (#1A2D30 / RGB 26, 45, 48)
#define BMO_COLOR_FEATURE  0x1966  // 16-bit RGB565 for #1A2D30
// Blush / Accent: Soft Mint (#A1DFCD / RGB 161, 223, 205)
#define BMO_COLOR_BLUSH    0xA6FB  // 16-bit RGB565 for #A1DFCD
// Tongue / Mouth Inside: Coral Pink (#E88B98 / RGB 232, 139, 152)
#define BMO_COLOR_TONGUE   0xE473  // 16-bit RGB565 for #E88B98

namespace BMO
{
    class BMOFace
    {
    private:
        uint32_t _last_blink_time = 0;
        uint32_t _blink_duration = 140; // ms
        uint32_t _next_blink_interval = 3500; // ms
        bool _is_blinking = false;

        uint32_t _mouth_anim_time = 0;
        uint8_t _mouth_frame = 0;

        void drawEyeLeft(LGFX_Sprite* canvas, int cx, int cy, int state, bool blinking, uint32_t now);
        void drawEyeRight(LGFX_Sprite* canvas, int cx, int cy, int state, bool blinking, uint32_t now);
        void drawMouth(LGFX_Sprite* canvas, int cx, int cy, int state, uint32_t now);
        void drawBlushes(LGFX_Sprite* canvas, int w, int h);

    public:
        BMOFace();
        ~BMOFace();

        void reset();
        void render(LGFX_Sprite* canvas, int appState, uint32_t now);
    };
}
