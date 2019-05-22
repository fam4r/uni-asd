/*
 * Fabrizio Margotta
 * 789072
 * Computer Science and Engineering
 * University of Bologna
 */

#include "bloom.h"

/*
 * Writes 1 in the Bloom Filter in the position given from the hash function
 * to the given element.
 */
void insertElem(const uint8_t* elem)
{
    int i;
    for(i = 1; i <= k; i++)
    {
        filter[hashFunction(elem, i)] = 1;
    }
}

/*
 * Tells if given element is present in the Bloom Filter.
 */
bool checkElem(const uint8_t* elem)
{
    int i;
    for(i = 1; i <= k; i++)
    {
        if(filter[hashFunction(elem, i)] == 0)
        {
            return false;
        }
    }

    return true;
}

/*
 * Allocates space for the Bloom Filter (array of booleans),
 * then calls `insertElem` with each element of the construction set as
 * parameter
 */
void buildFilter(const uint8_t** dataset)
{
    int i;
    filter = calloc(m, sizeof(bool));
    /*
    filter = malloc(m * sizeof(bool));
    for(i = 0; i < m; i++) 
    {
        filter[i] = 0; // zero-ing Bloom Filter (initialization)
    }
    */

    for(i = 0; i < n; i++)
    {
        insertElem(dataset[i]);
    }

    //printf("%hhu", (uint8_t)*dataset[n - 1]);
}

void selfCheck(const uint8_t** dataset, FILE* fout)
{
    int i;
    int tp = 0;
    for(i = 0; i < n; i++)
    {
        if(checkElem(dataset[i]))
        {
            tp++;
        }
    }
    
    fprintf(fout, "True positives (self-check): %d\n", tp);
}

void nonElementsCheck(const uint8_t** dataset, FILE* fout)
{
    int i;
    int fp = 0;
    int tn = 0;
    for(i = 0; i < non_elements; i++)
    {
        if(checkElem(dataset[i]))
        {
            fp++;
        }
        else
        {
            tn++;
        }
    }

    fprintf(fout, "True negatives: %d\n", tn);
    fprintf(fout, "False positives: %d\n", fp);
    fprintf(fout, "FPR: %f", (fp/(double)non_elements));
}
