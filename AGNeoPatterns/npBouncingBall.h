// Neopixel effect using npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPBOUNCINGBALLS_H
#define NPBOUNCINGBALLS_H

#include <math.h>
#include "npBase.h"
//-------------------------------------------------------------------------------------
class npBouncingBall : public npBase {
public:
  npBouncingBall(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target);
  npBouncingBall(unsigned int SpeedDelay, npVirtualNeo Target);
  ~npBouncingBall();
private:
  void doInit();
  bool doUpdate();
  float Gravity;
  unsigned int StartHeight;
  float Height;
  float ImpactVelocityStart;
  float ImpactVelocity;
  float Dampening;
  uint32_t ClockTimeSinceLastBounce;
  uint32_t TimeSinceLastBounce;
  unsigned int lastPosition;
};
//-------------------------------------------------------------------------------------

#endif // NPBOUNCINGBALLS_H
