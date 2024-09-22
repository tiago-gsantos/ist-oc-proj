#include "./Task1/L1Cache.h"

int main() {

  uint32_t value1, value2, clock;

  resetTime();
  initCache();
  value1 = 37;
  value2 = 0;

  write(356, (uint8_t *)(&value1));

  //clock = getTime();
  //printf("Time: %d\n", clock);

  read(356, (uint8_t *)(&value2));
  //clock = getTime();
  //printf("Time: %d\n", clock);
  printf("value2: %d\n", value2);
  printf("value1: %d\n", value1);
  write(512, (uint8_t *)(&value1));
  //clock = getTime();
  //printf("Time: %d\n", clock);

  read(512, (uint8_t *)(&value2));
  //clock = getTime();
  //printf("Time: %d\n", clock);
  printf("value2: %d\n", value2);
  printf("value1: %d\n", value1);

  

  return 0;
}
