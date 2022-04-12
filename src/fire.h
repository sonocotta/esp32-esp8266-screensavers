#pragma once

#include <stdint.h>
#include "output.h"
#include "screensaver.h"

#define F_PALETTE_DIM 7 // translated to fire height in the end
#define F_PALETTE_LEN (1 << F_PALETTE_DIM)
#define MAX_X (OUT_WIDTH >> 1)
#define MAX_Y (OUT_HEIGHT >> 1)

class FireScreensaver : public Screensaver
{

public:
    FireScreensaver(OUT_DEVICECLASS *);
    void loop(void) override;

private:
    uint32_t round = 0;
    OUT_DEVICECLASS *out;
    uint8_t frames[2][MAX_Y + 2][MAX_X]; // two extra lines for purely random pixels
    uint16_t palette[F_PALETTE_LEN];
    uint8_t curFrame = 0;
};