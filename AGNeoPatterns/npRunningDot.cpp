// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npRunningDot.h"
//-------------------------------------------------------------------------------------
npRunningDot::npRunningDot(unsigned char red, unsigned char green, unsigned char blue,
                           unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground, bool AutoUpdate) :
                           npBase(Target, SpeedDelay, red, green, blue, KeepBackground, AutoUpdate)
{
  init();
  lastPosition = 0;
  oldColor = 0;
}
//-------------------------------------------------------------------------------------
npRunningDot::npRunningDot(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground, bool AutoUpdate) :
                           npBase(Target, SpeedDelay, KeepBackground, AutoUpdate)
{
  init();
  lastPosition = 0;
  oldColor = 0;
}
//-------------------------------------------------------------------------------------
npRunningDot::~npRunningDot()
{
}
//-------------------------------------------------------------------------------------
void npRunningDot::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npRunningDot::doUpdate()
{
  int rc = false;
  if (doRainbow) {
    Wheel(((Position * 256 / target->numPixels()) + Position) & 255, &r, &g, &b);
  }
  if (keepBackground) {
    setPixelColor(lastPosition, oldColor);
    oldColor = getPixelColor(Position);
  }
  else setPixelColor(lastPosition, 0, 0, 0);
  rc = setPixelColor(Position, r, g, b);
  lastPosition = Position;
  Position++;
  if (Position >= target->numPixels()) {
    done = true;
    Position = 0;
  }
  return rc;
}
//-------------------------------------------------------------------------------------
