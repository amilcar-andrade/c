/*
**Cliente para enviar imagenes ppm
**Autores:
**Amilcar Andrade
**Julio Rodríguez
**Contiene codigo proporcionado por el profesor
**Ariel Ortiz, basado en el capitulo 11 de Griffiths.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "ppm.h"

#define MAX_CLIENTS 10
#define NAME_TAM 20

/**********************************************************/
/*******FUNCIONES PROPORCIONADAS POR EL PROFESOR***********/
void error(char *msg) {
	printf("%s\n", msg);
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int catch_signal(int sig, void (*handler)(int))
 {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction (sig, &action, NULL);
}

int read_in(int socket, char *buf, int len) {
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    while ((c > 0) && (s[c-1] != '\n')) {
        s += c; 
        slen -= c;
        c = recv(socket, s, slen, 0);
    }
    if (c < 0) 
        return c;
    else if (c == 0)
        buf[0] = '\0';
    else
        s[c-1]='\0';
    return len - slen;
}

int open_listener_socket() {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Can't open socket");
    return s;
}

void bind_to_port(int socket, int port) {
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t) htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, 
            (char *)&reuse, sizeof(int)) == -1)
        error("Can't set the reuse option on the socket");
    int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (c == -1)
        error("Can't bind to socket");
}

int say(int socket, char *s) {
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "%s: %s\n", "Error talking to the client",
            strerror(errno));
    return result;
}

int listener_d;

void handle_shutdown(int sig) {
    if (listener_d)
        close(listener_d);
    fprintf(stderr, "\nBye!\n");
    exit(0);
}
/**********************************************************/
/**********************************************************/

int client_counter = 0;

//arreglo de threads, 10 por el numero maximo de clientes
//arreglo de struct con la información para el thread
pthread_t threads[MAX_CLIENTS];


/********************thread function*****************/
void* new_client(void *a){
	//variables para la conexion y lectura de datos
	int connect_d = (int)a;
	int status = 1;
	char c = 0;
	//datos para la creacion de archivos
	char name[NAME_TAM];
	char* type = ".ppm";
	//ppm para ser manipulado
	ppm_t ppm_data;
	
	printf("New client, total: %d\n", client_counter+1);
	client_counter++;
	
	//crear el archivo temporal
	sprintf(name, "%d", connect_d);
	strcat(name, type);
	printf("Archivo por crear: %s\n", name);
	
	FILE* file = fopen(name, "w");
	if (!file) {
        error("No se creo el archivo original");
    }
	//ejecucion normal
	say(connect_d,"Welcome, ppm compress server\r\n");
	if(say(connect_d,"Envía el archivo\r\n")!=-1){
		 status = read(connect_d, &c, 1);
		 while(status){
		 //printf("Char from client = %c\n", c);
		 fprintf(file, "%c", c);
		 status = read(connect_d, &c, 1);
		 }	
	}
	fclose(file);
	
	//reduccion de tamaño, uso de la librearia ppm.h
	if (ppm_open(name, &ppm_data) != OK) {
        error("Hubo un error");
    }
	ppm_save_c(name, &ppm_data);
	ppm_dispose(&ppm_data);
    
	
    file = fopen(name, "r");
   	if (!file) {
        error("No se puede abrir el archivo comprimido");
    }
	while(c != EOF){
		c = fgetc(file);
		if(isprint(c) || isspace(c) || ispunct(c)){
			write(connect_d, &c, 1);
			//printf("%c", c);		
		}
	}
	fclose(file);
    */
    
    remove(name);
	client_counter--;
	return NULL;
}


/*****************************************************/

int main(int argc, char *argv[]) {  
    
    if (argc != 2) {
        puts("Please specify port.");
        exit(1);
    }
    
    int port = atoi(argv[1]);
    
    //al teclear CTRL+C se termina el servidor
    if (catch_signal(SIGINT, handle_shutdown) == -1)    
        error("Can't set the interrupt handler"); 
    
    listener_d = open_listener_socket(); 
    bind_to_port(listener_d, port);  
    
    //maximo de clientes 10
    if (listen(listener_d, MAX_CLIENTS) == -1)    
        error("Can't listen");
    
    struct sockaddr_storage client_addr;  
    unsigned int address_size = sizeof(client_addr);  
    printf("Listening in port %d\n", port);  
    char buf[255];
    
    while (1) {
    	printf("Esperando la petición\n");    
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr,
                               &address_size);
        if (connect_d == -1){
            error("Can't open secondary socket");
		}
		//ejecución normal threads
        pthread_create(&threads[client_counter], NULL, new_client, (void*)connect_d);          
    }
    return 0;
         
    }
