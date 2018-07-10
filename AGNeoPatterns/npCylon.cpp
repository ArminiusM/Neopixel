// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npCylon.h"
//-------------------------------------------------------------------------------------
npCylon::npCylon(unsigned char red, unsigned char green, unsigned char blue, unsigned int Size, unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay, red, green, blue)
{
  size = Size;
  init();
  lastPosition = 0;
  toggle = true;
}
//-------------------------------------------------------------------------------------
npCylon::npCylon(unsigned int Size, unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay)
{
  size = Size;
  init();
  lastPosition = 0;
  toggle = true;
}
//-------------------------------------------------------------------------------------
npCylon::~npCylon()
{
}
//-------------------------------------------------------------------------------------
void npCylon::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npCylon::doUpdate()
{
  int rc = false;
  if (doRainbow) {
    Wheel(((Position * 256 / target->numPixels()) + Position) & 255, &r, &g, &b);
  }

  setPixelColor(Position-1, 0, 0, 0);
  setPixelColor(Position, r/2, g/2, b/2);
  for(int j = 1; j <= size; j++) {
    setPixelColor(Position+j, r, g, b);
  }
  setPixelColor(Position+size+1, r/2, g/2, b/2);
  setPixelColor(Position+size+2, 0, 0, 0);

  if (toggle) {
    Position++;
    if (Position >= target->numPixels()-size-2) {
      toggle = !toggle;
    }
  }
  else {
    if (Position == 0) {
      toggle = !toggle;
      done = true;
    }
    Position--;
  }
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
