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
#include <math.h>
#include <pthread.h>
#include <cv.h>
#include <highgui.h>
#include <time.h>

typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
	int pos1;
	int pos2;
	int status;
}Cuadrante;



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

#define POSICION_ERRONEA -1

 /**********************************************
MATRIZ DE ESTADOS 1 esta libre y 0 esta ocupado. por el momento todos estan libres;
******************************************************/
int matriz_estados[3][3];

//sirve para calcular si todos los cuadrantes consecutivos tiene el mismo simbolo
int matriz_consecutivos[3][3];



#define PORT 3490

#define MAX_ENVIAR_DATOS 1025
#define TRUE 1
 #define RADIO 40

#define ESC_KEY 27


//struct



 /*
devuelve un descriptor para poder comunicarse con el cliente;
 */
//Variables globales
int vg_socket_fd;

int vg_cliente_fd;
char vg_nombre_retador[1024];
FILE* vg_logger;
FILE* vg_loggerv2;
Cuadrante vg_cuadrante;
int vg_simbolo_jugador;
int vg_simbolo_retador;
int vg_turno;
IplImage* vg_img1;
IplImage* vg_img; 
int vg_empate;
char* vg_name;
 char vg_key;
typedef enum {circulo=1,X=2,empate=3,perdi=4,gane=5,fuera_del_rango=6,simbolo_elegido=7,tu_turno=8,nombre_retador=9}tipo_simbolo;
 



#define FAIL -1


 typedef struct 
{
	int tipo;
	int tamanio;

}cabeceraMensaje;

typedef struct jugada
{
	char* name;
	char hora_jugada[26];
	Cuadrante cuadrante;
	
}t_jugada;



void calcular_hora(char*);





/**********************************************************************************
ESTA LISTA VA A GUARDAR EN CADA NODO, LAS JUGADAS REALIZADAS POR LOS CONTRINCANTES*
***********************************************************************************/

//prototipos.....
/*************************************************************
Int abrir_socket();                                          *
DEVUELVO UN DESCRIPTOR PARA PODER COMUNICARME CON EL SERVIDOR*
**************************************************************/
int abrir_socket();


/******************************************************************************************
int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo);            *
ESTA FUNCIONES ME CALCULA SI EL SIMBOLO ESTA DIBUJADO CONSECUTIVAMETE,                    *
DE ESA MANERA PUEDO SABER SI YA SE DIBUJARON 3 SIMBOLOS CONSECUTIVOS POR EJEMPLO XXX o OOO*
TANTO DIAGONAL, HORIZONAL Y VERTICAL.                                                     *
*******************************************************************************************/ 
int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo);



int estafueraDelRango(Cuadrante cuadrante);





/*********************************************************
Cuadrante calcular_cuadrante(int x, int y);				 *
ESTA FUNCIONE ME CALCULA LAS COORDENADAS CORRESPONDIENTES*
 PARA PODER DIBUJARLAS EN LA IMAGEN 					 *
**********************************************************/
Cuadrante calcular_cuadrante(int x, int y);



/*************************************************************************
int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio);	**
int recibirPorSocket(int fdCliente, void * buffer, int tamanio);		**
																		**
ESTAS FUNCION ME SRIVE PARA ENVIAR Y RECIBIR BYTES A TRAVES DE LOS SOCKET*
**************************************************************************/

int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio);
int recibirPorSocket(int fdCliente, void * buffer, int tamanio);


/***************************************************************************************
void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje);*
void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje);		   *
																					   *
ESTA FUNCION ME AYUDA A ABSTRAERME DEL ENVIO DE PAQUETE,							   *
 TANTO DE LAS COORDENADAS Y  EL TIPO DE SIMBOLO.									   *
 RE UTILIZA LA FUNCIONES EnviarPorSocket y recibirPorSocket, utilizo la estrucutra 
 cabecera para enviarle el tipo y la cantidad de Bytes que necesita						   *
****************************************************************************************/
void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje);
void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje);





/********************************************************************************************************************
int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante);*
ESTA FUNCION ME DEVUELVE  1 SI EL CUADRANTE DONDE VOY A DIBUJAR ESTA VACION Y 0 SE YA ESTA OCUPADO                  *   
*********************************************************************************************************************/
int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante);





/*******************************************************************
void dibujar_O(Cuadrante cuadrante,CvArr* img1);				   *
void dibujar_x(Cuadrante cuadrante,CvArr* img1);				   *
ESTAN FUNCIONES ME PERMITEN DIBUJAR EN LA IMAGEN, EL SIMBOLO X o O *
********************************************************************/
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
void dibujar_x(Cuadrante cuadrante,CvArr* img1);





/*********************************************************************************
void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);		 *
ESTA FUNCION DIBUJA EN EL CUADRANTE CORRESPONDIENTE EN FUNCION A LA QUE RECIBO DE*
LA FUNCION calcular_cuadran(int, int). HAGO USO DE ESTA FUNCION CUANDO HAGO CLICK* 
DONDE QUIERO DIBUJARLAS                                                          *
**********************************************************************************/
void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);



/*****************************************************************************************
void dibujar_en_cuadrante_desde_cliente(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);*
ES LA FUNCION, CONTIENE LA MISMA LOGICA, A DIFERENCIA QUE LA UTILIZO* 					 *
EN EL MINSTANTE QUE RECIBO LOS PAQUETES                                 *     			 *
******************************************************************************************/
void dibujar_en_cuadrante_desde_cliente(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);




/****************************************************
void enlazar_puerto(int descriptor, int puerto);	*
ENLAZA EL PUERTO DONDE VOY A ESCUCHAR LAS CONEXIONES*
*****************************************************/
void enlazar_puerto(int descriptor, int puerto);


/************************************************
void escuchar_clientes(int socket, int cantidad)*
												*
CON ESTA FUNCIONES VOY A CONFIGURAR LAS CANTIDAD* 
DE CLIENTES QUE PUEDO TENER EN ESPERA.          * 
*************************************************/
void escuchar_clientes(int socket, int cantidad);


/*******************************************************************
void transferencia_datos();										   *
ESA FUNCION ME PERMITE RECIBIR EL PAQUETE DE DATOS CORRESPONDIENTE *
A LAS COORDENADAS DEL BIBUJO QUE VOY A RECIBIR DE PARTE DEL CLIENTE*
POR EJEMPLO: UNA X CON LOS PUNTOS (X,Y);                           *
********************************************************************/
void transferencia_datos();



/************************************************
void ciclo_de_conexiones(int master_descriptor);*
CON ESTA FUNCION ACEPTO LAS conexiones 			*
*************************************************/
void ciclo_de_conexiones(int master_descriptor);





/*******************************************************************
void mouseHandler(int event, int x, int y, int flags, void* param);*
CON ESTA FUNCION CALCULO LA COORDENADAS  CUANDO POSICIONO EL MOUSE *
																   *
********************************************************************/
void mouseHandler(int event, int x, int y, int flags, void* param);

FILE* crear_logger(const char* nombre);



void guardar_movimientos(FILE* logger,Cuadrante, char* name,char* horario);

typedef  struct nodo{
    void *datos;
    struct nodo* siguiente;
  }t_nodo;
  

typedef struct {
    t_nodo *cabeza;
    int contador;
  } t_list;
t_list* vg_lista_jugadas;

void linkear_nodos(t_nodo* anterior, t_nodo* siguiente);
t_nodo* crear_nodo(void* datos);
 t_nodo* obtener_nodo(t_list* lista, int indice) ;
 t_list* crear_lista();
 int agregar_datos(t_list *lista, void *datos);
 void* obtener_datos(t_list *lista, int indice) ;
 void *eliminar_nodo(t_list *lista, int indice);
 int tamanio_lista(t_list *lista) ;
 void copiar_logger(t_list* lista, FILE* logger);



#endif /* CONEXIONES_H_ */
