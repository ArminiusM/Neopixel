// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npFire.h"
//-------------------------------------------------------------------------------------
npFire::npFire(int Cooling, int Sparking, unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay)
{
  cooling = Cooling;
  sparking = Sparking;
  init();
}
//-------------------------------------------------------------------------------------
npFire::~npFire()
{
}
//-------------------------------------------------------------------------------------
void npFire::doInit()
{
  heat = new unsigned int [target->numPixels()];
  for (unsigned int i=0; i<target->numPixels(); i++) heat[i] = 0;
}
//-------------------------------------------------------------------------------------
bool npFire::doUpdate()
{
  bool rc = false;
  //  static int heat[neo->getSize()];
  unsigned int cooldown;
  // Step 1.  Cool down every cell a little
  for(unsigned int i = 0; i < target->numPixels(); i++) {
    cooldown = random(0, ((cooling * 10) / target->numPixels()) + 2);
    if(cooldown > heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= target->numPixels() - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if(random(0,255) < sparking ) {
    int y = random(0, 7);
//    heat[y] = heat[y] + random(160,255);
    heat[y] = random(160,255);
  }
  // Step 4.  Convert heat to LED colors
  for(unsigned int j = 0; j < target->numPixels(); j++) {
    setPixelHeatColor(j, heat[j]);
  }
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
void npFire::setPixelHeatColor (int Pixel, int temperature)
{
  // Scale 'heat' down from 0-255 to 0-191
  int t192 = round((temperature/255.0)*191);
  // calculate ramp up from
  int heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixelColor(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixelColor(Pixel, heatramp, 0, 0);
  }
}
//-------------------------------------------------------------------------------------
