#include <stdio.h>
#include <stdlib.h>


int main( int argc, char** argv ) {
    char* construction_ds = "dataset1.csv";
    char* output_file = "outputf.txt";

    FILE *fp;
    char* input;

    fp = fopen(construction_ds, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(fp)) {
      if (fscanf(fp, "%s", input) != 2)
        break;

    }

    fclose(fp);
    
    fp = fopen(output_file, "w"); // read mode

    if (fp == NULL) {
      fprintf(stderr, "Can't open output file %s!\n",
              output_file);
      exit(EXIT_FAILURE);
    }

    return 0;
}
