// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPCOLORWIPE_H
#define NPCOLORWIPE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npColorWipe : public npBase {
public:
  npColorWipe(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target);
  npColorWipe(unsigned int SpeedDelay, npVirtualNeo Target);
  ~npColorWipe();
private:
  void doInit();
  bool doUpdate();
};
//-------------------------------------------------------------------------------------

#endif // NPCOLORWIPE_H
