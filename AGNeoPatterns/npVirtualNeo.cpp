#include <stdio.h>
#include "npVirtualNeo.h"
//-------------------------------------------------------------------------------------
npVirtualNeo::npVirtualNeo(npNeoPixel *Strip, unsigned int start, unsigned int end, unsigned int step, direction dir, unsigned int rows)
{
  isUserDefined = false;
  pixels   = NULL;
  neo      = Strip;
  neoStart = start;
  neoEnd   = end;
  neoDir   = dir;
  neoRows  = rows;
  neoCols  = neo->numPixels() / neoRows;
  if (neoStart >= neo->numPixels()) neoStart = neo->numPixels()-1;
  if (neoEnd >= neo->numPixels()) neoEnd = neo->numPixels()-1;
  if (neoStart > neoEnd) {
    reverse = true;
    int h = neoStart;
    neoStart = neoEnd;
    neoEnd = h;
  }
  else reverse = false;
  neoStep  = step;
  if (neoStep < 1) neoStep = 1;
  neoSize = (neoEnd - neoStart) / neoStep + 1;
}
//-------------------------------------------------------------------------------------
npVirtualNeo::npVirtualNeo(npNeoPixel *Strip)
{
  isUserDefined = true;
  neo      = Strip;
  neoStart = 0;
  neoEnd   = 0;
  neoDir   = ROWHORI;
  neoRows  = 1;
  neoCols  = 0;
  neoStart = 0;
  neoEnd   = 0;
  reverse  = false;
  neoStep  = 1;
  neoSize  = 0;
  pixels   = NULL;
}
//-------------------------------------------------------------------------------------
npVirtualNeo::~npVirtualNeo()
{
  if (pixels != NULL) delete [] pixels;
}
//-------------------------------------------------------------------------------------
npVirtualNeo::npVirtualNeo(const npVirtualNeo &A)
{
  neo           = A.neo;
  neoStart      = A.neoStart;
  neoEnd        = A.neoEnd;
  neoSize       = A.neoSize;
  neoStep       = A.neoStep;
  neoDir        = A.neoDir;
  neoRows       = A.neoRows;
  neoCols       = A.neoCols;
  reverse       = A.reverse;
  isUserDefined = A.isUserDefined;
  pixels        = NULL;
  if (isUserDefined) {
    pixels        = new unsigned int[neo->numPixels()];
    if (pixels) {
      for (int i=0; i<neoSize; i++) {
        pixels[i] = A.pixels[i];
      }
    }
  }
}
//-------------------------------------------------------------------------------------
bool npVirtualNeo::add(unsigned int ledNo)
{
  bool rc = false;
  if (isUserDefined) {
    if (pixels == NULL) pixels   = new unsigned int[neo->numPixels()];
    if (pixels) {
      if (neoSize < neo->numPixels()) {
        pixels[neoSize] = ledNo;
        neoSize++;
        rc = true;
      }
    }
  }
  return rc;
}
//-------------------------------------------------------------------------------------
void npVirtualNeo::clear()
{
  if (isUserDefined) neoSize = 0;
}
//-------------------------------------------------------------------------------------
unsigned int npVirtualNeo::getStart()
{
  return neoStart;
}
//-------------------------------------------------------------------------------------
unsigned int npVirtualNeo::getEnd()
{
  return neoEnd;
}
//-------------------------------------------------------------------------------------
bool npVirtualNeo::isReverse()
{
  return reverse;
}
//-------------------------------------------------------------------------------------
unsigned int npVirtualNeo::numPixels()
{
  return neoSize;
}
//-------------------------------------------------------------------------------------
npNeoPixel *npVirtualNeo::getStrip()
{
  return neo;
}
//-------------------------------------------------------------------------------------
bool npVirtualNeo::checkNeoIndex(unsigned int index)
{
  bool rc = false;
  if (index < neo->numPixels()) rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
bool npVirtualNeo::checkLocalIndex(unsigned int index)
{
  bool rc = false;
  if (index < neoSize) rc = true;
  return rc;
}
//-------------------------------------------------------------------------------------
unsigned int npVirtualNeo::getPosition(unsigned int value)
{
//  printf("Step: %d\n", neoStep);
//  printf("%2d -> ", value);
  if (isUserDefined) {
    if (value < neoSize) value = pixels[value];
  }
  else {
    if (neoStep == 1) {
      if (reverse) value = neoEnd - value;
      else value = neoStart + value;
    }
    else {
      if (reverse) value = neoEnd - neoStep * value;
      else value = neoStart + neoStep * value;
    }
    if (value >= neo->numPixels()) value = neo->numPixels()-1;
    if (neoDir == ROWVERT) value = value/neoRows + neoCols * (value - (value/neoRows) * neoRows);
//    else if (neoDir == ZIGHORI) value = (value/neoCols)%2 == 0 ? value: value + neoRows - 2 * (value%neoCols);
    else if (neoDir == ZIGHORI) value = (value/neoCols)%2 == 0 ? value: value + neoCols - 2 * (value%neoCols) - 1;
    else if (neoDir == ZIGVERT) value = (value%neoRows)%2 == 0 ? value/neoRows + neoCols * (value - (value/neoRows) * neoRows) : neoCols * (1 + value%neoRows) - 1 - value/neoRows;
  }
//  printf("%2d\n", value);
  return value;
}
//-------------------------------------------------------------------------------------
void npVirtualNeo::setPixelColor(unsigned int ledNo, unsigned char red, unsigned char green, unsigned char blue)
{
  if (checkLocalIndex(ledNo)) neo->setPixelColor(getPosition(ledNo), red, green, blue);
}
//-------------------------------------------------------------------------------------
void npVirtualNeo::setPixelColor(unsigned int ledNo, uint32_t color)
{
//  printf("ledNo %d   -   %d\n", ledNo, getPosition(ledNo));
  if (checkLocalIndex(ledNo)) neo->setPixelColor(getPosition(ledNo), color);
}
//-------------------------------------------------------------------------------------
uint32_t npVirtualNeo::getPixelColor(unsigned int ledNo)
{
  uint32_t rc = 0;
  if (checkLocalIndex(ledNo)) rc = neo->getPixelColor(getPosition(ledNo));
  return rc;
}
//-------------------------------------------------------------------------------------
