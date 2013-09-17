/*
**Cliente para enviar imagenes ppm
**Autores:
**Amilcar Andrade
**Julio Rodríguez
**Contiene codigo proporcionado por el profesor
**Ariel Ortiz, basado en el capitulo 11 de Griffiths.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define BUFFER_SIZE 256


/**********************************************************/
/*******FUNCIONES PROPORCIONADAS POR EL PROFESOR***********/
void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int open_socket(char *host, char *port) {
    struct addrinfo *res;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &res) == -1)
        error("Can't resolve the address");
    int d_sock = socket(res->ai_family, res->ai_socktype,
    res->ai_protocol);
    if (d_sock == -1)
        error("Can't open socket");
    int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    if (c == -1)
        error("Can't connect to socket");
    return d_sock;
}


int say(int socket, char *s) {
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
    fprintf(stderr, "%s: %s\n", "Error talking to the server", 
      strerror(errno));
  return result;
}

void read_line(int socket, char*buf, int len) {
    char rec;
    while (len) {
        
        int bytesRcvd = recv(socket, &rec, 1, 0);
            
        if (bytesRcvd == -1)
            error("Can't read from server");
        if (rec == '\n') {
            *buf = '\0';
            return;
        }
        *buf++ = rec;
        len--;        
    }
}

void get_line(int socket) {
    char buf[BUFFER_SIZE];
    
    read_line(socket, buf, BUFFER_SIZE - 1);
    buf[BUFFER_SIZE - 1] = '\0';
    printf("%s\n", buf);
}

void put_line(int socket, char* message) {
    printf("%s", message);
    say(socket, message);
}
/**********************************************************/
/**********************************************************/


int main(int argc, char *argv[]) {
	unsigned int c = 0;
	int counter = 0;
	int rc = 0;
	int status = 0;
	
	//revision de los datos proporcionados por el usuario
	if (argc != 5) {
        printf("Parametros: IP, puerto, archivo in, archivo out\n");
        printf("Revisar los parametros\n");
        exit(1);
    }
    
    char* host = argv[1];
    char* port = argv[2];

	printf("Cliente para educción de imágenes PPM\n");
	
    //establecer la conexion
    int d_sock;
    d_sock = open_socket(host, port);
	get_line(d_sock);		//Bienvenida del servidor
	get_line(d_sock);		//petición de datos
	
	//enviar char por char al servidor
	FILE* file = fopen(argv[3], "r");
	while(c != EOF){
		c = fgetc(file);
		if(isprint(c) || isspace(c) || ispunct(c)){
			rc = write(d_sock, &c, 1);		
			//printf("Char that client send = %c\n", c);
		}
	}
	fclose(file);
	printf("Imagen enviada\n");
	
	//recibir y crear el nuevo archivo ppm
	/*
	file = fopen(argv[4], "w");
	if(say(d_sock,"Listo para recibir\r\n")!=-1){
	 	status = read(d_sock, &c, 1);
		while(status){
			//printf("Char from client = %c\n", c);
			fprintf(file, "%c", c);
			status = read(d_sock, &c, 1);
		}	
		
	}
	fclose(file);
	*/
	close(d_sock);	
	return 0;
} 
