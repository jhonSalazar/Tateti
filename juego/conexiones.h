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
 #define RADIO 40

#define ESC_KEY 27

//variables globales



typedef enum
{	
	HS=99,
	simbolo=2,
	coordenadas=3,
	estas_aceptado=4,
	elegir_simbolo=5,
	recibo_simbolo=6,
	dibujar=7
}protocolo;
//struct

typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
}Cuadrante;

 typedef struct 
{
	int tipo;
	int tamanio;

}cabeceraMensaje;
 /*
devuelve un descriptor para poder comunicarse con el cliente;
 */
int vg_socket_fd;
int vg_cliente_fd;
Cuadrante vg_cuadrante;
int vg_simbolo_jugador;
IplImage* img1;
char* name;
typedef enum {circulo=1,X=2}tipo_simbolo;
 IplImage* img ; 
 char key;
//prototipos.....
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
 void dibujar_x(Cuadrante cuadrante,CvArr* img1);
 Cuadrante calcular_cuadrante(int x, int y);
 void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipo_simbolo);
int abrir_socket();
void enlazar_puerto(int descriptor, int puerto) ;
void escuchar_clientes(int socket, int cantidad);
void mouseHandler(int event, int x, int y, int flags, void* param);
void transferencia_datos();
void ciclo_de_conexiones(int master_descriptor);
void conectar(int socket_fd);
void transferencia_datos_server(int client_fd);
int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio);
int recibirPorSocket(int fdCliente, void * buffer, int tamanio);
void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje);
void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje);
#endif /* CONEXIONES_H_ */
