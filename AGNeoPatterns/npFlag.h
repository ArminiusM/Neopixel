// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPFLAG_H
#define NPFLAG_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npFlag : public npBase {
public:
  npFlag(unsigned char red1, unsigned char green1, unsigned char blue1,
         unsigned char red2, unsigned char green2, unsigned char blue2,
         unsigned char red3, unsigned char green3, unsigned char blue3,
         unsigned int SpeedDelay, unsigned int Size, npVirtualNeo Target, bool KeepBackground = false);
  ~npFlag();
private:
  void doInit();
  bool doUpdate();
  int size;
  uint32_t colors[3];
  uint32_t *oldColor;
};
//-------------------------------------------------------------------------------------

#endif // NPFLAG_H
