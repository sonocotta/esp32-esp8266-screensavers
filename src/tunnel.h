#pragma once

#include <stdint.h>
#include "output.h"
#include "screensaver.h"
#include "circle.h"

#define CIRCLES_C 5
#define CIRCLES_COUNT (1 << CIRCLES_C)
#define CIRCLES_RADIUS_START 20
#define CIRCLES_RADIUS_STEP (3 * OUT_WIDTH >> (CIRCLES_C + 2))
#define CIRCLES_COLOR_START 64
#define CIRCLES_COLOR_STEP ((255 - CIRCLES_COLOR_START) >> CIRCLES_C)

// #define STARS_SPEED 1
// #define Z_MAX 256

struct Circle
{
    // absolute coordinates, doesn't change
    int16_t x; // [-X_MAX; X_MAX]
    int16_t y; // [-Y_MAX; Y_MAX]
    // radius
    int16_t r;
    uint8_t brightness;
};

class TunnelScreensaver : public Screensaver
{

public:
    TunnelScreensaver(OUT_DEVICECLASS *);
    void loop(void) override;

private:
    uint32_t round = 0;
    OUT_DEVICECLASS *out;
    Circle circles[CIRCLES_COUNT];

    void drawCircle(Circle, uint16_t);
    Circle newCircle();
};