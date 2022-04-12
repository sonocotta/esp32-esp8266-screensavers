#include "shadebobs.h"

const String TAG = "fire";

ShadebobsScreensaver::ShadebobsScreensaver(OUT_DEVICECLASS *_out)
{
    out = _out;

#ifdef S_RAINBOW_PALETTE
    uint8_t seglen = S_PALETTE_LEN >> 3;
    uint16_t i = 0;
    for (uint8_t j = 0; i < seglen * 1; i++, j += (1 << 3))
        palette[i] = palette[S_PALETTE_LEN - i] = RGB(0, 0, j);
    for (uint8_t j = 0; i < seglen * 2; i++, j += (1 << 3))
        palette[i] = palette[S_PALETTE_LEN - i] = RGB(j, 0, 255 - j);
    for (uint8_t j = palette[S_PALETTE_LEN - i] = 0; i < seglen * 3; i++, j += (1 << 3))
        palette[i] = palette[S_PALETTE_LEN - i] = RGB(255, j, 0);
    for (uint8_t j = 0; i < seglen * 4; i++, j += (1 << 3))
        palette[i] = palette[S_PALETTE_LEN - i] = RGB(255, 255, j);
#endif

#ifdef S_FIRE_PALETTE
    // fill palette with black-yellow-red
    uint32_t halflen = S_PALETTE_LEN >> 1;
    uint32_t quarterlen = S_PALETTE_LEN >> 2;
    for (uint16_t i = 0; i < quarterlen; i++)
        palette[i] = RGB(i << 2, 0, 0);
    for (uint16_t i = quarterlen; i < halflen; i++)
        palette[i] = RGB(255, 255 - (i << 2), 0);
    for (uint16_t i = halflen; i < S_PALETTE_LEN; i++)
        palette[i] = RGB(255, 255, ((i << 2) - 128) >> 2);
#endif

    // for (uint16_t i = 0; i < S_PALETTE_LEN; i++)
    //     Serial.printf("%d ", palette[i]);
    // Serial.println();

    // init screen buffer
    memset(frame, 0, sizeof(frame));
}

void ShadebobsScreensaver::loop(void)
{
    round++;

    for (uint16_t y = box.y; y < box.y + box.dy; y++)
    {
        for (uint16_t x = box.x; x < box.x + box.dx; x++)
        {
            if ((x > 0) && (x < S_MAX_X) && (y > 0) && (y < S_MAX_Y))
            {
                frame[x][y] += 1;

                // out->drawRect(x << 1, y << 1, 2, 2, palette[frame[x][y]]);
                PIXEL(x, y, palette[frame[x][y]]);
            }
        }
    }

    if ((box.x <= 0) || (box.x >= S_MAX_X - 1) || random(7) == 4)
        box.sx *= -1;

    if ((box.y <= 0) || (box.y >= S_MAX_Y - 1) || random(11) == 7)
        box.sy *= -1;

    box.x += box.sx;
    box.y += box.sy;

    // Serial.printf("x=%d y=%d sx=%d sy=%d\n", box.x, box.y, box.sx, box.sy);

    delay(DELAY_TIME >> 3);
}