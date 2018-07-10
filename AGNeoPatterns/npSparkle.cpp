// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npSparkle.h"
//-------------------------------------------------------------------------------------
npSparkle::npSparkle(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, red, green, blue, KeepBackground)
{
  init();
}
//-------------------------------------------------------------------------------------
npSparkle::npSparkle(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, KeepBackground)
{
  init();
}
//-------------------------------------------------------------------------------------
npSparkle::~npSparkle()
{
}
//-------------------------------------------------------------------------------------
void npSparkle::doInit()
{
  toggle = true;
  doDelay = true;
}
//-------------------------------------------------------------------------------------
bool npSparkle::doUpdate()
{
  int rc = false;
  if (toggle) {
    pos = random(0, target->numPixels()-1);
    if (doRainbow) Wheel(((pos * 256 / target->numPixels()) + pos) & 255, &r, &g, &b);
    if (keepBackground) getColor(pos, &oldr, &oldg, &oldb);
    setPixelColor(pos, r, g, b);
    toggle = !toggle;
    doDelay = true;
  }
  else {
    if (keepBackground) setPixelColor(pos, oldr, oldg, oldb);
    else setPixelColor(pos, 0, 0, 0);
    toggle = !toggle;
    doDelay = false;
    done = true;
  }
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
