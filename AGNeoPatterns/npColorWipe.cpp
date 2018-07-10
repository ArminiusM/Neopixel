// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npColorWipe.h"
//-------------------------------------------------------------------------------------
npColorWipe::npColorWipe(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay, red, green, blue)
{
  init();
}
//-------------------------------------------------------------------------------------
npColorWipe::npColorWipe(unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay)
{
  init();
}
//-------------------------------------------------------------------------------------
npColorWipe::~npColorWipe()
{
}
//-------------------------------------------------------------------------------------
void npColorWipe::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npColorWipe::doUpdate()
{
  int rc = false;
  if (doRainbow) {
    Wheel(((Position * 256 / target->numPixels()) + Position) & 255, &r, &g, &b);
  }
  setPixelColor(Position,r, g, b);
  rc = true;
  Position++;
  if (Position >= target->numPixels()) {
    done = true;
    Position = 0;
  }
  return rc;
}
//-------------------------------------------------------------------------------------
