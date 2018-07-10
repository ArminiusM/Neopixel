// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPFIRE_H
#define NPFIRE_H

//#include <math.h>
#include "npBase.h"
//-------------------------------------------------------------------------------------
class npFire : public npBase {
public:
  npFire(int Cooling, int Sparking, unsigned int SpeedDelay, npVirtualNeo Target);
  ~npFire();
protected:
  void doInit();
  bool doUpdate();
  void setPixelHeatColor (int Pixel, int temperature);
  unsigned int *heat;
  unsigned int cooling;
  unsigned int sparking;
};
//-------------------------------------------------------------------------------------

#endif // NPFIRE_H
