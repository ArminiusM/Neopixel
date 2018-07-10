// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPRUNNINGLIGHT_H
#define NPRUNNINGLIGHT_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npRunningLight : public npBase {
public:
  npRunningLight(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, int Size, npVirtualNeo Target);
  npRunningLight(unsigned int SpeedDelay, int Size, npVirtualNeo Target);
  ~npRunningLight();
private:
  void doInit();
  bool doUpdate();
  unsigned int loopCount;
  unsigned int size;
};
//-------------------------------------------------------------------------------------

#endif // NPRUNNINGLIGHT_H
