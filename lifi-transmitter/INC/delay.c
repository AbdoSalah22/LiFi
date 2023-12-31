#include "delay.h"


void delayMs(int n)
{
  int i, j;
  for (i = 0; i < n; i++){
    for (j = 0; j < 3180; j++)
    ;
  }
}


void delayUs(int n)
{
  int i, j;
  for (i = 0; i < n; i++){
    for (j = 0; j < 3; j++)
    ;
  }
}