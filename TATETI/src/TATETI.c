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
 //gcc conexiones.c TATETI.C -o juego $(pkg-config --cflags --libs opencv) -Wall -lpthread
// y para ejecutar ./jugador  /home/jhon/cuadrago.jpg
 //ese path del archivo.juego  es relativo depende mucho del lugar donde uds lo guarden
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

#include <cv.h>
#include <highgui.h>
//imagen 311 x 307
#define PORT 3490
#define FAIL -1
#define MAX_ENVIAR_DATOS 1025
#define TRUE 1
#define ESC_KEY 27

typedef struct ccc{
	int x1;
	int x2;
	int y1;
	int y2;
}Cuadrante;
int RADIO=40;

typedef enum {circulo=1,X=2}tipo_simbolo;
int tipoSimbolo;
 IplImage* img = 0; 
 IplImage* img1 = 0; 
 char* name;
 int c=0;
 
void dibujar_O(Cuadrante cuadrante,CvArr* img1);
void dibujar_x(Cuadrante cuadrante,CvArr* img1);
Cuadrante calcular_cuadrante(int x, int y);
void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1);
void mouseHandler(int event, int x, int y, int flags, void* param);
int abrir_socket();
void enlazar_puerto(int descriptor, int puerto) ;
void escuchar_clientes(int socket, int cantidad);
void transferencia_datos(int client_fd);
void ciclo_de_conexiones(int master_descriptor);
void* escuchar(void* nada);
int main(int argc, char *argv[])
{
	char key;
  	name=argv[1];
  	pthread_t  p_thread;

	
  
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
  printf("%s\n","elige el tipo de simbolo, O = 1,  X=2 \n");
  scanf("%d",&tipoSimbolo);

  // create a window
  cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
  cvMoveWindow(argv[1],100, 100);
  // Dibujo rectangulo Verde, Grosor 3, que compienza en el pixel pt1 y termina en pt2.
	//cvRectangle( img, pt1 , pt2 , CV_RGB(0,255,0), 3, 8, 0 );
	//cvRectangle( img, pt3 , pt4 , CV_RGB(25,0,0), 3, 8, 0 );
	//cvRectangle( img, pt5 , pt6 , CV_RGB(25,80,50), 3, 8, 0 );
  // invert the image
  
 	 cvSetMouseCallback(argv[1],mouseHandler,0);
	pthread_create(&p_thread, NULL, &escuchar, NULL);
	cvShowImage(argv[1], img);
	
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
  	return 0;
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
int abrir_socket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		perror("error al abrir el descriptor :");

	return sockfd;

}


void enlazar_puerto(int descriptor, int puerto) {
	struct sockaddr_in server;
	int reu = 1;
	int true;
	// re-utilizo el puerto
	if (setsockopt(descriptor,SOL_SOCKET, SO_REUSEADDR, &reu,
			sizeof(true)) < 0) {
		perror("no es posible enlazar puerto: ");
		exit(EXIT_FAILURE);
	}
	//seteo la estructura del server
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(puerto);
	//enlazamos el puerto
	if (bind(descriptor, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("fallo en la funcion bind: ");
		exit(EXIT_FAILURE);
	}

}

void escuchar_clientes(int descriptor, int cantidad) {
	//cantidad de clientes que deseo escuchar
	if (listen(descriptor, cantidad) < 0){
		perror("no se puede transmitir la cola de escucha: ");
		exit(EXIT_FAILURE);
	}

}


void transferencia_datos(int client_fd){
int tamanio_enviar=1024;
    char buffer[10241], enviar[1024];
int num;
 while(1) {
        if ((num = recv(client_fd, buffer, 10240,0))== -1) {
            //fprintf(stderr,"Error in receiving message!!\n");
            perror("recv");
            exit(1);
        }   
        else if (num == 0) {
            printf("Connection closed\n");
            exit(EXIT_FAILURE);
        }
    //  num = recv(client_fd, buffer, sizeof(buffer),0);
        buffer[num] = '\0';
        printf("Message received: %s\n", buffer);

        printf("%s","enviar mensaje al jugador: " );

        fgets(enviar,tamanio_enviar,stdin);

        send(client_fd,enviar,tamanio_enviar,0);
        }

}



void ciclo_de_conexiones(int socket_fd){
struct sockaddr_in cliente;
int client_fd;
socklen_t size;
	
    while(1) {
        size = sizeof(struct sockaddr_in);  

        if ((client_fd = accept(socket_fd, (struct sockaddr *)&cliente, &size))==-1) {
            //fprintf(stderr,"Accept Failure\n");
            perror("accept");
            exit(1);
        }
        printf("servidor conectado con %s\n", inet_ntoa(cliente.sin_addr));
        //buffer = "Hello World!! I am networking!!\n";
        	transferencia_datos(client_fd);

        close(client_fd);   
        close(socket_fd);   
    }

	
}



void* escuchar(void* nada){

	int socket_fd;

    socket_fd =abrir_socket();

    enlazar_puerto(socket_fd, PORT);
   printf("%s\n","escuchar a clientes" );
    escuchar_clientes(socket_fd,5);
    ciclo_de_conexiones(socket_fd);


	return NULL;
}

//8 noviembre segundo parcial y la entrega.
//22 noviembre primer recuperatorio.
//29 noviembre segundo recuperatorio.