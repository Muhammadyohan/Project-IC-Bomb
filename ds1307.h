#include "tm1638.h"

void DISP_CLOCK(uint8_t hour, uint8_t minute)
{
  int mUnit = minute % 10;
  int mTen = minute / 10;
  int hUnit = hour % 10;
  int hTen = hour / 10;

  DISP_NUM_to_7SEG(7, mUnit);
  DISP_NUM_to_7SEG(6, mTen);
  DISP_NUM_to_7SEG(5, 0x40); // - between hour and minute display
  DISP_NUM_to_7SEG(4, hUnit);
  DISP_NUM_to_7SEG(3, hTen);
}

//Hello
