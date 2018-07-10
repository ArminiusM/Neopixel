#define NeoPin     13 // NeoPixel Pin
#define MAXPIXELS 300 // Number of Pixels
//-------------------------------------------------------------------------------------
#include <npMeteor.h>
npNeoPixel pixels = npNeoPixel(MAXPIXELS, NeoPin, NEO_GRB + NEO_KHZ800);
//-------------------------------------------------------------------------------------
unsigned int Delay = 2;
npMeteor Meteor1(0x20, 0x3A, 0x05, 10, 64, true, Delay, npVirtualNeo(&pixels, pixels.numPixels()/2-1, 0), false);
npMeteor Meteor2(0x40, 0x1A, 0x20, 10, 64, true, Delay, npVirtualNeo(&pixels, pixels.numPixels()/2, pixels.numPixels()-1), false);
//-------------------------------------------------------------------------------------
void setup ()
{
  Serial.begin (115200); // Serial output with 115200 bps
  pixels.begin();
  pixels.clear();
  pixels.npShow();
}
//-------------------------------------------------------------------------------------
void loop ()
{
  Meteor1.update();
  Meteor2.update();
  delay (1);
}
