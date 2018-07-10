#include "npNeoPixel.h"

//-------------------------------------------------------------------------------------
//npNeoPixel::npNeoPixel(QWidget *parent, uint16_t n, uint8_t p, neoPixelType t) : Adafruit_NeoPixel(parent, n, p, t)
npNeoPixel::npNeoPixel(uint16_t n, uint8_t p, neoPixelType t, float maxAmps) : Adafruit_NeoPixel(n, p, t)
{
  maxCurrent = maxAmps;
}
//-------------------------------------------------------------------------------------
npNeoPixel::~npNeoPixel()
{
}
//-------------------------------------------------------------------------------------
float npNeoPixel::npShow(void)
{
  float mA = 0;
  if(!pixels) return mA;
  mA = npAmps();
  if (mA > maxCurrent) {
		printf("%6.3fA > %6.3fA", mA, maxCurrent);
	  float factor = maxCurrent / mA;
		for (int i=0; i<numLEDs; i++) {
			unsigned int lColor = getPixelColor(i);
			int whi = (float)(lColor >> 24) * factor;
			int red = (float)((lColor >> 16) & 0xFF) * factor;
			int gre = (float)((lColor >>  8) & 0xFF) * factor;
			int blu = (float)(lColor & 0xFF) * factor;
			setPixelColor(i, red, gre, blu, whi);
		}
		mA = npAmps();
		printf(" reduced to %6.3fA\n", mA);
  }
  show();
  return mA;
}
//-------------------------------------------------------------------------------------
// Attention: The npAmps() method is NOT absolutly safe and gives just 
// a hint of the current needed for a specific pattern.
//
float npNeoPixel::npAmps(void)
{
  float mA = 0.0;
  if(!pixels) return mA;
  for (int i=0; i<numLEDs; i++) {
    unsigned int lColor = getPixelColor(i);
    int whi =  lColor >> 24;
    int red = (lColor >> 16) & 0xFF;
    int gre = (lColor >>  8) & 0xFF;
    int blu = lColor & 0xFF;
    mA += (float)whi / 256. * 0.02;
    mA += (float)red / 256. * 0.02;
    mA += (float)gre / 256. * 0.02;
    mA += (float)blu / 256. * 0.02;
  }
  return mA;
}
