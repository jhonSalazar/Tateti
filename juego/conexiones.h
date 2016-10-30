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
//varibales para definir coodenadas del los cuadrantes

# define C1_X1 18
#define C1_X2 107
#define C1_Y1 16
#define C1_Y2 105

#define C2_X1 107
#define C2_X2 197
#define C2_Y1 16
#define C2_Y2 105

 #define C3_X1 197
	#define C3_X2 285
	#define C3_Y1 16
	#define C3_Y2 105

	 #define C4_X1 18
	#define C4_X2 107
	#define C4_Y1 105
	#define C4_Y2 194

 	#define C5_X1 107
	#define C5_X2 200
	#define C5_Y1 105
	#define C5_Y2 194

 	#define C6_X1 200
	#define C6_X2 285
	#define C6_Y1 105
	#define C6_Y2 194

 	#define C7_X1 18
		#define C7_X2 107
		#define C7_Y1 194
		#define C7_Y2 285

 		#define C8_X1 107
		#define C8_X2 200
		#define C8_Y1 194
		#define C8_Y2 285

 		#define C9_X1 200
		#define C9_X2 285
		#define C9_Y1 194
		#define C9_Y2 285
 //varibales para definir coodenadas del los cuadrante



/**********************************************
MATRIZ DE ESTADOS 1 esta libre y 0 esta ocupado. por el momento todos estan libres;
******************************************************/
int matriz_estados[3][3];
int matriz_consecutivos[3][3];


 #include <cv.h>
#include <highgui.h>
#define PORT 3490
#define FAIL -1
#define MAX_ENVIAR_DATOS 1025
#define TRUE 1
 #define RADIO 40

#define ESC_KEY 27

//variables globales

//struct

typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
	int pos1;
	int pos2;
	int status;
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
int vg_simbolo_retador;
IplImage* img1;
char* name;
typedef enum {circulo=1,X=2}tipo_simbolo;
 IplImage* img; 
 char key;
//prototipos.....
 int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo);
 int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante);
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
 void dibujar_x(Cuadrante cuadrante,CvArr* img1);
 Cuadrante calcular_cuadrante(int x, int y);
 void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipo_simbolo);
 void dibujar_en_cuadrante_desde_cliente(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);
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
