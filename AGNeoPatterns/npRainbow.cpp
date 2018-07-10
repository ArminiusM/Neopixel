// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npRainbow.h"
//-------------------------------------------------------------------------------------
npRainbow::npRainbow(unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay)
{
  init();
  loopCount = 0;
}
//-------------------------------------------------------------------------------------
npRainbow::~npRainbow()
{
}
//-------------------------------------------------------------------------------------
void npRainbow::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npRainbow::doUpdate()
{
  bool rc = false;
//  TimeSinceLastUpdate =  millis() - ClockTimeSinceLastUpdate;
//  if (TimeSinceLastUpdate > speedDelay) {
    for(unsigned int i=0; i< target->numPixels(); i++) {
      Wheel(((i * 256 / target->numPixels()) + loopCount) & 255, &r, &g, &b);
      setPixelColor(i, r, g, b);
    }
    rc = true;
    done = true;
    loopCount++;
    if (loopCount > 2000000000) loopCount = 0;
//  }
  return rc;
}
//-------------------------------------------------------------------------------------
