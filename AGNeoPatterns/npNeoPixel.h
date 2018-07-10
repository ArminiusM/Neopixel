#ifndef NPNEOPIXEL_H
#define NPNEOPIXEL_H

#include "Adafruit_NeoPixel.h"
//-------------------------------------------------------------------------------------
class npNeoPixel : public Adafruit_NeoPixel {
public:
//  npNeoPixel(QWidget *parent, uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);
  npNeoPixel(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800, float maxAmps = 0.5);
  ~npNeoPixel();
  float npShow();
	// Attention: The npAmps() method is NOT absolutly safe and gives just 
	// a hint of the current needed for a specific pattern.
  float npAmps(void);
private:
  float maxCurrent;
};
//-------------------------------------------------------------------------------------

#endif // NPNEOPIXEL_H
