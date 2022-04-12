#ifndef OUTPUT_H
#define OUTPUT_H

#ifdef VGA_ENABLE
#include <VGA/VGA6Bit.h>
#define OUT_DEVICECLASS VGA6Bit
#define OUT_WIDTH VGA_WIDTH
#define OUT_HEIGHT VGA_HEIGHT
const int VGA_RED_PINS[] = {VGA_RED_1, VGA_RED_2};
const int VGA_GREEN_PINS[] = {VGA_GREEN_1, VGA_GREEN_2};
const int VGA_BLUE_PINS[] = {VGA_BLUE_1, VGA_BLUE_2};
#define RGB(r, g, b) out->RGB(r, g, b)
#define PIXEL(x, y, c) out->dot(x, y, c);
#define RECT(x, y, w, h, c) out->fillRect(x, y, w, h, c);
#define DELAY_TIME 25
#endif
#ifdef TFT_ENABLE
#include "TFT_eSPI.h"
#define OUT_DEVICECLASS TFT_eSPI
#define OUT_WIDTH TFT_HEIGHT
#define OUT_HEIGHT TFT_WIDTH
#define RGB(r, g, b) out->color565(r, g, b)
#define PIXEL(x, y, c) out->drawPixel(x, y, c);
#define RECT(x, y, w, h, c) out->drawRect(x, y, w, h, c);
#define DELAY_TIME 10
#endif

#endif