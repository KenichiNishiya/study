#include <stdio.h>
#include <stdlib.h>

int main () {
   int id;
   char nome[20], categoria[20];
   double preco;

   FILE *fp = fopen("a.txt","r");
   
   /* rewind(fp); */
   fscanf(fp, "%d %s %s %lf", &id, nome, categoria, &preco);
   
   printf("Read id |%d|\n", id );
   printf("Read nome |%s|\n", nome );
   printf("Read categoria |%s|\n", categoria );
   printf("Read preco |%lf|\n", preco );

   fclose(fp);
   
   return(0);
}
