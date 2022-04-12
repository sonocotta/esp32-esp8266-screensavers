#pragma once

#include <stdint.h>

#include "screensaver.h"
#include "output.h"
#include "circle.h"

#define P_MAX_X OUT_WIDTH
#define P_MAX_Y OUT_HEIGHT
// grid size for each color
#define P_A1_K 2
#define P_A2_K 3
#define P_A3_K 5

class PlasmaScreensaver : public Screensaver
{

public:
    PlasmaScreensaver(OUT_DEVICECLASS *);
    void loop(void) override;

private:
    uint32_t round = 0;
    OUT_DEVICECLASS *out;
};