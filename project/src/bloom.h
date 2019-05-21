#ifndef BLOOM_H_INCLUDED
#define BLOOM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "hash.h"

#define ELEM_LENGTH 4
#define HASH_NUMBER 10
#define CELL_NUMBER 1048576

typedef enum { false, true } bool;

uint8_t** construction_dataset;
uint8_t** verification_dataset;

bool* filter;

int n;
int m;
int k;
int non_elements;

void insertElem(const uint8_t* elem);
bool checkElem(const uint8_t* elem);

void buildFilter(const uint8_t** dataset);
void selfCheck(const uint8_t** dataset, FILE* fout);
void nonElementsCheck(const uint8_t** dataset, FILE* fout);

#endif // BLOOM_H_INCLUDED
