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
#include <pthread.h>

///   SERVER   

void* new_client(void *a){
	int connect_d = (int)a;
	int status;
	char ch = 0;
	char buf[255];
	FILE* file = fopen("imagen.ppm", "w");
	
	printf("New client, total: %d\n", client_counter+1);
	client_counter++;
	
	//ejecucion normal
	say(connect_d,"Welcome, ppm compress server\r\n");
	if(say(connect_d,"Envía el archivo\r\n")!=-1){
		get_line(connect_d);	
	}
	printf("%s", buf);
	
    client_counter--;
    fclose(file);
	return NULL;
}



int main(int argc, char *argv[])
{
    //Declaring process variables.
    int server_sockfd, client_sockfd;
    int server_len ; 
    int status ; 
    unsigned client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
	char ch;
	char *port = argv[1];
	char *p;
	long l;
	l = strtol (port, &p, 0);
	int contadorClientes = 0;
	int cont = 0;
	
	
	
	printf("Servidor de reducción de imágenes PPM\n");
	printf("Listo para recibir conexiones en el puerto %ld\n" , l);
	
	//Remove any old socket and create an unnamed socket for the server.
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(l) ; 
    server_len = sizeof(server_address);
	
	/*
	 int bind(int socket_descriptor,
	 struct sockaddr *local_address,
	 int address_length)
	 This function returns 0 on success and -1 if it fail
	 */
	
    status = bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    printf("status from bind = %d\n", status ) ; 
	
    /*
	 int listen(int s,int backlog);
	 s = The socket descriptor.
	 
	 backlog = Maximum length for the queue of pending connections. If backlog is less than 0, its value is set to 0. 
	 The maximum value for backlog is 32 767. If the value passed is greater than 32 767, the value is set to 32 767.
	 
	 Create a connection queue and wait for clients
	 Return code 0 indicates that the function was successful
	 
	 
	 */
    status = listen(server_sockfd, 5);
    printf("status from listen = %d\n", status ) ; 
	
    client_len = sizeof(client_address);
	
	/*
	 SOCKET accept(
	 _In_     SOCKET s,
	 _Out_    struct sockaddr *addr,
	 _Inout_  int *addrlen
	 );
	 
	 If no error occurs, accept returns a value of type SOCKET that is a descriptor for the new socket. 
	 This returned value is a handle for the socket on which the actual connection is made.
	 
	 */
	
	while (1) {
	
	client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
	printf("after accept()... client_sockfd = %d\n", client_sockfd) ; 
	
	
    while(1)
    {
		
	
        //Accept a connection
        //client_len = sizeof(client_address);
        //client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        //printf("after accept()... client_sockfd = %d\n", client_sockfd) ; 
        //Read write to client on client_sockfd
		
        status = read(client_sockfd, &ch, 1);
        //printf("status from read = %d\n", status ) ;  
		if (ch == EOF) {
			break;
			close(client_sockfd);
		}
		printf("Char from client = %c\n", ch);
		cont++;
        write(client_sockfd, &ch, 1);
		
    }
    printf("server listening\n");
	printf("contador %i\n", cont);
	}

    return 0;
}