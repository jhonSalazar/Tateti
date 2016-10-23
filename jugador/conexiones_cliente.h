/*
 * conexiones_cliente.h
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 3490
#define MAXSIZE 1024
#ifndef CONEXIONES_CLIENTE_H_
#define CONEXIONES_CLIENTE_H_
int abrir_socket();
void enlazar_puerto(int descriptor, int puerto) ;
void escuchar_clientes(int socket, int cantidad);
void transferencia_datos(int client_fd);
void ciclo_de_conexiones(int master_descriptor);
void conectar(int socket_fd);
void transferencia_datos_server(int client_fd);




#endif /* CONEXIONES_CLIENTE_H_ */
