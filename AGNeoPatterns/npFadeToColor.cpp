// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npFadeToColor.h"
//-------------------------------------------------------------------------------------
npFadeToColor::npFadeToColor(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, unsigned int FadeValue, npVirtualNeo Target) : npBase(Target, SpeedDelay, red, green, blue)
{
  fadeValue = FadeValue;
  colors = NULL;
  init();
}
//-------------------------------------------------------------------------------------
npFadeToColor::npFadeToColor(npNeoPixel *Strip, unsigned int SpeedDelay, unsigned int FadeValue, npVirtualNeo Target) : npBase(Target, SpeedDelay, 0, 0, 0)
{
  colors = new uint32_t[Target.numPixels()];
  for (unsigned int i=0; i<Target.numPixels(); i++) {
    if (i < Strip->numPixels()) colors[i] = Strip->getPixelColor(Target.getPosition(i));
    else colors[i] = 0;
  }
  fadeValue = FadeValue;
  init();
}
//-------------------------------------------------------------------------------------
npFadeToColor::npFadeToColor(unsigned int SpeedDelay, unsigned int FadeValue, npVirtualNeo Target) : npBase(Target, SpeedDelay, 0, 0, 0)
{
  fadeValue = FadeValue;
  colors = NULL;
  init();
}
//-------------------------------------------------------------------------------------
npFadeToColor::~npFadeToColor()
{
  delete [] colors;
}
//-------------------------------------------------------------------------------------
void npFadeToColor::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npFadeToColor::doUpdate()
{
  int rc = false;
  allOff = true; // allOff indicates that the MeteorRain finished
  for(unsigned int i=0; i<target->numPixels(); i++) {
    if (colors != NULL) fadeToColor(i, colors[i], fadeValue, &allOff);
    else fadeToColor(i, r, g, b, fadeValue, &allOff);
  }
  if (allOff) done = true;
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
