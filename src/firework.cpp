#include "firework.h"

const String TAG = "fire";

FireworkScreensaver::FireworkScreensaver(OUT_DEVICECLASS *_out)
{
    out = _out;

    // fill palette
    uint32_t halflen = FW_PALETTE_LEN >> 1;
    uint32_t quarterlen = FW_PALETTE_LEN >> 2;
    for (uint16_t i = 0; i < quarterlen; i++)
        palette[i] = RGB(i << 2, 0, 0);
    for (uint16_t i = quarterlen; i < halflen; i++)
        palette[i] = RGB(255, 255 - (i << 2), 0);
    for (uint16_t i = halflen; i < FW_PALETTE_LEN; i++)
        palette[i] = RGB(255, 255, ((i << 2) - 128) >> 2);

    // init particles
    memset(particles, 0, sizeof(particles));

    // init screen buffer
    memset(frame, 0, sizeof(frame));

    // init first firework in the center of the screen
    boom(random(MAX_X), random(MAX_Y));
}

void FireworkScreensaver::boom(int16_t x, int16_t y)
{
    for (uint16_t i = 0; i < FW_PARTICLES_COUNT; i++)
    {
        auto p = particles[i];
        p.x = x;
        p.y = y;
        uint8_t radius = random(FW_RADIUS_MAX);
        uint16_t direction = random(quartercircle_length << 2);
        p.dx = (radius * (SIN8(direction) >> 6));
        p.dy = (radius * (COS8(direction) >> 6));
        p.color = FW_PALETTE_LEN - 1;
        particles[i] = p;

        // Serial.printf("%d [%d] x=%d, y=%d, dx=%d, dy=%d\n", round, i, p.x, p.y, p.dx, p.dy, p.color);
    }
}

void FireworkScreensaver::loop(void)
{
    uint8_t color;

    if (++round % 32 == 0)
        boom(random(MAX_X), random(MAX_Y));

    for (uint16_t i = 0; i < FW_PARTICLES_COUNT; i++)
    {
        auto p = particles[i];
        // check if visible
        if ((p.x > 0) && (p.x < MAX_X - 1) && (p.y > 0) && (p.y < MAX_Y - 1))
            frame[p.x][p.y] = p.color;

        // increment coordinates
        p.x += p.dx;
        p.y += p.dy;

        // jump off the ground and gravity
        if (p.y > MAX_Y)
        {
            p.y = MAX_Y;
            p.dy = -p.dy >> 1;
        }
        else
        {
            p.dy += FW_G;
        }

        particles[i] = p;

        // Serial.printf("%d [%d] x=%d, y=%d, dx=%d, dy=%d, c=%d\n", round, i, p.x, p.y, p.dx, p.dy, p.color);
    }

    for (int16_t y = 1; y < MAX_Y - 1; y++)
    {
        for (int16_t x = 1; x < MAX_X - 1; x++)
        {
            color = ((frame[x + 1][y] + frame[x - 1][y] + frame[x][y + 1] + frame[x][y - 1]) >> 2);
            if (color <= 2)
                color = 0;
            else
                color -= 2;

            frame[x][y] = color;

            RECT(x << 1, y << 1, 2, 2, palette[color]);
        }
    }

    delay(DELAY_TIME >> 3);
}