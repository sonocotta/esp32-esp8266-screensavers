#include "tunnel.h"

const String TAG = "tunnel";

TunnelScreensaver::TunnelScreensaver(OUT_DEVICECLASS *_out)
{
    out = _out;
    for (uint8_t i = 0; i < CIRCLES_COUNT; i++)
    {
        circles[i] = newCircle();
    }
}

void TunnelScreensaver::drawCircle(Circle c, uint16_t color)
{
    for (uint8_t i = 0; i <= quartercircle_length; i += 8)
    {
        int32_t x = c.r * SIN(i) >> 10;
        int32_t y = c.r * COS(i) * OUT_HEIGHT / OUT_WIDTH >> 10;
        PIXEL(c.x + x, c.y + y, color);
        PIXEL(c.x - x, c.y + y, color);
        PIXEL(c.x - x, c.y - y, color);
        PIXEL(c.x + x, c.y - y, color);
    }
}

void TunnelScreensaver::loop(void)
{
    round++;

    for (int16_t i = CIRCLES_COUNT - 2; i >= 0; i--)
    {
        Circle c = circles[i];
        // remove prev trace
        drawCircle(circles[i + 1], RGB(0, 0, 0));

        c.r += CIRCLES_RADIUS_STEP;
        c.brightness += CIRCLES_COLOR_STEP;
        circles[i + 1] = c;

        drawCircle(c, RGB(c.brightness, c.brightness, c.brightness));
    }

    uint32_t r = round << 1;
    int32_t x0 = SIN(r);

    circles[0] = (Circle){
        X_MAX + ((x0 * CIRCLES_RADIUS_START * 2) >> 10),
        Y_MAX + ((x0 * CIRCLES_RADIUS_START * 2) >> 10),
        CIRCLES_RADIUS_START,
        CIRCLES_COLOR_START};

    delay(DELAY_TIME);
}

Circle TunnelScreensaver::newCircle()
{
    return (Circle){
        X_MAX,
        Y_MAX,
        CIRCLES_RADIUS_START,
        CIRCLES_COLOR_START};
}