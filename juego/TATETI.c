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

#include "conexiones.h"

#include <cv.h>
#include <highgui.h>
#include <pthread.h>

//#include <cv.h>
//#include <highgui.h>
//imagen 311 x 307
#define PORT 3490
#define FAIL -1
#define MAX_ENVIAR_DATOS 1025
#define TRUE 1
#define ESC_KEY 27

void* jugar_con_cliente(void* param){

			 vg_socket_fd =abrir_socket();
    	 enlazar_puerto(vg_socket_fd, PORT);
   		 
   		 escuchar_clientes(vg_socket_fd,5);
    	 ciclo_de_conexiones(vg_socket_fd);
return NULL;
}  
int main(int argc, char *argv[])
{
	int i,j;
	vg_simbolo_jugador=1;
  vg_simbolo_retador=2;
  vg_empate=0;
  vg_img =0; 
  vg_img1=0;
  vg_name=argv[1];
  vg_turno=0;

	//incializo mas matrices .
  
  	pthread_t  p_thread;
  	for(i=0;i<3;i++){
  		for(j=0;j<3;j++){
  			matriz_estados[i][j]=1;
        matriz_consecutivos[i][j]=5;

  		}
  	}
  if(argc<2){printf("Usage: hello_world <archivo-imagen>\n\7");    exit(0);  }

    vg_img=cvLoadImage(argv[1],3);
    vg_img1 = cvCloneImage(vg_img); 

  if(!vg_img){printf("Could not load image file: %s\n",argv[1]);    exit(0);  }
//printf("mi tipo de imagen es :%d\n",vg_simbolo_jugador);
  	
  vg_logger= crear_logger("LOG_DE_MOVIMIENTOS");
  vg_loggerv2= crear_logger("LOG_DE_MOVIMIENTOSV2");
  vg_lista_jugadas= crear_lista();
  //free(vg_lista);
  //fclose(vg_loggerv2);
  cvNamedWindow(vg_name, CV_WINDOW_AUTOSIZE);
  cvMoveWindow(vg_name,100, 100);

  	cvSetMouseCallback(vg_name,mouseHandler,0);
 	
	pthread_create(&p_thread, NULL, &jugar_con_cliente, NULL);
  	
  cvShowImage(vg_name, vg_img);
  	while(1){

		vg_key = cvWaitKey(20);
		if(vg_key== ESC_KEY) 
			break;
	}
 		
	cvDestroyAllWindows();
	cvReleaseImage(&vg_img);
 	

  
	
  	return 0;
}





//8 noviembre segundo parcial y la entrega.
//22 noviembre primer recuperatorio.
//29 noviembre segundo recuperatorio.