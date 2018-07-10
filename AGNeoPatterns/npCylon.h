// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPCYLONBOUNCE_H
#define NPCYLONBOUNCE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npCylon : public npBase {
public:
  npCylon(unsigned char red, unsigned char green, unsigned char blue, unsigned int Size, unsigned int SpeedDelay, npVirtualNeo Target);
  npCylon(unsigned int Size, unsigned int SpeedDelay, npVirtualNeo Target);
  ~npCylon();
private:
  void doInit();
  bool doUpdate();
  unsigned int size;
  unsigned int lastPosition;
  bool toggle;
};
//-------------------------------------------------------------------------------------

#endif // NPCYLONBOUNCE_H
