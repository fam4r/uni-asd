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
 * @returns if the element is present or not in the Bloom Filter.
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
 *
 * Note: `calloc` call sets allocated memory to zero, so initializates the Bloom
 * Filter.
 */
void buildFilter(const uint8_t** dataset)
{
    int i;
    filter = calloc(m, sizeof(bool));

    for(i = 0; i < n; i++)
    {
        insertElem(dataset[i]);
    }
}

/*
 * Checks the Bloom Filter consistency with a self-test (should be given the
 * same dataset as the one used to fill the Bloom Filter itself)
 */
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

/*
 * Checks the Bloom Filter consistency with a test (should be given the a
 * dataset without common elements with the one used to fill the Bloom Filter
 * itself)
 */
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
