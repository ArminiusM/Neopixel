// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npTheaterChase.h"
//-------------------------------------------------------------------------------------
npTheaterChase::npTheaterChase(unsigned char red, unsigned char green, unsigned char blue, unsigned int Distance, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, red, green, blue, KeepBackground)
{
  distance = Distance;
  init();
  localPosition = 0;
  q = 0;
  toggle = true;
}
//-------------------------------------------------------------------------------------
npTheaterChase::npTheaterChase(unsigned int Distance, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, KeepBackground)
{
  distance = Distance;
  init();
  localPosition = 0;
  q = 0;
  toggle = true;
}
//-------------------------------------------------------------------------------------
npTheaterChase::~npTheaterChase()
{
}
//-------------------------------------------------------------------------------------
void npTheaterChase::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npTheaterChase::doUpdate()
{
  bool rc = false;

  if (toggle) {
    if (keepBackground) savePixels();
    for (unsigned int i=0; i < target->numPixels(); i=i+distance) {
      if (doRainbow) Wheel((i + localPosition) % 255, &r, &g, &b);
      setPixelColor(i+q, r, g, b);    //turn every third pixel on
    }
    doDelay = true;
  }
  else {
    if (keepBackground) restorePixels();
    else {
      for (unsigned int i=0; i < target->numPixels(); i=i+distance) {
        setPixelColor(i+q, 0, 0, 0);    //turn every third pixel off
      }
    }
    doDelay = false;
    q++;
    if (q >= distance) q = 0;
  }
  toggle = !toggle;
  // localPosition is kept for the lifetime of the instance to avoid jumps in rainbow colors
  localPosition++;
  if (localPosition > 4000000000) localPosition = localPosition % q;
  // Position ist needed just for determining the end of the effect
  Position++;
  if (Position > target->numPixels()) done = true;
  rc = true;

  return rc;
}
//-------------------------------------------------------------------------------------
