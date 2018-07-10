// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npRunningLight.h"
//-------------------------------------------------------------------------------------
npRunningLight::npRunningLight(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, int Size, npVirtualNeo Target) : npBase(Target, SpeedDelay, red, green, blue)
{
  size = Size;
  if (size < 1) size = 1;
  init();
  loopCount = 0;
}
//-------------------------------------------------------------------------------------
npRunningLight::npRunningLight(unsigned int SpeedDelay, int Size, npVirtualNeo Target) : npBase(Target, SpeedDelay)
{
  size = Size;
  if (size < 1) size = 1;
  init();
  loopCount = 0;
}
//-------------------------------------------------------------------------------------
npRunningLight::~npRunningLight()
{
}
//-------------------------------------------------------------------------------------
void npRunningLight::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npRunningLight::doUpdate()
{
  bool rc = false;
  for(unsigned int i=0; i<target->numPixels(); i++) {
    if (doRainbow) {
      Wheel(((i * 256 / target->numPixels()) + loopCount) & 255, &r, &g, &b);

    }
    setPixelColor(i, ((sin((i+loopCount)/2.) * 127 + 128)/255) * r,
                     ((sin((i+loopCount)/2.) * 127 + 128)/255) * g,
                     ((sin((i+loopCount)/2.) * 127 + 128)/255) * b);
    rc = true;
  }
  loopCount++;
  if (loopCount >= (int)target->numPixels()) {
    done = true;
    if (loopCount > 2000000000) loopCount = 0;
  }
  return rc;
}
//-------------------------------------------------------------------------------------
