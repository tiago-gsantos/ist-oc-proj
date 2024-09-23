#include "L1Cache.h"
#include <math.h>

uint8_t L1CacheData[L1_SIZE];
uint8_t L2Cache[L2_SIZE];
uint8_t DRAM[DRAM_SIZE];
uint32_t time;
CacheL1 L1Cache;

/**************** Time Manipulation ***************/
void resetTime() { time = 0; }

uint32_t getTime() { return time; }

/****************  RAM memory (byte addressable) ***************/
void accessDRAM(uint32_t address, uint8_t *data, uint32_t mode) {

  if (address >= DRAM_SIZE - WORD_SIZE + 1)
    exit(-1);

  if (mode == MODE_READ) {
    memcpy(data, &(DRAM[address]), BLOCK_SIZE);
    time += DRAM_READ_TIME;
  }

  if (mode == MODE_WRITE) {
    memcpy(&(DRAM[address]), data, BLOCK_SIZE);
    time += DRAM_WRITE_TIME;
  }
}

/*********************** L1 cache *************************/

void initCache() { L1Cache.init = 0; }

uint32_t log2(uint32_t x) {
  return log(x) / log(2);
}

uint32_t pow2(uint32_t e) {
  uint32_t pow = 1;

  while (e > 0) { 
    pow = pow * 2;
    e --;
  }

  return pow;
}


void accessL1(uint32_t address, uint8_t *data, uint32_t mode) {

  uint32_t index, Tag, MemAddress;
  uint8_t TempBlock[BLOCK_SIZE];

  if (L1Cache.init == 0) {
    for(int i = 0; i < (L1_SIZE/BLOCK_SIZE); i++){
      L1Cache.lines[i].Valid = 0;
    }
    L1Cache.init = 1;
  }
  
  uint32_t num_bits_offset = log2(BLOCK_SIZE);
  uint32_t num_bits_index = log2(L1_SIZE/BLOCK_SIZE);

  Tag = address >> (num_bits_offset + num_bits_index);
  index = (address >> num_bits_offset) % (pow2(num_bits_index));

  //printf("tag: %b\n", Tag);
  //printf("index: %b\n", index);
  

  CacheLine *Line = &L1Cache.lines[index];
  
  MemAddress = (address >> num_bits_offset) << num_bits_offset; 

  //printf("address: %b\n", MemAddress);

  /* access Cache*/

  if (!Line->Valid || Line->Tag != Tag) {         // if block not present - miss
    accessDRAM(MemAddress, TempBlock, MODE_READ); // get new block from DRAM

    if ((Line->Valid) && (Line->Dirty)) { 
      uint32_t MemAddressDirty = ((Line->Tag << num_bits_index) + index) << num_bits_offset;
      
      accessDRAM(MemAddressDirty, &(L1CacheData[index * BLOCK_SIZE]), MODE_WRITE);
    }

    memcpy(&(L1CacheData[index * BLOCK_SIZE]), TempBlock, BLOCK_SIZE); 
    Line->Valid = 1;
    Line->Tag = Tag;
    Line->Dirty = 0;
  }

  uint32_t num_word = (address >> log2(WORD_SIZE)) % pow2(num_bits_offset-log2(WORD_SIZE));
  uint32_t num_byte = address % pow2(num_bits_offset-log2(BLOCK_SIZE/WORD_SIZE));

  //printf("num_word: %d\n", num_word);
  //printf("num_byte: %d\n", num_byte);

  if (mode == MODE_READ) {    // read data from cache line
    memcpy(data, (&L1CacheData[index * BLOCK_SIZE] + num_word * WORD_SIZE + num_byte),
    WORD_SIZE - num_byte);
    time += L1_READ_TIME;
  }
  
  if (mode == MODE_WRITE) { // write data from cache line
   
    memcpy((&L1CacheData[index * BLOCK_SIZE] + num_word * WORD_SIZE + num_byte), data,
    WORD_SIZE - num_byte);
    time += L1_WRITE_TIME;
    Line->Dirty = 1;
  }
}

void read(uint32_t address, uint8_t *data) {
  accessL1(address, data, MODE_READ);
}

void write(uint32_t address, uint8_t *data) {
  accessL1(address, data, MODE_WRITE);
}
