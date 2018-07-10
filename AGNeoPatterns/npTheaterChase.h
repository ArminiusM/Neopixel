// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPTHEATERCHASE_H
#define NPTHEATERCHASE_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npTheaterChase : public npBase {
public:
  npTheaterChase(unsigned char red, unsigned char green, unsigned char blue, unsigned int Distance, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground = false);
  npTheaterChase(unsigned int Distance, unsigned int SpeedDelay, npVirtualNeo bound, bool KeepBackground = false);
  ~npTheaterChase();
private:
  void doInit();
  bool doUpdate();
  unsigned int distance;
  unsigned int localPosition;
  unsigned int q;
  bool toggle;
  uint32_t savedPixel;
};
//-------------------------------------------------------------------------------------

#endif // NPTHEATERCHASE_H
