#include "Cache_L1.h"

uint8_t L1CacheData[L1_SIZE];
uint8_t DRAM[DRAM_SIZE];
uint32_t time;
CacheL1 L1Cache;

/**************** Auxiliar ******************/
uint32_t logBase2(uint32_t x) {
  uint32_t log = 0;

    while (x > 1) {
        x = x / 2;
        log++;
    }

    return log;
}

uint32_t pow2(uint32_t e) {
  uint32_t pow = 1;

  while (e > 0) { 
    pow = pow * 2;
    e --;
  }

  return pow;
}

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

void accessL1(uint32_t address, uint8_t *data, uint32_t mode) {

  uint32_t index, Tag, MemAddress, num_bits_index, num_bits_offset;
  uint8_t TempBlock[BLOCK_SIZE];

  // init cache
  if (L1Cache.init == 0) {
    for(int i = 0; i < L1_NUM_LINES; i++){
      L1Cache.lines[i].Valid = 0;
    }
    L1Cache.init = 1;
  }
  
  num_bits_offset = logBase2(BLOCK_SIZE);
  num_bits_index = logBase2(L1_NUM_LINES);

  Tag = address >> (num_bits_offset + num_bits_index);
  index = (address >> num_bits_offset) % L1_NUM_LINES;
  
  MemAddress = (address >> num_bits_offset) << num_bits_offset; 

  CacheLine *Line = &L1Cache.lines[index];
  
  /* access Cache*/

  if (!Line->Valid || Line->Tag != Tag) {         // if block not present - miss
    accessDRAM(MemAddress, TempBlock, MODE_READ); // get new block from DRAM

    if ((Line->Valid) && (Line->Dirty)) { // if block dirty
      uint32_t MemAddressDirty = ((Line->Tag << num_bits_index) + index) << num_bits_offset;
      
      accessDRAM(MemAddressDirty, &(L1CacheData[index * BLOCK_SIZE]), MODE_WRITE); // update block in DRAM
    }

    memcpy(&(L1CacheData[index * BLOCK_SIZE]), TempBlock, BLOCK_SIZE); // write new block from DRAM to cache
    Line->Valid = 1;
    Line->Tag = Tag;
    Line->Dirty = 0; // pk é que aqui nao continua dirty?
  }

  uint32_t num_word = (address >> logBase2(WORD_SIZE)) % pow2(num_bits_offset-logBase2(WORD_SIZE)); // = (address % BLOCK_SIZE) >> logBase2(WORD_SIZE) ???
  uint32_t num_byte = address % pow2(num_bits_offset-logBase2(BLOCK_SIZE/WORD_SIZE)); // = addresss % pow2(WORD_SIZE) ???

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
