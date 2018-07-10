// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npMeteor.h"
//-------------------------------------------------------------------------------------
npMeteor::npMeteor(unsigned char red, unsigned char green, unsigned char blue, int meteorSize, int meteorTrailDecay, bool meteorRandomDecay, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, red, green, blue, KeepBackground)
{
  size = meteorSize;
  trailDecay = meteorTrailDecay;
  randomDecay = meteorRandomDecay;
  init();
}
//-------------------------------------------------------------------------------------
npMeteor::npMeteor(int meteorSize, int meteorTrailDecay, bool meteorRandomDecay, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, KeepBackground)
{
  size = meteorSize;
  trailDecay = meteorTrailDecay;
  randomDecay = meteorRandomDecay;
  init();
}
//-------------------------------------------------------------------------------------
npMeteor::~npMeteor()
{
}
//-------------------------------------------------------------------------------------
void npMeteor::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npMeteor::doUpdate()
{
  bool rc = false;

  if (doRainbow) {
    Wheel(((Position * 256 / target->numPixels()) + Position) & 255, &r, &g, &b);
  }
  // fade brightness all LEDs one step
  allOff = true; // allOff indicates that the MeteorRain finished
  for(unsigned int i=0; i<target->numPixels(); i++) {
    if( (!randomDecay) || (random(0, 10)>5) ) {
      if (fadeToBlack(i, trailDecay, &allOff)) rc = true;
    }
    else {
      if(getPixelColor(i) != 0) allOff = false;
    }
  }
  // draw meteor
  for(int i = 0; i < size; i++) {
    int sPosition = Position - i;
    setPixelColor(sPosition, r, g, b);
    rc = true;
  }
  Position++;
  if (Position > target->numPixels() && allOff) done = true;

  return rc;
}
//-------------------------------------------------------------------------------------
