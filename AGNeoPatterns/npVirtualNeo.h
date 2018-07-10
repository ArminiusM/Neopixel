#ifndef NPVIRTUALNEO_H
#define NPVIRTUALNEO_H
#include "npNeoPixel.h"
//-------------------------------------------------------------------------------------
class npVirtualNeo {
public:
  enum direction {
    ROWHORI = 0,
    ZIGHORI = 1,
    ROWVERT = 2,
    ZIGVERT = 3
  };

  npVirtualNeo(npNeoPixel *Strip, unsigned int start, unsigned int end, unsigned int step = 1, direction dir = ROWHORI, unsigned int rows = 1);
  npVirtualNeo(npNeoPixel *Strip);
  ~npVirtualNeo();
  npVirtualNeo(const npVirtualNeo &A);
  unsigned int getStart();
  unsigned int getEnd();
  bool isReverse();
  unsigned int numPixels();
  unsigned int getPosition(unsigned int value);
  npNeoPixel *getStrip();
  bool checkNeoIndex(unsigned int index);
  bool checkLocalIndex(unsigned int index);
  void setPixelColor(unsigned int ledNo, unsigned char red, unsigned char green, unsigned char blue);
  void setPixelColor(unsigned int ledNo, uint32_t color);
  uint32_t getPixelColor(unsigned int ledNo);
  bool add(unsigned int ledNo);
  void clear();
private:
  npNeoPixel *neo;
  unsigned int neoStart;
  unsigned int neoEnd;
  unsigned int neoSize;
  unsigned int neoStep;
  direction neoDir;
  unsigned int neoRows;
  unsigned int neoCols;
  bool reverse;
  bool isUserDefined;
  unsigned int *pixels;
};
//-------------------------------------------------------------------------------------

#endif // NPVIRTUALNEO_H
