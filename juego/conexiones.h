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

 #include <cv.h>
#include <highgui.h>
#define PORT 3490
#define FAIL -1
#define MAX_ENVIAR_DATOS 1025
#define TRUE 1

//variables globales
int vg_simbolo_jugador;
IplImage* img1;
char* name;

typedef enum
{	
	HS=99,
	simbolo=2,
	coordenadas=3,
	estas_aceptado=4,
	elegir_simbolo=5,
	recibo_simbolo=6,
}protocolo;
//struct

 typedef struct 
{
	int tipo;
	int tamanio;

}cabeceraMensaje;
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
int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio);
int recibirPorSocket(int fdCliente, void * buffer, int tamanio);
void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje);
void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje);
#endif /* CONEXIONES_H_ */
