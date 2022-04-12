#pragma once

#include <stdint.h>
#include "output.h"
#include "screensaver.h"
#include "circle.h"

#define FW_PALETTE_LEN 256
#define MAX_X (OUT_WIDTH >> 1)
#define MAX_Y (OUT_HEIGHT >> 1)
#define FW_PARTICLES_COUNT 256
#define FW_RADIUS_MAX 5
#define FW_G 1

struct Particle
{
    // position
    int16_t x;
    int16_t y;
    // direction
    int16_t dx;
    int16_t dy;
    // color index in palette
    uint8_t color;
};

class FireworkScreensaver : public Screensaver
{

public:
    FireworkScreensaver(OUT_DEVICECLASS *);
    void loop(void) override;

private:
    uint32_t round = 0;
    OUT_DEVICECLASS *out;
    Particle particles[FW_PARTICLES_COUNT];
    uint16_t palette[FW_PALETTE_LEN];
    uint8_t frame[MAX_X][MAX_Y];

    void boom(int16_t, int16_t);
};