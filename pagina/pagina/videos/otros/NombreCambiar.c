#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
   int ret;
   char str1[1000] = "ff.txt" ;
   char string[1000] ;

// Abrir el id unico
   FILE *f = fopen("id_video.txt", "r");

// Pasa el contenido del archivo a un string
   if(fgets(str1, 500, f)!=NULL)
   {
	puts(str1) ;
        ret = rename("videoReporte.mp4", str1) ;
   }

   fclose(f) ;
   if(ret == 0){printf("File renamed successfully") ;}
   else{printf("Error: unable to rename the file") ;}
   return(0);
}
