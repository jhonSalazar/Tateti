/*
 ============================================================================
 Name        : TATETI.c
 Author      : JHON SALAZAR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//compilar con estos parametros
 //gcc -o juego conexiones.c TATETI.c $(pkg-config --cflags --libs opencv) -Wall -lpthread
// y para ejecutar ./juego  /home/jhon/cuadrago.jpg
 //ese path del la imagen es relativo, depende mucho del lugar donde uds lo guarden
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
#include <math.h>
#include <pthread.h>
#include "conexiones.h"

#include <cv.h>
#include <highgui.h>
//imagen 311 x 307
#define PORT 3490
#define FAIL -1
#define MAX_ENVIAR_DATOS 1025
#define TRUE 1
#define ESC_KEY 27

void* jugar_con_cliente(void* param){

			vg_socket_fd =abrir_socket();
    	 enlazar_puerto(vg_socket_fd, PORT);
   		 printf("%s\n","escuchar a clientes" );
   		 escuchar_clientes(vg_socket_fd,5);
    	 ciclo_de_conexiones(vg_socket_fd);
return NULL;
}


int main(int argc, char *argv[])
{
	int i,j;
	vg_simbolo_jugador=1;
	
  	name=argv[1];
  	pthread_t  p_thread;
  	for(i=0;i<3;i++){
  		for(j=0;j<3;j++){
  			matriz_estados[i][j]=1;
        matriz_consecutivos[i][j]=5;

  		}
  	}
  if(argc<2){    printf("Usage: hello_world <image-file-name>\n\7");    exit(0);  }

  img=cvLoadImage(argv[1],3);
   img1 = cvCloneImage(img); 

  if(!img){    printf("Could not load image file: %s\n",argv[1]);    exit(0);  }

  	
  
  cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
  cvMoveWindow(argv[1],100, 100);

  	cvSetMouseCallback(name,mouseHandler,0);
 	
	pthread_create(&p_thread, NULL, &jugar_con_cliente, NULL);
  	
  cvShowImage(name, img);
  	while(1){

		key = cvWaitKey(20);
		if(key== ESC_KEY) 
			break;
	}
 		
	cvDestroyAllWindows();
	cvReleaseImage(&img);
 	

  
	
  	return 0;
}





//8 noviembre segundo parcial y la entrega.
//22 noviembre primer recuperatorio.
//29 noviembre segundo recuperatorio.