// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPSPARCLE_H
#define NPSPARCLE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npSparkle : public npBase {
public:
  npSparkle(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  npSparkle(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  ~npSparkle();
private:
  void doInit();
  bool doUpdate();
  unsigned char oldr, oldg, oldb;
  bool toggle;
  unsigned int pos;
};
//-------------------------------------------------------------------------------------

#endif // NCOLORWIPE_H
