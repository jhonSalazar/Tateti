/*
 ============================================================================
 Name        : JUGADOR.c
 Author      : JHON SALAZAR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
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
#include <cv.h>
#include <highgui.h>
#include <pthread.h>
#include "conexiones.h"

 //compilar con estos parametros
 //gcc conexiones.c JUGADOR.c -o jugador $(pkg-config --cflags --libs opencv) -Wall -lpthread
// y para ejecutar ./jugador  /home/jhon/cuadrago.jpg 127.0.0.1
 //ese path del archivo.jgp es relativo depende mucho del lugar donde uds lo guarden

void* jugar_con_servidor(void* param){
		vg_socket_fd = abrir_socket();
		conectar();
		return NULL;
}

int main(int argc, char *argv[])
{
	int i,j;
	vg_simbolo_jugador=2;
	vg_simbolo_retador=0;
  	vg_name=argv[1];
  	vg_ip=argv[2];
  	vg_img = 0; 
 	vg_img1 = 0; 
  	vg_name=argv[1];
  	pthread_t  p_thread;




  	for(i=0;i<3;i++){
  		for(j=0;j<3;j++){
  			matriz_estados[i][j]=1;
  			matriz_consecutivos[i][j]=8;
  		}
  	}
	
	

  if(argc<2){    printf("Ingresa <./ejecutable> <image-file-name> <IP-SERVER>\n\7");    exit(0);  }

  	vg_img=cvLoadImage(argv[1],3);
    vg_img1 = cvCloneImage(vg_img); 

  if(!vg_img){    printf("La imagen no se ha cargado: %s\n",argv[1]);exit(0);  }

  	cvNamedWindow(vg_name, CV_WINDOW_AUTOSIZE);
  	cvMoveWindow(vg_name,100, 100);


	cvSetMouseCallback(vg_name,mouseHandler,0);
	//levanto un hilo para las conexiones y pueda recibir los paquetes de coordenadas de los dibujos.
	pthread_create(&p_thread, NULL, &jugar_con_servidor, NULL);
	cvShowImage(vg_name, vg_img);
			while(1)
	{
		vg_key = cvWaitKey(20);
		if(vg_key== ESC_KEY) 
			break;
	}
	cvDestroyAllWindows();
	cvReleaseImage(&vg_img);
   return 0;
}