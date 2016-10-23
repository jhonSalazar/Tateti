/*
 * conexiones.c
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */



#include "conexiones.h"


int abrir_socket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		perror("error al abrir el descriptor :");

	return sockfd;

}


void enlazar_puerto(int descriptor, int puerto) {
	struct sockaddr_in server;
	int reu = 1;
	int true;
	// re-utilizo el puerto
	if (setsockopt(descriptor,SOL_SOCKET, SO_REUSEADDR, &reu,
			sizeof(true)) < 0) {
		perror("no es posible enlazar puerto: ");
		exit(EXIT_FAILURE);
	}
	//seteo la estructura del server
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(puerto);
	//enlazamos el puerto
	if (bind(descriptor, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("fallo en la funcion bind: ");
		exit(EXIT_FAILURE);
	}

}

void escuchar_clientes(int descriptor, int cantidad) {
	//cantidad de clientes que deseo escuchar
	if (listen(descriptor, cantidad) < 0){
		perror("no se puede transmitir la cola de escucha: ");
		exit(EXIT_FAILURE);
	}

}


void transferencia_datos(int client_fd){
int tamanio_enviar=1024;
    char buffer[10241], enviar[1024];
int num;
 while(1) {
        if ((num = recv(client_fd, buffer, 10240,0))== -1) {
            //fprintf(stderr,"Error in receiving message!!\n");
            perror("recv");
            exit(1);
        }
        else if (num == 0) {
            printf("Connection closed\n");
            exit(EXIT_FAILURE);
        }
    //  num = recv(client_fd, buffer, sizeof(buffer),0);
        buffer[num] = '\0';
        printf("Message received: %s\n", buffer);
        printf("%s","enviar mensaje al jugador: " );

        fgets(enviar,tamanio_enviar,stdin);

        send(client_fd,enviar,tamanio_enviar,0);
        }

}



void ciclo_de_conexiones(int socket_fd){
struct sockaddr_in cliente;
int client_fd;
socklen_t size;

    while(1) {
        size = sizeof(struct sockaddr_in);

        if ((client_fd = accept(socket_fd, (struct sockaddr *)&cliente, &size))==-1) {
            //fprintf(stderr,"Accept Failure\n");
            perror("accept");
            exit(1);
        }
        printf("Server got connection from client %s\n", inet_ntoa(cliente.sin_addr));
        //buffer = "Hello World!! I am networking!!\n";
        	transferencia_datos(client_fd);

        close(client_fd);
        close(socket_fd);
    }


}

void conectar(int socket_fd){
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port = htons(PORT);

	//client  connect to server on port

	if (connect(socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("no me puedo conectar");
		exit(1);
	}
    else
    {
    	printf("%s","enviar mensaje al servidor:" );
    	transferencia_datos_server(socket_fd);
    }


}
void transferencia_datos_server(int client_fd){
int tamanio_enviar=1024;
 char  enviar[1024];

		printf("%s", "enviar mensaje al servidor:  ");
		fgets(enviar,tamanio_enviar,stdin);
		send(client_fd,enviar,tamanio_enviar,0);
		transferencia_datos( client_fd);


}
