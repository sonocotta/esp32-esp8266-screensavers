#pragma once

#include <stdint.h>
#include "output.h"
#include "screensaver.h"
#include "circle.h"

#define S_RAINBOW_PALETTE
// #define S_FIRE_PALETTE

#define S_PALETTE_LEN 256
#define S_MAX_X OUT_WIDTH
#define S_MAX_Y OUT_HEIGHT
#define S_BOX_START_SPEED 3
#define S_BOX_DIM_X 32
#define S_BOX_DIM_Y 32

struct Box {
    // coordinates
    int16_t x;
    int16_t y;
    // speed
    int8_t sx;
    int8_t sy;
    // dimension
    uint8_t dx;
    uint8_t dy;
};

class ShadebobsScreensaver : public Screensaver
{

public:
    ShadebobsScreensaver(OUT_DEVICECLASS *);
    void loop(void) override;

private:
    uint32_t round = 0;
    OUT_DEVICECLASS *out;
    Box box = (Box) {
        S_MAX_X,
        S_MAX_Y,
        S_BOX_START_SPEED,
        S_BOX_START_SPEED,
        S_BOX_DIM_X,
        S_BOX_DIM_Y
    };
    uint16_t palette[S_PALETTE_LEN];
    uint8_t frame[S_MAX_X][S_MAX_Y];
};