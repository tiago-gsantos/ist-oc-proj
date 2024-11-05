#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../Cache_L2_1W.h"

int main() {
  uint32_t value1, value2, clock;

  resetTime();
  initCache();

  value1 = 27;
  
  write(0, (uint8_t *)(&value1));
  clock = getTime();
  printf("Write; Address %d; Value %d; Time %d\n", 0, value1, clock);

  read(0, (uint8_t *)(&value2));
  clock = getTime();
  printf("Read; Address %d; Value %d; Time %d\n", 0, value2, clock);

  value1 = 39;

  write(32768, (uint8_t *)(&value1));
  clock = getTime();
  printf("Write; Address %d; Value %d; Time %d\n", 32768, value1, clock);

  read(32768, (uint8_t *)(&value2));
  clock = getTime();
  printf("Read; Address %d; Value %d; Time %d\n", 32768, value2, clock);

  read(0, (uint8_t *)(&value2));
  clock = getTime();
  printf("Read; Address %d; Value %d; Time %d\n", 0, value2, clock);

  return 0;
}