//compilar con gcc "gcc server.c -o server"
//ejecutar "./server"

#include <netinet/in.h>    
#include <stdio.h>    
#include <stdlib.h>    
#include <sys/socket.h>    
#include <sys/stat.h>    
#include <sys/types.h>    
#include <unistd.h>  
#include <string.h>  

    
int main() {  
// se crean los sockets  
   int create_socket, new_socket;    
   socklen_t addrlen;    
   int bufsize = 1;  
   char filecontador = '0';
   char *filename = "patito.txt";    //nombre del archivo a guardar
   char buffer = '0';       
   int cont = 0;
   char idnombre[12];
 //se crea el socket que se encarga de escuchar
   if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){printf("The socket was created\n");}
    
   struct sockaddr_in address;
   address.sin_family = AF_INET;    
   address.sin_addr.s_addr = INADDR_ANY;    
   address.sin_port = htons(6666);    
 
//se asocia el socket de escucha con el puerto
   if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){printf("Binding Socket\n");}
        
//se esperan llamadas
   while (1) 
	{  if (cont==0){

      filename = "md5Checksum.md5sum";

   }
   if (cont==1){
      filename = "videoReporte.mjpeg";
   }
   if (cont==2){
      filename = "id_video.txt";
   }
      if (listen(create_socket, 10) < 0) {    
         perror("server: listen");    
         exit(1);    
      }    
    //se acceptan las llamadas entrantes y se manda a otro socket a atender la peticion
	addrlen = sizeof(struct sockaddr_in);
      if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {    
         perror("server: accept");    
         exit(1);    
      }    
    
      if (new_socket > 0){    
         printf("The Client is connected...\n");
      }
//se leen los parametros del cliente para ver que pide
      
	FILE *fptr;
	fptr = fopen(filename, "wb");

	int leido=0;
    while(read(new_socket, &buffer, 1)>0){  

	fputc( buffer, fptr );
	leido=leido+1;
   

}
	printf("%i\n",leido);  //cantidad de bytes recibidos
   if (cont==0){// este es el caso en el que se crea el comprimido
         cont=1;
         //system("tar -xvzf ~/Escritorio/gg/pagina/videos/recibido.tar.gz");
         //system("mv ~/Escritorio/gg/pagina/videos/_2server/id_video.txt ~/Escritorio/gg/pagina/videos/id_video.txt");
         //system("mv ~/Escritorio/gg/pagina/videos/_2server/md5Checksum.md5sum ~/Escritorio/gg/pagina/videos/md5Checksum.md5sum");
         //system("md5sum -c md5Checksum.md5sum");


   }
   else if (cont==1){
      cont=2;
     // system("md5sum -c md5Checksum.md5sum");

   }
   else if (cont==2){
      system("md5sum -c md5Checksum.md5sum");
      system("sh convierte.sh");
      //system("rm id_video.txt && rm videoReporte.mjpeg");
      //system("mv md5Checksum.md5sum /otros/md5Checksum.md5sum");
      //sleep(2);
      //system("./ncambia");
   
      cont=0;
      
   }

   /////////////////////////////////////////
   ///////////////////////////////////////////
	fclose(fptr);
//sleep(1);
close(new_socket);

      
   }    
   close(create_socket);  
   //system("tar -xvzf recibido.tar.gz")  
   return 0;    
}



