/*
 * conexiones.h
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

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
#define FAIL -1
#define MAX_ENVIAR_DATOS 1025
#define TRUE 1

//variables globales


//struct
 /*
devuelve un descriptor para poder comunicarse con el cliente;
 */


//prototipos.....
int abrir_socket();
void enlazar_puerto(int descriptor, int puerto) ;
void escuchar_clientes(int socket, int cantidad);
void transferencia_datos(int client_fd);
void ciclo_de_conexiones(int master_descriptor);
void conectar(int socket_fd);
void transferencia_datos_server(int client_fd);

#endif /* CONEXIONES_H_ */
