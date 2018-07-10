// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPRUNNINGDOT_H
#define NPRUNNINGDOT_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npRunningDot : public npBase {
public:
  npRunningDot(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false, bool AutoUpdate = true);
  npRunningDot(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false, bool AutoUpdate = true);
  ~npRunningDot();
private:
  void doInit();
  bool doUpdate();
  unsigned int lastPosition;
  uint32_t oldColor;
};
//-------------------------------------------------------------------------------------

#endif // NPRUNNINGDOT_H
