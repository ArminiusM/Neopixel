// Neopixel base effect class using npNeoPixel and npVirtualNeo classes.
// Based on the ideas from:
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ 
//
#ifndef NPBASE_H
#define NPBASE_H

#include <math.h>
#include "npVirtualNeo.h"
//-------------------------------------------------------------------------------------
class npBase {
public:
  npBase(npVirtualNeo Target, unsigned int Delay, unsigned char red, unsigned char green, unsigned char blue, bool KeepBackground = false, bool AutoUpdate = true);
  npBase(npVirtualNeo Target, unsigned int Delay, bool KeepBackground = false, bool AutoUpdate = true);
  ~npBase();
  bool update();
  void restart();
  bool hasFinished();
  void changeColor(unsigned char red, unsigned char green, unsigned char blue);
  void changeColor();
  void getColor(unsigned int pos, unsigned char *r, unsigned char *g, unsigned char *b);
  uint32_t getCounter();
  uint32_t getPosition();
  uint32_t getMillisFromFirstRun();
  uint32_t getMillisFromLastRun();
  void savePixels();
  bool restorePixels();
  bool setPixelColor(unsigned int ledNo, unsigned char red, unsigned char green, unsigned char blue);
  bool setPixelColor(unsigned int ledNo, uint32_t color);
  uint32_t getPixelColor(unsigned int ledNo);
  bool setAll(unsigned char red, unsigned char green, unsigned char blue);
  bool allOff();
  float getAmps();
protected:
  void init();
  virtual void doInit() = 0;
  virtual bool doUpdate() = 0;
  void Wheel(unsigned int WheelPos, unsigned char *r, unsigned char *g, unsigned char *b);
  bool fadeToBlack(unsigned int ledNo, int fadeValue, bool *allOff);
  bool fadeToColor(unsigned int ledNo, unsigned int color, int fadeValue, bool *allOff);
  bool fadeToColor(unsigned int ledNo, unsigned char red, unsigned char green, unsigned char blue, int fadeValue, bool *allOff);
  unsigned char r, g, b;
  bool keepBackground;
  uint32_t *pixels;
  bool doRainbow;
  npVirtualNeo *target;
  unsigned int loopDelay;
  bool doDelay;
  bool autoUpdate;
  unsigned int Position;
  uint32_t TimeSinceLastUpdate;
  uint32_t ClockTimeSinceLastUpdate;
  bool started;
  uint32_t TimeStampOfFirstRun;
  uint32_t TimeStampOfLastRun;
  uint32_t counter;
  bool done;
  float Amps;
};
//-------------------------------------------------------------------------------------

#endif // NPFIRE_H
