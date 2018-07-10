// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPMETEOR_H
#define NPMETEOR_H

#include <math.h>
#include "npBase.h"
//-------------------------------------------------------------------------------------
class npMeteor : public npBase {
public:
  npMeteor(unsigned char red, unsigned char green, unsigned char blue, int meteorSize, int meteorTrailDecay, bool meteorRandomDecay, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground);
  npMeteor(int meteorSize, int meteorTrailDecay, bool meteorRandomDecay, unsigned int SpeedDelay, npVirtualNeo Target, bool KeepBackground);
  ~npMeteor();
private:
  void doInit();
  bool doUpdate();
  unsigned int size;
  unsigned int trailDecay;
  bool randomDecay;
  bool allOff;
};
//-------------------------------------------------------------------------------------

#endif // NPMETEOR_H
