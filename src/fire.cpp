#include "fire.h"

const String TAG = "fire";

FireScreensaver::FireScreensaver(OUT_DEVICECLASS *_out)
{
    out = _out;

    // fill palette
    uint32_t halflen = F_PALETTE_LEN >> 1;
    for (uint8_t i = 0; i < halflen; i++)
    {
        palette[i] = RGB(i << (8 - F_PALETTE_DIM + 1), 0, 0);
    }
    for (uint8_t i = halflen; i < F_PALETTE_LEN; i++)
    {
        palette[i] = RGB(255, 255 - ((i - halflen) << (8 - F_PALETTE_DIM + 1)), 0);
    }

    memset(frames, 0, sizeof(frames));
}

void FireScreensaver::loop(void)
{
    round++;

    // fill two extra rows with random colors
    for (uint16_t i = 0; i < MAX_X; i++)
    {
        frames[curFrame][MAX_Y + 0][i] = random(F_PALETTE_LEN);
        frames[curFrame][MAX_Y + 1][i] = random(F_PALETTE_LEN);
    }

    uint16_t c, v;

    // calculate full array
    for (uint16_t y = MAX_Y; y > 0; y--)
    {
        for (uint16_t x = 1; x < MAX_X - 1; x++)
        {

            // calculate color based on average of points around
            v = (frames[curFrame][y][x] + frames[curFrame][y][x - 1] + frames[curFrame][y][x + 1] + frames[curFrame][y + 1][x]) >> 2;
            // if (v != 0)
            //     Serial.printf("x = %d, y = %d, v = %d\n", x, y, v);

            if (v > 1)
                v -= 1;

            // store in the 'other' frame
            frames[1 - curFrame][y - 1][x] = v;
        }
    }

    // flip frame
    curFrame = 1 - curFrame;

    // draw claculated frame
    for (uint16_t y = 0; y < MAX_Y; y++)
    {
        for (uint16_t x = 0; x < MAX_X; x++)
        {
            v = frames[curFrame][y][x];
            c = palette[v];
            // if (v > 0)
            //     Serial.printf("x = %d, y = %d, v = %d, c = %d\n", x, y, v, c);

            RECT(x << 1, y << 1, 2, 2, c);
        }
    }

    delay(DELAY_TIME >> 3);
}