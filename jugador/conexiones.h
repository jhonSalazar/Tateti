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
 #include <pthread.h>
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
 #define RADIO 40
 #define POSICION_ERRONEA -1

//variables globales

//structuras
  typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
	int pos1;
	int pos2;
}Cuadrante;

typedef struct Nodo_registro{

	char jugadas[50];
	int simbolo;
	char nombre[20];

}t_nodo;
typedef struct 
{
	int tipo;
	int tamanio;

}cabeceraMensaje;
typedef enum {circulo=1,X=2,empate=3,gane=4,perdi=5,fuera_del_rango=6,simbolo_elegido=7,tu_turno=8,nombre=9}tipo_simbolo;




//variables globales nomen clatura vg de variable global
int vg_socket_fd;
int vg_empate;
char* vg_ip;
int vg_simbolo_jugador;
int vg_simbolo_retador;
IplImage* vg_img; 
int vg_turno;
IplImage* vg_img1; 
char* vg_name;
char vg_key;
Cuadrante vg_cuadrante;


 /**********************************************
MATRIZ DE ESTADOS 1 esta libre y 0 esta ocupado. por el momento todos estan libres;
******************************************************/
int matriz_estados[3][3];

//sirve para calcular si todos los cuadrantes consecutivos tiene el mismo simbolo
int matriz_consecutivos[3][3];

/***************************************
INICIALIZA LAS MATRICES
******************************************/
void cargar_matrices();

/*********************************************************
IMRPIME LA BARRA DE PORCENTAJE
***********************************************************/
void barra_procentaje();



int estafueraDelRango(Cuadrante cuadrante);




//prototipos.....
/*************************************************************
int abrir_socket();
DEVUELVO UN DESCRIPTOR PARA PODER COMUNICARME CON EL SERVIDOR
******************************/
int abrir_socket();


/************************************************************************************************
ESTA FUNCION ME DEVUELVE  1 SI EL CUADRANTE DONDE VOY A DIBUJAR ESTA VACION Y 0 SE YA ESTA OCUPADO
**************************************************************************************************/
int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante);




/*********************************************************************
ESTA FUNCIONES ME CALCULA SI EL SIMBOLO ESTA DIBUJADO CONSECUTIVAMETE,
DE ESA MANERA PUEDO SABER SI YA SE DIBUJARON 3 SIMBOLOS CONSECUTIVOS POR EJEMPLO XXX o OOO,
TANTO DIAGONAL, HORIZONAL Y VERTICAL.
********************************************/
int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo);




/********************************************
CON ESA FUNCION PUEDO CONECTARME AL SERVIDOR*
*********************************************/
void conectar();



/************************************************
ESA FUNCION ME PERMITE RECIBIR EL PAQUETE DE DATOS CORRESPONDIENTE
A LAS COORDENADAS DEL BIBUJO QUE VOY A RECIBIR DE PARTE DEL SERVIDOR POR EJEMPLO: UNA X CON LOS PUNTOS (X,Y);
******************************************************/
void transferencia_datos_server();



/************************************************
ESTAS FUNCION ME SRIVE PARA ENVIAR Y RECIBIR BYTES A TRAVES DE LOS SOCKET
******************************************************/

int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio);
int recibirPorSocket(int fdCliente, void * buffer, int tamanio);


/***********************************************************************************
ESTA FUNCION ME AYUDA A ABSTRAERME DEL ENVIO DE PAQUETE,						   *
 TANTO DE LAS COORDENADAS Y  EL TIPO DE SIMBOLO.								   *
 RE UTILIZA LA FUNCIONES EnviarPorSocket y recibirPorSocket. Utilizo la estrucutra *
 cabecera para enviarle el tipo y la cantidad de Bytes que necesita				   *
************************************************************************************/
void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje);
void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje);



/******************************************************************
ESTAN FUNCIONES ME PERMITEN DIBUJAR EN LA IMAGEN, EL SIMBOLO X o O*
*******************************************************************/
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
void dibujar_x(Cuadrante cuadrante,CvArr* img1);

/*********************************************************
ESTA FUNCIONE ME CALCULA LAS COORDENADAS CORRESPONDIENTES*
 PARA PODER DIBUJARLAS EN LA IMAGEN
**********************************************************/
Cuadrante calcular_cuadrante(int x, int y);


/*********************************************************************************
ESTA FUNCION DIBUJA EN EL CUADRANTE CORRESPONDIENTE EN FUNCION A LA QUE RECIBO DE*
LA FUNCION calcular_cuadran(int, int). HAGO USO DE ESTA FUNCION CUANDO HAGO CLICK* 
DONDE QUIERO DIBUJARLAS                                                          *
**********************************************************************************/
void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);

/********************************************************************
ES LA FUNCION, CONTIENE LA MISMA LOGICA, A DIFERENCIA QUE LA UTILIZO* 
EN EL INSTANTE EN  QUE RECIBO LOS PAQUETES                                 *     
*********************************************************************/
void dibujar_en_cuadrante_desde_servidor(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo);


/******************************************************************************
CON ESTA FUNCION CALCULO LA COORDENADAS  CUANDO POSICIONO EL MOUSE

******************************************************************************/
void mouseHandler(int event, int x, int y, int flags, void* param);
#endif /* CONEXIONES_H_ */
