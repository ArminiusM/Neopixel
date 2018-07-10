// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npBouncingBall.h"
//-------------------------------------------------------------------------------------
npBouncingBall::npBouncingBall(unsigned char red, unsigned char green, unsigned char blue, unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay, red, green, blue)
{
  init();
}
//-------------------------------------------------------------------------------------
npBouncingBall::npBouncingBall(unsigned int SpeedDelay, npVirtualNeo Target) : npBase(Target, SpeedDelay)
{
  init();
}
//-------------------------------------------------------------------------------------
npBouncingBall::~npBouncingBall()
{
}
//-------------------------------------------------------------------------------------
void npBouncingBall::doInit()
{
  Gravity = -9.81;
  StartHeight = 1;
  ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  Height = StartHeight;
  ImpactVelocity = ImpactVelocityStart;
  Dampening = 0.90 - 0.0/pow(1,2);
  lastPosition = 0;
}
//-------------------------------------------------------------------------------------
bool npBouncingBall::doUpdate()
{
  bool rc = false;
  if (doRainbow) {
    Wheel(((Position * 256 / target->numPixels()) + Position) & 255, &r, &g, &b);
  }
  setPixelColor(lastPosition, 0, 0, 0);
  TimeSinceLastBounce = millis() - ClockTimeSinceLastBounce;

  Height = 0.5 * Gravity * pow(TimeSinceLastBounce/1000. , 2.0 ) + ImpactVelocity * TimeSinceLastBounce/1000.;
  if (Height < 0 ) {
    Height = 0;
    ImpactVelocity = Dampening * ImpactVelocity;
    ClockTimeSinceLastBounce = millis();
    if (ImpactVelocity < 0.01 ) {
      ImpactVelocity = ImpactVelocityStart;
      done = true;
    }
  }
  Position = round(Height * (target->numPixels() - 1) / StartHeight);
  setPixelColor(Position,r, g, b);
  lastPosition = Position;
  rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
