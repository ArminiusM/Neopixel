// Neopixel effect using npBase, npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#include "npBase.h"
//-------------------------------------------------------------------------------------
npBase::npBase(npVirtualNeo Target, unsigned int Delay, unsigned char red, unsigned char green, unsigned char blue, bool KeepBackground, bool AutoUpdate)
{
  r = red;
  g = green;
  b = blue;
  loopDelay = Delay;
  keepBackground = KeepBackground;
  target = new npVirtualNeo(Target);
  pixels = NULL;
  started = false;
  doRainbow = false;
  doDelay = true;
  counter = 1;
  autoUpdate = AutoUpdate;
  Amps = 0.0;
}
//-------------------------------------------------------------------------------------
npBase::npBase(npVirtualNeo Target, unsigned int Delay, bool KeepBackground, bool AutoUpdate)
{
  loopDelay = Delay;
  target = new npVirtualNeo(Target);
  keepBackground = KeepBackground;
  pixels = NULL;
  started = false;
  doRainbow = true;
  doDelay = true;
  counter = 1;
  autoUpdate = AutoUpdate;
  Amps = 0.0;
}
//-------------------------------------------------------------------------------------
npBase::~npBase()
{
  delete target;
  if (pixels) delete [] pixels;
}
//-------------------------------------------------------------------------------------
void npBase::init()
{
  doInit();
  ClockTimeSinceLastUpdate = millis();
  Position = 0;
  done = false;
}
//-------------------------------------------------------------------------------------
bool npBase::update() {
  bool rc = false;
  if (!done) {
    if (!started) {
      started = true;
      TimeStampOfFirstRun = millis();
    }
    TimeSinceLastUpdate =  millis() - ClockTimeSinceLastUpdate;
    if (doDelay) {
      if (TimeSinceLastUpdate > loopDelay) {
        ClockTimeSinceLastUpdate = millis();
        rc = doUpdate();
      }
    }
    else {
      ClockTimeSinceLastUpdate = millis();
      rc = doUpdate();
    }
    if (autoUpdate && rc) Amps = target->getStrip()->npShow();
  }
  return rc;
}
//-------------------------------------------------------------------------------------
float npBase::getAmps() {
	return Amps;
}
//-------------------------------------------------------------------------------------
void npBase::restart()
{
  init();
  TimeStampOfLastRun = millis();
  counter++;
}
//-------------------------------------------------------------------------------------
bool npBase::hasFinished()
{
  return done;
}
//-------------------------------------------------------------------------------------
uint32_t npBase::getCounter()
{
  return counter;
}
//-------------------------------------------------------------------------------------
uint32_t npBase::getPosition()
{
  return Position;
}
//-------------------------------------------------------------------------------------
uint32_t npBase::getMillisFromFirstRun()
{
  return millis() - TimeStampOfFirstRun;
}
//-------------------------------------------------------------------------------------
uint32_t npBase::getMillisFromLastRun()
{
  return millis() - TimeStampOfLastRun;
}
//-------------------------------------------------------------------------------------
void npBase::changeColor(unsigned char red, unsigned char green, unsigned char blue)
{
  r = red;
  g = green;
  b = blue;
  doRainbow = false;
}
//-------------------------------------------------------------------------------------
void npBase::changeColor()
{
  doRainbow = true;
}
//-------------------------------------------------------------------------------------
bool npBase::setPixelColor(unsigned int ledNo, unsigned char red, unsigned char green, unsigned char blue)
{
  target->setPixelColor(ledNo, red, green, blue);
  return true;
}
//-------------------------------------------------------------------------------------
bool npBase::setPixelColor(unsigned int ledNo, uint32_t color)
{
  target->setPixelColor(ledNo, color);
  return true;
}
//-------------------------------------------------------------------------------------
uint32_t npBase::getPixelColor(unsigned int ledNo)
{
  uint32_t rc = 0;
  rc = target->getPixelColor(ledNo);
  return rc;
}
//-------------------------------------------------------------------------------------
bool npBase::setAll(unsigned char red, unsigned char green, unsigned char blue)
{
  for (unsigned int i=0; i<target->numPixels(); i++) {
    setPixelColor(i, red, green, blue);
  }
  return true;
}
//-------------------------------------------------------------------------------------
bool npBase::allOff() {
  for (unsigned int i=0; i<target->numPixels(); i++) {
    setPixelColor(i, 0);
  }
  return true;
}
//-------------------------------------------------------------------------------------
void npBase::savePixels()
{
  if (pixels == NULL) pixels = new uint32_t[target->numPixels()];
  if (pixels) {
    for (unsigned int i=0; i<target->numPixels(); i++) {
      pixels[i] = getPixelColor(i);
    }
  }
}
//-------------------------------------------------------------------------------------
bool npBase::restorePixels()
{
  if (pixels) {
    for (unsigned int i=0; i<target->numPixels(); i++) {
      setPixelColor(i, pixels[i]);
    }
  }
  return true;
}
//-------------------------------------------------------------------------------------
void npBase::getColor(unsigned int pos, unsigned char *r, unsigned char *g, unsigned char *b)
{
  unsigned int oldColor;
  oldColor = target->getStrip()->getPixelColor(pos);
  *r = (oldColor & 0x00ff0000UL) >> 16;
  *g = (oldColor & 0x0000ff00UL) >> 8;
  *b = (oldColor & 0x000000ffUL);
}
//-------------------------------------------------------------------------------------
void npBase::Wheel(unsigned int WheelPos, unsigned char *r, unsigned char *g, unsigned char *b)
{
  if(WheelPos < 85) {
    *r = WheelPos * 3;
    *g = 255 - WheelPos * 3;
    *b = 0;
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    *r = 255 - WheelPos * 3;
    *g = 0;
    *b = WheelPos * 3;
  } else {
    WheelPos -= 170;
    *r = 0;
    *g = WheelPos * 3;
    *b = 255 - WheelPos * 3;
  }
}
//-------------------------------------------------------------------------------------
bool npBase::fadeToBlack(unsigned int ledNo, int fadeValue, bool *allOff)
{
  return fadeToColor(ledNo, 0, 0, 0, fadeValue, allOff);
}
//-------------------------------------------------------------------------------------
bool npBase::fadeToColor(unsigned int ledNo, unsigned int color, int fadeValue, bool *allOff)
{
  unsigned char red   = color >> 16 & 0xFF;
  unsigned char green = color >>  8 & 0xFF;
  unsigned char blue  = color       & 0xFF;
  return fadeToColor(ledNo, red, green, blue, fadeValue, allOff);
}
//-------------------------------------------------------------------------------------
bool npBase::fadeToColor(unsigned int ledNo, unsigned char red, unsigned char green, unsigned char blue, int fadeValue, bool *allOff)
{
  bool rc = false;
  unsigned int oldColor;
  unsigned char oldr, oldg, oldb, newr, newg, newb;
  int difr, difg, difb;

  oldColor = getPixelColor(ledNo);
  oldr = oldColor >> 16 & 0xFF;
  oldg = oldColor >>  8 & 0xFF;
  oldb = oldColor       & 0xFF;
  difr = (int)oldr - (int)red;
  difg = (int)oldg - (int)green;
  difb = (int)oldb - (int)blue;

  newr = (difr*fadeValue/256 == 0) ? red   : (int) oldr-(difr*fadeValue/256);
  newg = (difg*fadeValue/256 == 0) ? green : (int) oldg-(difg*fadeValue/256);
  newb = (difb*fadeValue/256 == 0) ? blue  : (int) oldb-(difb*fadeValue/256);

  if ((newr != red) || (newg != green) || (newb != blue)) *allOff = false;
  if ((oldr != newr) || (oldg != newg) || (oldb != newb)) {
    setPixelColor(ledNo, newr, newg, newb);
    rc = true;
  }
  return rc;
}
//-------------------------------------------------------------------------------------
