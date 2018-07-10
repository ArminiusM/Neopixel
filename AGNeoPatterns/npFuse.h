// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPFUSE_H
#define NPFUSE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npFuse : public npBase {
public:
  npFuse(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  npFuse(unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  ~npFuse();
private:
  void doInit();
  bool doUpdate();
  unsigned int lastPosition;
  uint32_t oldColor;
  bool allOff;
};
//-------------------------------------------------------------------------------------

#endif // NPFUSE_H
