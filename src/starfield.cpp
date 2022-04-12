#include "starfield.h"

const String TAG = "starfield";

StarFieldScreensaver::StarFieldScreensaver(OUT_DEVICECLASS *_out)
{
    out = _out;
    for (uint8_t i = 0; i < STARS_COUNT; i++)
    {
        stars[i] = newStar();
        // Serial.printf("%d %d %d\n", i, stars[i].x, stars[i].y);
    }
}

void StarFieldScreensaver::loop(void)
{
    // Serial.printf("frame %d\n", round);
    round++;

    // out->fillScreen(TFT_BLACK); // to slow, blinking is clearly visible

    for (uint8_t i = 0; i < STARS_COUNT; i++)
    {
        Star s = stars[i];

        // remove prev trace
        PIXEL(s.sx + X_MAX, s.sy + Y_MAX, RGB(0, 0, 0));
        // with dynamic star size
        // out->fillCircle(s.sx + X_MAX, s.sy + Y_MAX, ((256 - s.z) >> 7), TFT_BLACK);

        // move the star
        s.z -= STARS_SPEED;

        // star outside screen
        if ((s.z <= 0) || (s.sx < -X_MAX) || (s.sx >= X_MAX) || (s.sy <= -Y_MAX) || (s.sy >= Y_MAX))
            s = newStar();

        s.sx = (int16_t)(s.x * Z_MAX / s.z);
        s.sy = (int16_t)(s.y * Z_MAX / s.z);

        if (s.brightness < 255)
            s.brightness += 1;

        stars[i] = s;

        PIXEL(s.sx + X_MAX, s.sy + Y_MAX, RGB(s.brightness, s.brightness, s.brightness));
        // with dynamic star size
        // out->fillCircle(s.sx + X_MAX, s.sy + Y_MAX, ((256 - s.z) >> 7) ,RGB(s.brightness, s.brightness, s.brightness));
    }

    delay(DELAY_TIME);
}

Star StarFieldScreensaver::newStar()
{
    return (Star){
        random(X_TOT) - X_MAX,
        random(Y_TOT) - Y_MAX,
        0,
        0,
        Z_MAX,
        64};
}