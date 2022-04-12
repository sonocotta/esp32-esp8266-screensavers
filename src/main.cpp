#include "SPI.h"
#include "output.h"
#include "screensaver.h"
#include "starfield.h"
#include "tunnel.h"
#include "fire.h"
#include "firework.h"
#include "shadebobs.h"
#include "plasma.h"

#ifndef SERIAL_BAUD
#define SERIAL_BAUD 115200
#endif

const String TAG = "main";

OUT_DEVICECLASS *out = new OUT_DEVICECLASS();

#ifdef ESP8266 
#define ANIMATION_COUNT 4 // unable to solve out of memory issues for now
#else
#define ANIMATION_COUNT 6
#endif

uint8_t animationIndex = 0;
Screensaver *animation; 

uint8_t frameCount = 0;
uint32_t frameCounterStart = 0;

void setup()
{
  Serial.begin(SERIAL_BAUD);
  while (!Serial)
    ;

  delay(1000);
  Serial.println("starting");

#ifdef PIN_SWITCH
  pinMode(PIN_SWITCH, INPUT);
#endif

  #ifdef TFT_ENABLE
  out->init();
  out->setRotation(TFT_ROTATION);
  out->setSwapBytes(false);
  out->fillScreen(TFT_BLACK);
  #endif

  #ifdef VGA_ENABLE
  out->init(out->MODE320x240, VGA_RED_PINS, VGA_GREEN_PINS, VGA_BLUE_PINS, VGA_HSYNC, VGA_VSYNC);
  #endif

  frameCounterStart = millis();

  animation = new StarFieldScreensaver(out);
  // animation = new TunnelScreensaver(out);
  // animation = new FireScreensaver(out);
  // animation = new FireworkScreensaver(out);
  // animation = new ShadebobsScreensaver(out);
  // animation = new PlasmaScreensaver(out);
}

bool btn_is_down = false;

void switchScreensaver(void)
{
  if (animation != NULL)
    delete animation;

  switch (animationIndex)
  {
  case 0:
    animation = new StarFieldScreensaver(out);
    break;

  case 1:
    animation = new TunnelScreensaver(out);
    break;

  case 2:
    animation = new FireScreensaver(out);
    break;

  case 3:
    animation = new FireworkScreensaver(out);
    break;

  case 4:
    animation = new ShadebobsScreensaver(out);
    break;

  case 5:
    animation = new PlasmaScreensaver(out);
    break;
  }
}

void loop(void)
{
#ifdef PIN_SWITCH
  if (digitalRead(PIN_SWITCH) == LOW)
    // key down
    btn_is_down = true;
  else if (btn_is_down)
  {
    // key up
    #ifdef TFT_ENABLE
    out->fillScreen(TFT_BLACK);
    #endif
    #ifdef VGA_ENABLE
    out->clear();
    #endif
    animationIndex = (animationIndex + 1) % ANIMATION_COUNT;
    switchScreensaver();
    btn_is_down = false;
  }
#endif

#ifdef SWITCH_AUTO
  uint32_t period = ((millis() >> 10) / SWITCH_AUTO) % ANIMATION_COUNT;
  if (period != animationIndex)
  {
    out->fillScreen(TFT_BLACK);
    animationIndex = (animationIndex + 1) % ANIMATION_COUNT;
    switchScreensaver();
  }
#endif

  animation->loop(); // 1 frame

  if (++frameCount == 0)
  {
    uint32_t timespent = millis() - frameCounterStart;
    Serial.printf("fps = %d\n", (256 << 10) / timespent);
    ;

    frameCounterStart = millis();
  }

  yield();
}