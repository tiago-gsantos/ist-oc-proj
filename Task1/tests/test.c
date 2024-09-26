#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../Cache_L1.h"

int main() {
  uint32_t value1, value2, clock;

  resetTime();
  initCache();
  

  printf("\n1º teste: ler e escrever num endereço normal:\n\n");
  
  value1 = 7;
  
  write(128, (uint8_t *)(&value1));
  clock = getTime();
  printf("Write; Address %d; Value %d; Time %d\n", 128, value1, clock);
  
  read(128, (uint8_t *)(&value2));
  clock = getTime();
  printf("Read; Address %d; Value %d; Time %d\n\n", 128, value2, clock);
  


  printf("\n2º teste: escrever no 3º byte de uma palavra:\n\n");
  
  value1 = 65537;
  
  write(2, (uint8_t *)(&value1));
  clock = getTime();
  printf("Write; Address %d; Value %d (2^16 + 1); Time %d\n", 2, value1, clock);
  
  read(0, (uint8_t *)(&value2));
  clock = getTime();
  printf("Read; Address %d; Value %d (em binário: %b); Time %d\n", 0, value2, value2, clock);

  read(4, (uint8_t *)(&value2));
  clock = getTime();
  printf("Read; Address %d; Value %d; Time %d\n", 0, value2, clock);

  return 0;
}