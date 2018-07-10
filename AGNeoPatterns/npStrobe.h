// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPSTROBE_H
#define NPSTROBE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npStrobe : public npBase {
public:
  npStrobe(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  npStrobe(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  ~npStrobe();
private:
  void doInit();
  bool doUpdate();
  unsigned char oldr, oldg, oldb;
  bool toggle;
};
//-------------------------------------------------------------------------------------

#endif // NPSTROBE_H
