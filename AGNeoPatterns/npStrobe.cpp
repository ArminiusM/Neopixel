// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npStrobe.h"
//-------------------------------------------------------------------------------------
npStrobe::npStrobe(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, red, green, blue, KeepBackground)
{
  init();
}
//-------------------------------------------------------------------------------------
npStrobe::npStrobe(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, KeepBackground)
{
  init();
}
//-------------------------------------------------------------------------------------
npStrobe::~npStrobe()
{
}
//-------------------------------------------------------------------------------------
void npStrobe::doInit()
{
  toggle = true;
  doDelay = true;
}
//-------------------------------------------------------------------------------------
bool npStrobe::doUpdate()
{
  int rc = false;

  if (doRainbow) Wheel(((random(0, 256) * 256 / target->numPixels()) + random(0, 256)) & 255, &r, &g, &b);

  if (toggle) {
    if (keepBackground) savePixels();
    for (unsigned int i=0; i<target->numPixels(); i++) {
      setPixelColor(i, r, g, b);
    }
    toggle = !toggle;
//    doDelay = true;
  }
  else {
    if (keepBackground) restorePixels();
    else allOff();
    toggle = !toggle;
    //doDelay = false;
    done = true;
  }
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
