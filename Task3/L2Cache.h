#ifndef L2CACHE_H
#define L2CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../Cache.h"

/*************** Auxiliar *********************/

uint32_t pow2(uint32_t e);

uint32_t logBase2(uint32_t x);

/**************** Time Manipulation ***************/
void resetTime();

uint32_t getTime();

/****************  RAM memory (byte addressable) ***************/
void accessDRAM(uint32_t, uint8_t *, uint32_t);

/*********************** Cache *************************/

void initCache();
void accessL1(uint32_t, uint8_t *, uint32_t);
void accessL2(uint32_t, uint8_t *, uint32_t);

typedef struct CacheLine2way {
  uint8_t Valid1;
  uint8_t Dirty1;
  uint32_t Tag1;
  uint32_t time1;
  uint8_t Valid2;
  uint8_t Dirty2;
  uint32_t Tag2;
  uint32_t time2;
} CacheLine2way;

typedef struct CacheLine {
  uint8_t Valid;
  uint8_t Dirty;
  uint32_t Tag;
} CacheLine;

typedef struct CacheL1 {
  uint32_t init;
  CacheLine lines[L1_SIZE/BLOCK_SIZE];
} CacheL1;

typedef struct CacheL2 {
  uint32_t init;
  CacheLine2way lines[L2_SIZE/(BLOCK_SIZE*2)];
} CacheL2;

/*********************** Interfaces *************************/

void read(uint32_t, uint8_t *);

void write(uint32_t, uint8_t *);

#endif