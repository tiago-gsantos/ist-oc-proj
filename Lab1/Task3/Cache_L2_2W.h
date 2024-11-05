#ifndef CACHE_L2_2W_H
#define CACHE_L2_2W_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../Cache.h"

#define L1_NUM_LINES (L1_SIZE/BLOCK_SIZE)
#define L2_NUM_LINES (L2_SIZE/(BLOCK_SIZE*2))

/*************** Auxiliar *********************/
uint32_t logBase2(uint32_t x);

uint32_t pow2(uint32_t e);

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
  uint8_t Valid[2];
  uint8_t Dirty[2];
  uint32_t Tag[2];
  uint8_t LRUblock;
} CacheLine2way;

typedef struct CacheLine {
  uint8_t Valid;
  uint8_t Dirty;
  uint32_t Tag;
} CacheLine;

typedef struct CacheL1 {
  uint32_t init;
  CacheLine lines[L1_NUM_LINES];
} CacheL1;

typedef struct CacheL2 {
  uint32_t init;
  CacheLine2way lines[L2_NUM_LINES];
} CacheL2;

/*********************** Interfaces *************************/

void read(uint32_t, uint8_t *);

void write(uint32_t, uint8_t *);

#endif