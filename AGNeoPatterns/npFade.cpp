// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npFade.h"
//-------------------------------------------------------------------------------------
npFade::npFade(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay, red, green, blue)
{
  init();
}
//-------------------------------------------------------------------------------------
npFade::npFade(unsigned int SpeedDelay, npVirtualNeo bound) : npBase(bound, SpeedDelay)
{
  init();
}
//-------------------------------------------------------------------------------------
npFade::~npFade()
{
}
//-------------------------------------------------------------------------------------
void npFade::doInit()
{
  toggle = true;
  doDelay = true;
  density = 0;
}
//-------------------------------------------------------------------------------------
bool npFade::doUpdate()
{
  int rc = false;

  if (doRainbow) Wheel(((random(0, 256) * 256 / target->numPixels()) + random(0, 256)) & 255, &r, &g, &b);

  float rr, gg, bb;
  rr = (density/256.0) * r;
  gg = (density/256.0) * g;
  bb = (density/256.0) * b;
  setAll(rr, gg, bb);
  if (toggle) {
    density++;
    if (density >= 255) toggle = !toggle;
  }
  else {
    density--;
    if (density <= 0) {
      toggle = !toggle;
      done = true;
    }
  }
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
