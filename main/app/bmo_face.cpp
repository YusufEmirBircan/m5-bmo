#include "bmo_face.h"
#include "gemini_app.h"
#include <cmath>

namespace BMO
{
    BMOFace::BMOFace()
    {
        reset();
    }

    BMOFace::~BMOFace()
    {
    }

    void BMOFace::reset()
    {
        _last_blink_time = 0;
        _next_blink_interval = 3000;
        _is_blinking = false;
        _mouth_anim_time = 0;
        _mouth_frame = 0;
    }

    void BMOFace::drawEyeLeft(LGFX_Sprite* canvas, int cx, int cy, int state, bool blinking, uint32_t now)
    {
        uint16_t color = BMO_COLOR_FEATURE;

        if (state == APP_STATE_S2S_ERROR || state == APP_STATE_DISCONNECTED)
        {
            // X Eye
            int s = 7;
            for (int t = -1; t <= 1; t++)
            {
                canvas->drawLine(cx - s + t, cy - s, cx + s + t, cy + s, color);
                canvas->drawLine(cx - s + t, cy + s, cx + s + t, cy - s, color);
            }
            return;
        }

        if (state == APP_STATE_S2S_SPEAKING)
        {
            // Happy inverted arch eyes: ^
            int r = 10;
            for (int t = 0; t <= 2; t++)
            {
                canvas->drawArc(cx, cy + 4, r, r - t, 200, 340, color);
            }
            return;
        }

        if (blinking)
        {
            // Closed eye line
            canvas->fillRect(cx - 7, cy - 1, 15, 3, color);
            return;
        }

        if (state == APP_STATE_S2S_LISTENING)
        {
            // Attentive bigger round/oval eyes slightly higher
            canvas->fillEllipse(cx, cy - 2, 7, 9, color);
            // Cute tiny sparkle/highlight
            canvas->fillCircle(cx - 2, cy - 5, 2, BMO_COLOR_BG);
            return;
        }

        if (state == APP_STATE_S2S_CONNECTING || state == APP_STATE_CONNECTING_WIFI)
        {
            // Thinking: looking sideways/up
            int x_shift = (int)(sinf(now / 350.0f) * 4.0f);
            canvas->fillEllipse(cx + x_shift, cy - 2, 6, 8, color);
            return;
        }

        // Default Idle / Ready state: Classic solid BMO oval eyes
        canvas->fillEllipse(cx, cy, 6, 8, color);
    }

    void BMOFace::drawEyeRight(LGFX_Sprite* canvas, int cx, int cy, int state, bool blinking, uint32_t now)
    {
        uint16_t color = BMO_COLOR_FEATURE;

        if (state == APP_STATE_S2S_ERROR || state == APP_STATE_DISCONNECTED)
        {
            // X Eye
            int s = 7;
            for (int t = -1; t <= 1; t++)
            {
                canvas->drawLine(cx - s + t, cy - s, cx + s + t, cy + s, color);
                canvas->drawLine(cx - s + t, cy + s, cx + s + t, cy - s, color);
            }
            return;
        }

        if (state == APP_STATE_S2S_SPEAKING)
        {
            // Happy inverted arch eyes: ^
            int r = 10;
            for (int t = 0; t <= 2; t++)
            {
                canvas->drawArc(cx, cy + 4, r, r - t, 200, 340, color);
            }
            return;
        }

        if (blinking)
        {
            // Closed eye line
            canvas->fillRect(cx - 7, cy - 1, 15, 3, color);
            return;
        }

        if (state == APP_STATE_S2S_LISTENING)
        {
            // Attentive bigger round/oval eyes
            canvas->fillEllipse(cx, cy - 2, 7, 9, color);
            canvas->fillCircle(cx - 2, cy - 5, 2, BMO_COLOR_BG);
            return;
        }

        if (state == APP_STATE_S2S_CONNECTING || state == APP_STATE_CONNECTING_WIFI)
        {
            // Thinking: looking sideways/up
            int x_shift = (int)(sinf(now / 350.0f) * 4.0f);
            canvas->fillEllipse(cx + x_shift, cy - 2, 6, 8, color);
            return;
        }

        // Default Idle
        canvas->fillEllipse(cx, cy, 6, 8, color);
    }

    void BMOFace::drawBlushes(LGFX_Sprite* canvas, int w, int h)
    {
        // Soft subtle mint cheek accents
        int y = h / 2 + 10;
        int lx = w / 2 - 62;
        int rx = w / 2 + 62;

        // 2 small cute parallel strokes on each cheek
        for (int i = 0; i < 2; i++)
        {
            canvas->drawLine(lx + i * 5, y, lx + 3 + i * 5, y + 6, BMO_COLOR_BLUSH);
            canvas->drawLine(lx + 1 + i * 5, y, lx + 4 + i * 5, y + 6, BMO_COLOR_BLUSH);

            canvas->drawLine(rx + i * 5, y, rx + 3 + i * 5, y + 6, BMO_COLOR_BLUSH);
            canvas->drawLine(rx + 1 + i * 5, y, rx + 4 + i * 5, y + 6, BMO_COLOR_BLUSH);
        }
    }

    void BMOFace::drawMouth(LGFX_Sprite* canvas, int cx, int cy, int state, uint32_t now)
    {
        uint16_t color = BMO_COLOR_FEATURE;

        if (state == APP_STATE_S2S_ERROR || state == APP_STATE_DISCONNECTED)
        {
            // Sad / glitch mouth: inverted curve
            for (int t = 0; t <= 2; t++)
            {
                canvas->drawArc(cx, cy + 18, 16, 16 - t, 210, 330, color);
            }
            return;
        }

        if (state == APP_STATE_S2S_SPEAKING)
        {
            // Talking animation cycle: 3 frames
            if (now - _mouth_anim_time > 130)
            {
                _mouth_anim_time = now;
                _mouth_frame = (_mouth_frame + 1) % 4;
            }

            if (_mouth_frame == 0)
            {
                // Frame 0: Medium open happy mouth (half circle filled with tongue)
                int mw = 18;
                int mh = 14;
                canvas->fillRoundRect(cx - mw/2, cy - 2, mw, mh, 7, color);
                // Inside tongue
                canvas->fillCircle(cx, cy + 6, 5, BMO_COLOR_TONGUE);
            }
            else if (_mouth_frame == 1)
            {
                // Frame 1: Wide open mouth (Big joyful BMO speech)
                int mw = 26;
                int mh = 18;
                canvas->fillRoundRect(cx - mw/2, cy - 3, mw, mh, 9, color);
                canvas->fillCircle(cx + 2, cy + 7, 7, BMO_COLOR_TONGUE);
            }
            else if (_mouth_frame == 2)
            {
                // Frame 2: Small round mouth 'o'
                canvas->fillCircle(cx, cy + 4, 7, color);
                canvas->fillCircle(cx, cy + 5, 3, BMO_COLOR_TONGUE);
            }
            else
            {
                // Frame 3: Wide smile line
                for (int t = 0; t <= 2; t++)
                {
                    canvas->drawArc(cx, cy - 4, 20, 20 - t, 30, 150, color);
                }
            }
            return;
        }

        if (state == APP_STATE_S2S_LISTENING)
        {
            // Attentive listening: small cute 'o' mouth
            canvas->fillCircle(cx, cy + 4, 5, color);
            canvas->fillCircle(cx, cy + 4, 2, BMO_COLOR_BG);
            return;
        }

        if (state == APP_STATE_S2S_CONNECTING || state == APP_STATE_CONNECTING_WIFI)
        {
            // Thinking: small straight/wavy line
            canvas->fillRect(cx - 10, cy + 3, 20, 3, color);
            return;
        }

        // Default / Idle: Classic BMO gentle curved smile
        // Arc from 30 deg to 150 deg downwards
        for (int t = 0; t <= 2; t++)
        {
            canvas->drawArc(cx, cy - 5, 18, 18 - t, 30, 150, color);
        }
    }

    void BMOFace::render(LGFX_Sprite* canvas, int appState, uint32_t now)
    {
        int w = canvas->width();
        int h = canvas->height();

        // 1. Fill authentic BMO Mint Screen background
        canvas->fillScreen(BMO_COLOR_BG);

        // 2. Handle Blink Timing (only in idle/listening states)
        if (appState != APP_STATE_S2S_ERROR && appState != APP_STATE_DISCONNECTED && appState != APP_STATE_S2S_SPEAKING)
        {
            if (!_is_blinking)
            {
                if (now - _last_blink_time > _next_blink_interval)
                {
                    _is_blinking = true;
                    _last_blink_time = now;
                }
            }
            else
            {
                if (now - _last_blink_time > _blink_duration)
                {
                    _is_blinking = false;
                    _last_blink_time = now;
                    // Random interval between 2.5s and 5.5s for natural look
                    _next_blink_interval = 2500 + (now % 3000);
                }
            }
        }
        else
        {
            _is_blinking = false;
        }

        // 3. Coordinate Layout for 240x135 Screen
        int centerX = w / 2;
        int eyeSpacing = 42; // Distance from center to each eye (total 84px between eyes)
        int eyeY = 52;
        int mouthY = 74;

        // 4. Draw Cheeks / Blushes
        drawBlushes(canvas, w, h);

        // 5. Draw Left and Right Eyes
        drawEyeLeft(canvas, centerX - eyeSpacing, eyeY, appState, _is_blinking, now);
        drawEyeRight(canvas, centerX + eyeSpacing, eyeY, appState, _is_blinking, now);

        // 6. Draw Mouth
        drawMouth(canvas, centerX, mouthY, appState, now);
    }
}
