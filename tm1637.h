#include <TM1637.h>

//set clk and dio pin for tm1637
const int tm1637clk = 2;
const int tm1637dio = 3;
TM1637 tm(tm1637clk, tm1637dio);