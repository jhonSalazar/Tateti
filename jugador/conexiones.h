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
#include <errno.h>
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
#define MAXSIZE 1024
#define ESC_KEY 27

//variables globales

//

 /**********************************************
MATRIZ DE ESTADOS 1 esta libre y 0 esta ocupado. por el momento todos estan libres;
******************************************************/
int matriz_estados[3][3];
int matriz_consecutivos[3][3];

int RADIO;
int vg_socket_fd;
typedef enum {circulo=1,X=2}tipo_simbolo;
int vg_simbolo_jugador;
int vg_simbolo_retador;
 IplImage* img; 
 IplImage* img1; 
 int socket_fd;
 char* name;

char key;
 typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
	int pos1;
	int pos2;
}Cuadrante;

Cuadrante vg_cuadrante;


//estructuras
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
int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante);
int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo);
void enlazar_puerto(int descriptor, int puerto) ;
void escuchar_clientes(int socket, int cantidad);
void transferencia_datos(int client_fd);
void ciclo_de_conexiones(int master_descriptor);
void conectar();
void transferencia_datos_server();
int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio);
int recibirPorSocket(int fdCliente, void * buffer, int tamanio);
void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje);
void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje);
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
void dibujar_x(Cuadrante cuadrante,CvArr* img1);
Cuadrante calcular_cuadrante(int x, int y);
void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);
void dibujar_en_cuadrante_desde_servidor(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);
void mouseHandler(int event, int x, int y, int flags, void* param);
#endif /* CONEXIONES_H_ */
