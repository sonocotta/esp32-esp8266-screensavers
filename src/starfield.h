#pragma once

#include <stdint.h>
#include "output.h"
#include "screensaver.h"

#define STARS_COUNT 128
#define STARS_SPEED 1

#define Z_MAX 256

struct Star
{
    // absolute coordinates, doesn't change
    int16_t x; // [-X_MAX; X_MAX]
    int16_t y; // [-Y_MAX; Y_MAX]
    // screen coordinates, updated every step
    int16_t sx; // [-X_MAX; X_MAX]
    int16_t sy; // [-Y_MAX; Y_MAX]
    // depth from the screen
    int16_t z; // [0; Z_MAX]

    uint8_t brightness;
};

class StarFieldScreensaver : public Screensaver
{

public:
    StarFieldScreensaver(OUT_DEVICECLASS *);
    void loop(void) override;

private:
    uint32_t round = 0;
    OUT_DEVICECLASS *out;
    Star stars[STARS_COUNT];

    Star newStar();
};