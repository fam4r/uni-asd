#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

uint32_t hashMapping(uint32_t h);

uint32_t hashFunction(const uint8_t* key, int seed);

uint32_t hash_murmur3_32(const uint8_t* key, size_t len, uint32_t seed);

#endif // HASH_H_INCLUDED
