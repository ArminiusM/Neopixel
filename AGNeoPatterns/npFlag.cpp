// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npFlag.h"
//-------------------------------------------------------------------------------------
npFlag::npFlag(unsigned char red1, unsigned char green1, unsigned char blue1,
               unsigned char red2, unsigned char green2, unsigned char blue2,
               unsigned char red3, unsigned char green3, unsigned char blue3,
               unsigned int SpeedDelay, unsigned int Size, npVirtualNeo Target, bool KeepBackground) : npBase(Target, SpeedDelay, KeepBackground)
{
  size = Size;
  if (size < 1) size = 1;
  size *= 3;
  oldColor = new uint32_t[size];
  colors[0] = (uint32_t)red1 << 16 | (uint32_t)green1 << 8 | (uint32_t)blue1;
  colors[1] = (uint32_t)red2 << 16 | (uint32_t)green2 << 8 | (uint32_t)blue2;
  colors[2] = (uint32_t)red3 << 16 | (uint32_t)green3 << 8 | (uint32_t)blue3;
  init();
}
//-------------------------------------------------------------------------------------
npFlag::~npFlag()
{
  delete oldColor;
}
//-------------------------------------------------------------------------------------
void npFlag::doInit()
{
}
//-------------------------------------------------------------------------------------
bool npFlag::doUpdate()
{
  int rc = false;

  if (keepBackground) {
    setPixelColor(Position-size, oldColor[size-1]);
    for (int i=(size-1); i>0; i--) {
      oldColor[i] = oldColor[i-1];
    }
    oldColor[0] = getPixelColor(Position);
  }
  else setPixelColor(Position-size, 0, 0, 0);

  for (int i=0; i<size; i++) {
    int sPosition = Position - i;
    int index = i / (size/3);
    setPixelColor(sPosition, colors[index]);
  }
  rc = true;
  Position++;
  if (Position > (target->numPixels() + size)) {
    done = true;
    Position = 0;
  }
  return rc;
}
//-------------------------------------------------------------------------------------
