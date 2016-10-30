/*
 * conexiones.c
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */



#include "conexiones.h"

#include <string.h>


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

 void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo){

 
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


void mouseHandler(int event, int x, int y, int flags, void* param)
{	
	void* buffer;
	int tamanioMensaje;
	if (event != CV_EVENT_LBUTTONDOWN)
	{	

	}
	if(event == CV_EVENT_LBUTTONDOWN ){
	vg_cuadrante=calcular_cuadrante(x,y);
 	dibujar_en_cuadrante(vg_cuadrante,img1,vg_simbolo_jugador);
 	tamanioMensaje=sizeof(Cuadrante);
	buffer=malloc(tamanioMensaje);
	memcpy(buffer,&vg_cuadrante,tamanioMensaje);
	enviarPaquete(vg_cliente_fd,vg_simbolo_jugador,buffer,tamanioMensaje);
	free(buffer);
	printf("se cargaron las corrdenadas x1:%d x2:%d \n",vg_cuadrante.x1,vg_cuadrante.x2);
 
 	
 	
	}

	
}




void transferencia_datos(){
void *buffer;
int tipoSimbolo,tamanioMensaje;
//int num;

	
		while(1)
		{

			buffer=recibirPaquete(vg_cliente_fd,&tipoSimbolo,&tamanioMensaje);
			if(buffer !=NULL)
			{
				memcpy(&vg_cuadrante,buffer,tamanioMensaje);
				dibujar_en_cuadrante(vg_cuadrante,img1,tipoSimbolo);
				free(buffer);

			}else{
				//printf("%s\n","no llegaron las coordenadas correspondientes" );
				return;
			}


		}

	

}


void ciclo_de_conexiones(int socket_fd){
struct sockaddr_in cliente;
//int client_fd;
socklen_t size;

    while(1) {
        size = sizeof(struct sockaddr_in);

        if ((vg_cliente_fd = accept(socket_fd, (struct sockaddr *)&cliente, &size))==-1) {
            //fprintf(stderr,"Accept Failure\n");
            perror("accept");
            exit(1);
        }
        printf("Server got connection from client %s\n", inet_ntoa(cliente.sin_addr));
        //buffer = "Hello World!! I am networking!!\n";
        	transferencia_datos();

        close(vg_cliente_fd);
    }


}

void conectar(int socket_fd){
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port = htons(PORT);

	//client  connect to server on port

	if (connect(socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("no me puedo conectar");
		exit(1);
	}
    else
    {
    	
    	transferencia_datos_server(socket_fd);
    }


}
void transferencia_datos_server(int client_fd){
int tamanio_enviar=1024;
 char  enviar[1024];

		printf("%s", "enviar mensaje al servidor:  ");
		fgets(enviar,tamanio_enviar,stdin);
		send(client_fd,enviar,tamanio_enviar,0);
		transferencia_datos( client_fd);


}

int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio) {
	int bytes_enviados;
	int total = 0;

	while (total < tamanio) {
		bytes_enviados = send(fdCliente, mensaje + total, tamanio, 0);
		if (bytes_enviados == FAIL) {
			break;
		}
		total += bytes_enviados;
		tamanio -= bytes_enviados;
	}

	if (bytes_enviados == FAIL) perror("[ERROR] Funcion send");
	
	return bytes_enviados;
}

int recibirPorSocket(int fdCliente, void * buffer, int tamanio) {
	int total = 0;
	int bytesRecibidos;

	while (total < tamanio) {
		bytesRecibidos = recv(fdCliente, buffer + total, tamanio, 0);
		if (bytesRecibidos == FAIL) {
			// Error
			perror("[ERROR] Funcion recv");
			break;
		}
		if (bytesRecibidos == 0) {
			// Desconexion
			break;
		}
		total += bytesRecibidos;
		tamanio -= bytesRecibidos;
	}
	return bytesRecibidos;
}	// retorna 

void enviarPaquete(int fdCliente, int tipoMensaje, void * mensaje, int tamanioMensaje){
	cabeceraMensaje nuevoMensaje;
	nuevoMensaje.tipo = tipoMensaje;
	nuevoMensaje.tamanio = tamanioMensaje;
	enviarPorSocket(fdCliente, (void *) &nuevoMensaje, sizeof(cabeceraMensaje));
	enviarPorSocket(fdCliente, mensaje, nuevoMensaje.tamanio);
}

void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje){
	cabeceraMensaje nuevoMensaje;
	int recibido = recibirPorSocket(fdCliente, &nuevoMensaje, sizeof(cabeceraMensaje));
	if (recibido > 0) {
		printf("tamanio de mensaje:%d\n", nuevoMensaje.tamanio);
		printf("el tipo del mensaje %d\n",nuevoMensaje.tipo );
		void * buffer = malloc(nuevoMensaje.tamanio);
		recibido = recibirPorSocket(fdCliente, buffer, nuevoMensaje.tamanio);
		
		if (recibido > 0) {
			*tipoMensaje = nuevoMensaje.tipo;
			*tamanioMensaje = nuevoMensaje.tamanio;
			return buffer;
		}
	}
	return NULL;
}