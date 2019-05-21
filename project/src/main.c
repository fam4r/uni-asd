#include "bloom.h"

#define LINE_LENGTH 120

//funzione di verifica dei file di output
bool filediff(FILE* f1, FILE* f2);

// Main
int main (int argc, char* argv[])
{

   static const char* CONSTRUCTION_DATASET = "dataset1.csv";
   static const char* VERIFICATION_DATASET = "non-elements.csv";
   static const char* OUTPUT_FILE = "output.txt";
   static const char* VERIFICATION_FILE = "OUTPUT1.txt";

   char *line[LINE_LENGTH];
   int i;

   bool final_check;

   m = CELL_NUMBER;
   k = HASH_NUMBER;

   ////////// LETTURA DEI DATASET E SALVATAGGIO NEGLI ARRAY //////////

   FILE* fin = fopen(CONSTRUCTION_DATASET ,"r");
   if(fin == NULL ) exit(1);
   FILE* fver = fopen(VERIFICATION_DATASET ,"r");
   if(fver == NULL ) exit(1);
   FILE* fout = fopen(OUTPUT_FILE ,"w");
   if(fout == NULL ) exit(1);
   FILE* foutver = fopen(VERIFICATION_FILE ,"r");
   if(foutver == NULL ) exit(1);

   //conta il numero di elementi che compongono il dataset di costruzione
   n = 0;
   while ( fgets((char*)line, LINE_LENGTH, fin)!= NULL ) n++;
   //conta il numero di elementi che compongono il dataset di verifica
   non_elements = 0;
   while ( fgets((char*)line, LINE_LENGTH, fver)!= NULL ) non_elements++;

   rewind(fin);
   rewind(fver);

   construction_dataset = malloc(n * sizeof(uint8_t *));
   for(i = 0; i < n; i++) construction_dataset[i] = malloc(ELEM_LENGTH * sizeof(uint8_t));

   i=0;
   while (fgets((char*)line,LINE_LENGTH,fin)!= NULL)
   {
      memcpy(construction_dataset[i], (uint8_t*)line, ELEM_LENGTH);
      i++;
   }

   verification_dataset = malloc(non_elements * sizeof(uint8_t *));
   for(i = 0; i < non_elements; i++) verification_dataset[i] = malloc(ELEM_LENGTH * sizeof(uint8_t));

   i=0;
   while (fgets((char*)line,LINE_LENGTH,fver)!= NULL)
   {
       memcpy(verification_dataset[i],(uint8_t*)line,ELEM_LENGTH);
      i++;
   }

   ////////// COSTRUZIONE DEL FILTRO //////////

   buildFilter((const uint8_t**)construction_dataset);
   fprintf(fout,"Elementi del dataset di costruzione: %d\n", n);
   fprintf(fout,"Elementi del dataset di verifica: %d\n", non_elements);

   //////////  SELF-CHECK ELEMENTI  //////////

   selfCheck((const uint8_t**)construction_dataset, fout);

   //////////  CHECK NON ELEMENTI  //////////

   nonElementsCheck((const uint8_t**)verification_dataset, fout);

   //////////  CONTROLLO DI CORRISPONDENZA DEI RISULTATI CON IL FILE FORNITO  //////////
   fclose(fout);

   fout = fopen(OUTPUT_FILE ,"r");
   if(fout == NULL ) exit(1);

   final_check = filediff(fout, foutver);
   if(final_check) printf("Verifica dei risultati eseguita con successo.\n");
   else printf("Verifica dei risultati fallita.\n");

   free(filter);
   free(construction_dataset);
   free(verification_dataset);

   fclose(fin);
   fclose(fver);
   fclose(fout);
   fclose(foutver);

   return 0;
}


//confronta due file; ritorna true se il contenuto è identico, false altrimenti
bool filediff(FILE* fp1, FILE* fp2)
{
    char ch1, ch2;

    rewind(fp1);
    rewind(fp2);

    ch1 = getc(fp1);
    ch2 = getc(fp2);
    while(ch1 == '\r') ch1 = getc(fp1);
    while(ch2 == '\r') ch2 = getc(fp2);

    //legge un char da entrambi i file
    while(ch1 != EOF || ch2 != EOF)
    {
        if(ch1 != ch2) return false;
        ch1 = getc(fp1);
        ch2 = getc(fp2);
        while(ch1 == '\r') ch1 = getc(fp1);
        while(ch2 == '\r') ch2 = getc(fp2);
    }

    return true;
}
