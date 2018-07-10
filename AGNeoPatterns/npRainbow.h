// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPRAINBOW_H
#define NPRAINBOW_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npRainbow : public npBase {
public:
  npRainbow(unsigned int SpeedDelay, npVirtualNeo Target);
  ~npRainbow();
private:
  void doInit();
  bool doUpdate();
  unsigned int loopCount;
};
//-------------------------------------------------------------------------------------

#endif // NPRAINBOW_H
