// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npFuse.h"
//-------------------------------------------------------------------------------------
npFuse::npFuse(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, red, green, blue, KeepBackground)
{
  init();
}
//-------------------------------------------------------------------------------------
npFuse::npFuse(unsigned int SpeedDelay, npVirtualNeo bound, bool KeepBackground) : npBase(bound, SpeedDelay, KeepBackground)
{
  init();
}
//-------------------------------------------------------------------------------------
npFuse::~npFuse()
{
}
//-------------------------------------------------------------------------------------
void npFuse::doInit()
{
  doDelay = true;
}
//-------------------------------------------------------------------------------------
bool npFuse::doUpdate()
{
  int rc = false;
  if (doRainbow) {
    Wheel(((Position * 256 / target->numPixels()) + Position) & 255, &r, &g, &b);
  }
  allOff = true; // allOff indicates that the MeteorRain finished

//  if (keepBackground) {
//    setPixelColor(lastPosition, oldColor);
//    oldColor = getPixelColor(Position);
//  }
//  else setPixelColor(lastPosition, 0, 0, 0);
  for (int i=0; i<target->numPixels(); i++) {
    if(random(0, 10)>5) {
      if (fadeToBlack(i, 235, &allOff)) rc = true;
    }
    else {
      if(getPixelColor(i) != 0) allOff = false;
    }
  }
  //
  float zf = 1. - random(0,3)/10.;
  setPixelColor(Position, r * zf, g * zf, b * zf);
  int nsparcs = random(0, 1);
  for (int i=0; i<nsparcs; i++) {
    int dist = random(0, 8);
    zf = 1. - random(0,3)/10.;
    setPixelColor(Position + 5 - dist, r * zf, g * zf, b * zf);
    rc = true;
  }

  lastPosition = Position;
  if (random(0,10) > 3) Position++;
  if (Position > target->numPixels() && allOff) done = true;

  return rc;
}
//-------------------------------------------------------------------------------------
