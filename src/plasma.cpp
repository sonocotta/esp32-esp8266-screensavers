#include "plasma.h"

const String TAG = "fire";

PlasmaScreensaver::PlasmaScreensaver(OUT_DEVICECLASS *_out)
{
    out = _out;
}

void PlasmaScreensaver::loop(void)
{
    round++;
    uint8_t r, g, b;
    for (uint16_t y = 0; y < P_MAX_Y; y++)
    {
        for (uint16_t x = 0; x < P_MAX_X; x++)
        {
            r = 128 + (SIN8(P_A1_K * x + (round << 4)) >> 2) + (COS8(P_A1_K * y - (round << 4)) >> 2);
            g = 128 + (COS8(P_A2_K * x - (round << 4)) >> 2) + (SIN8(P_A2_K * y + (round << 4)) >> 2);
            b = 128 + (SIN8(P_A3_K * x + (round << 4)) >> 2) + (COS8(P_A3_K * y - (round << 4)) >> 2);
            PIXEL(x, y, RGB(r, g, b));
        }
    }

    delay(DELAY_TIME >> 3);
}