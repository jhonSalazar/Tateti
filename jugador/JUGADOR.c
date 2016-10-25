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
#define PORT 3490
#define MAXSIZE 1024
#define ESC_KEY 27
 //compilar con estos parametros
 //gcc conexiones.c JUGADOR.c -o jugador $(pkg-config --cflags --libs opencv) -Wall -lpthread
// y para ejecutar ./jugador  /home/jhon/cuadrago.jpg
 //ese path del archivo.jgp es relativo depende mucho del lugar donde uds lo guarden
typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
}Cuadrante;
int RADIO=40;
int socket_fd;
typedef enum {circulo=1,X=2}tipo_simbolo;
int tipoSimbolo=2;
 IplImage* img = 0; 
 IplImage* img1 = 0; 
 char* name;
 int c=0;
 
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
void dibujar_x(Cuadrante cuadrante,CvArr* img1);
Cuadrante calcular_cuadrante(int x, int y);
void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1);
void mouseHandler(int event, int x, int y, int flags, void* param);
void* conectarse_servidor(void* nada);
int main(int argc, char *argv[])
{
	char key;
  	name=argv[1];
  	pthread_t  p_thread;



    socket_fd =abrir_socket();
    
	
  
  // Defino el punto (pixel) inicial del rectangulo (arriba a la izquierda)
	
 // uchar *data;
//  int i,j,k;

	


  if(argc<2){    printf("Usage: hello_world <image-file-name>\n\7");    exit(0);  }
  // load an image  
  //CvMat*
  img=cvLoadImage(argv[1],3);
   img1 = cvCloneImage(img); 
  if(!img){    printf("Could not load image file: %s\n",argv[1]);    exit(0);  }
  // get the image data
  //height    = img->height;
  //width     = img->width;
  //step      = img->widthStep;
  //channels  = img->nChannels;
  //data      = (uchar *)img->imageData;
 // printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
  //printf("%s\n","elige el tipo de simbolo, O = 1,  X=2 \n");
  //scanf("%d",&tipoSimbolo);

  // create a window
 
  
  cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
  cvMoveWindow(argv[1],100, 100);
  // Dibujo rectangulo Verde, Grosor 3, que compienza en el pixel pt1 y termina en pt2.
	//cvRectangle( img, pt1 , pt2 , CV_RGB(0,255,0), 3, 8, 0 );
	//cvRectangle( img, pt3 , pt4 , CV_RGB(25,0,0), 3, 8, 0 );
	//cvRectangle( img, pt5 , pt6 , CV_RGB(25,80,50), 3, 8, 0 );
  // invert the image
  
 	 cvSetMouseCallback(argv[1],mouseHandler,0);
	
	cvShowImage(argv[1], img);
	pthread_create(&p_thread, NULL,&conectarse_servidor, NULL);
   
	// Lazo infinito. Sale cuando presiono la tecla ESCAPE
	
	//pthread_join(p_thread,NULL);
	while(1)
	{
		// cvWaitKey me devuelve el ASCII de la tecla presionada
		// El valor pasado es el tiempo en milisegundos que esperarÃ¡ por una tecla
		// Si le paso 0 (cero) se bloquearÃ¡ hasta que se presione cualquier tecla
		key = cvWaitKey(20);
		if(key== ESC_KEY) 
			break;
	}

	
	printf("cantidad de dibujos es c:%d\n",c );
  
	cvDestroyAllWindows();
	cvReleaseImage(&img);
     
   
}

Cuadrante calcular_cuadrante(int x, int y){

Cuadrante cuadrante;
//1er cuadrante
	if((x>=18 && x<=107)&&(y>=16 && y <=105)){

		cuadrante.x1=18;
		cuadrante.x2=107;
		cuadrante.y1=16;
		cuadrante.y2=105;
	}



//2do cuadrante
	if((x>=107 && x<=197) &&(y>=16 && y<= 105)){

		cuadrante.x1=107;
		cuadrante.x2=197;
		cuadrante.y1=16;
		cuadrante.y2=105;
	}

		
		//tercer cuadrante
	if((x>=197 && x<=285) &&(y>=16 && y<= 105)){
		cuadrante.x1=197;
		cuadrante.x2=285;
		cuadrante.y1=16;
		cuadrante.y2=105;
	}

		//cuarto cuadrante
	if((x>=18 && x<=107) &&(y>=105 && y<= 194)){
		cuadrante.x1=18;
		cuadrante.x2=107;
		cuadrante.y1=105;
		cuadrante.y2=194;
	}
	

		//5to cuadrante
		if((x>=107 && x<=200) &&(y>=105 && y<=194)){
			cuadrante.x1=107;
			cuadrante.x2=200;
			cuadrante.y1=105;
			cuadrante.y2=194;
		}

		//6to cuadrante

		if((x>=200 && x<=285) &&(y>=105 && y<=194)){
			cuadrante.x1=200;
			cuadrante.x2=285;
			cuadrante.y1=105;
			cuadrante.y2=194;
		}

		//7to cuadrante

		if((x>=18 && x<=107) &&(y>=194 && y<=285)){
			cuadrante.x1=18;
			cuadrante.x2=107;
			cuadrante.y1=194;
			cuadrante.y2=285;
		}

		//8to cuadrante

		if((x>=107 && x<=200) &&(y>=194 && y<=285)){
			cuadrante.x1=107;
			cuadrante.x2=200;
			cuadrante.y1=194;
			cuadrante.y2=285;
		}

		//9to cuadrante

		if((x>=200 && x<=285) &&(y>=194 && y<=285)){
			cuadrante.x1=200;
			cuadrante.x2=285;
			cuadrante.y1=194;
			cuadrante.y2=285;
		}



		return cuadrante;
}

void dibujar_O(Cuadrante cuadrante,CvArr* img1){

	cvCircle(img1, cvPoint( (cuadrante.x1 + cuadrante.x2)/2,(cuadrante.y1 + cuadrante.y2)/2), RADIO	, CV_RGB(0,0,0), 2, CV_AA, 0);
	cvShowImage(name, img1);

}

 void dibujar_x(Cuadrante cuadrante,CvArr* img1){
 							//x1,y1										//x2,y2
		cvLine(img1, cvPoint(cuadrante.x1,cuadrante.y1),cvPoint(cuadrante.x2,cuadrante.y2), CV_RGB(0,0,0), 2, CV_AA , 0);
							//x1,y2										//x2,y1
		cvLine(img1, cvPoint(cuadrante.x1,cuadrante.y2),cvPoint(cuadrante.x2,cuadrante.y1), CV_RGB(0,0,0), 2, CV_AA , 0);
		cvShowImage(name, img1);


 }

 void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1){

 
	//printf("MOUSE(): CLICK IZQUIERDO ...\n");
	//printf("FILA (y) = %d    COL (x) = %d \n",y,x);
	  //img1 = cvCloneImage(img); 
	//cvCircle(img1, cvPoint( (pt1.x + pt2.x)/2,(pt1.y + pt2.y)/2), 40, CV_RGB(0,0,0), -1, CV_AA, 0);
	//int centro=(pt1.x + pt2.x)/2;
		switch(tipoSimbolo)
		{

			case circulo:
			dibujar_O(cuadrante ,img1);
			break;

			case X:
			dibujar_x(cuadrante,img1);
			break;

			default:
				printf("%s\n","bla bla bla bla bla bla\n");
			return;

		}


}
void mouseHandler(int event, int x, int y, int flags, void* param)
{	

	if (event != CV_EVENT_LBUTTONDOWN)
	{	
		//printf("No se peude dibujar de nuevo...\n");
		return;
	}
	Cuadrante cuadrante=calcular_cuadrante(x,y);
	dibujar_en_cuadrante(cuadrante,img1);

	
}

void* conectarse_servidor(void* nada){


	conectar(socket_fd);
	return NULL;
}