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
// y para ejecutar ./jugador  /home/jhon/cuadrago.jpg
 //ese path del archivo.jgp es relativo depende mucho del lugar donde uds lo guarden

void* jugar_con_servidor(void* param){
		vg_socket_fd = abrir_socket();
		conectar();
		return NULL;
}

int main(int argc, char *argv[])
{
	RADIO=40;
	vg_simbolo_jugador=2;
	vg_cuadrante.x1=0;
  	name=argv[1];
  	img = 0; 
 	img1 = 0; 
   	pthread_t  p_thread;
	

  if(argc<2){    printf("Usage: hello_world <image-file-name>\n\7");    exit(0);  }
  // load an image  
  //CvMat*
  img=cvLoadImage(argv[1],3);
   img1 = cvCloneImage(img); 
  if(!img){    printf("Could not load image file: %s\n",argv[1]);exit(0);  }

  	cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
  	cvMoveWindow(argv[1],100, 100);


	cvSetMouseCallback(name,mouseHandler,0);
	pthread_create(&p_thread, NULL, &jugar_con_servidor, NULL);
	cvShowImage(name, img);
			while(1)
	{
		// cvWaitKey me devuelve el ASCII de la tecla presionada
		// El valor pasado es el tiempo en milisegundos que esperarÃ¡ por una tecla
		// Si le paso 0 (cero) se bloquearÃ¡ hasta que se presione cualquier tecla
		

		key = cvWaitKey(20);
		if(key== ESC_KEY) 
			break;
	}
	cvDestroyAllWindows();
	cvReleaseImage(&img);
   return 0;
}