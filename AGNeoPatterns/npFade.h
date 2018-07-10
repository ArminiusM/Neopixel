// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPFADE_H
#define NPFADE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npFade : public npBase {
public:
  npFade(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target);
  npFade(unsigned int SpeedDelay, npVirtualNeo Target);
  ~npFade();
private:
  void doInit();
  bool doUpdate();
  unsigned char oldr, oldg, oldb;
  bool toggle;
  uint32_t *oldPixels;
  int density;
};
//-------------------------------------------------------------------------------------

#endif // NPFADE_H
