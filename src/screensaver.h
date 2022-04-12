#pragma once

#define X_TOT OUT_WIDTH
#define X_MAX (OUT_WIDTH >> 1)
#define Y_TOT OUT_HEIGHT
#define Y_MAX (OUT_HEIGHT >> 1)

class Screensaver
{
public:
   virtual ~Screensaver() {};
   virtual void loop(void) = 0;
};