// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPFADETOCOLOR_H
#define NPFADETOCOLOR_H

#include "npBase.h"
//-------------------------------------------------------------------------------------
class npFadeToColor : public npBase {
public:
  npFadeToColor(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, unsigned int FadeValue, npVirtualNeo Target);
  npFadeToColor(npNeoPixel *Strip, unsigned int SpeedDelay, unsigned int FadeValue, npVirtualNeo Target);
  npFadeToColor(unsigned int SpeedDelay, unsigned int FadeValue, npVirtualNeo Target);
  ~npFadeToColor();
private:
  void doInit();
  bool doUpdate();
  unsigned int fadeValue;
  bool allOff;
  npNeoPixel *Strip;
  uint32_t *colors;
};
//-------------------------------------------------------------------------------------

#endif // NPFADETOCOLOR_H
