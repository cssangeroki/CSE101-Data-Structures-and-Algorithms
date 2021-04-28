#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"

#define MAX_LEN 255

int main(int argc, char * argv[]){

   int count=0;
   FILE *in, *out;
   char str[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in == NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out == NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   while( fgets(str, MAX_LEN, in) != NULL){
     count++;
}


   rewind(in);

   char line1[count - 1][MAX_LEN];
   int line2 = -1;

   while(fgets(str, MAX_LEN, in) != NULL)
   {
      strcpy(line1[++line2], str);
   }

   List list = newList(); 

   append(list, 0); 

   //INSERTION SORT
   for(int i = 1; i < count; i++)
   {
      char *temp = line1[i];
      int j = i - 1;
     
      moveBack(list);
    
      while(j >= 0 && strcmp(temp, line1[get(list)])<= 0)
           {
             
               --j;
               movePrev(list);
           }
           if(index(list) >= 0) insertAfter(list, i);

           else
           {
               prepend(list, i);
           }
   }
   
   moveFront(list);
   
   while(index(list) >= 0)
   {
     fprintf(out, "%s", line1[get(list)]);
     moveNext(list);
   }

  
   fclose(in);
   fclose(out);

 
   freeList(&list);

   return 0;
   }

