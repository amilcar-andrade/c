#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
 
///   CLIENT   
 
 
int main(int argc, char *argv[])
{
    printf("Cliente para educción de imágenes PPM\n");
	FILE *text = fopen(argv[3], "r");

    int sockfd;
    int len, rc ;
    struct sockaddr_in address;
    int result;
    char ch;
	char *direccion = argv[1];
	char *port = argv[2];
	char *p;
	long l;
	l = strtol (port, &p, 0);
	unsigned int c = 0;
	int cont = 0;
	FILE *fp;

 
   //Create socket for client.
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) { 
        perror("Socket create failed.\n") ; 
        return -1 ; 
    } 
     
    //Name the socket as agreed with server.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(direccion);
    address.sin_port = htons(l);
    len = sizeof(address);
 
	
	/*
	 if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
	 error("ERROR connecting");
	 
	 This function returns 0 on success and -1 if it fail
	 */
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1)
    {
        perror("Error has occurred");
        exit(-1);
    }
	fp=fopen("Imagen.ppm","w");

	while(c != EOF){
		c = fgetc(text);
        //Read and write via sockfd
        rc = write(sockfd, &c, 1);		
		printf("Char that client send = %c\n", c);
		cont++;
		
		
		sleep(1/100);

      read(sockfd, &ch, 1);
	   ///printf("Char from server = %c\n", ch);
		
	   putc(ch,fp);

		
	}
	printf("contador %i\n", cont);
	close(sockfd);
	fclose(fp);

 
    exit(0);
}