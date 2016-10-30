/*
 * conexiones.c
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */



#include "conexiones.h"

#include <string.h>

int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo)
{

	// calculo horizontal vg_simbolo_retador
	if(matriz_consecutivos[0][0] == tipoSimbolo && matriz_consecutivos[0][1] == tipoSimbolo && matriz_consecutivos[0][2] == tipoSimbolo)
		return 1;
	if(matriz_consecutivos[0][0] == vg_simbolo_retador && matriz_consecutivos[0][1] == vg_simbolo_retador && matriz_consecutivos[0][2] == vg_simbolo_retador)
		return 1;

	if(matriz_consecutivos[1][0] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[1][2] == tipoSimbolo)
		return 1;

	if(matriz_consecutivos[1][0] == vg_simbolo_retador && matriz_consecutivos[1][1] == vg_simbolo_retador && matriz_consecutivos[1][2] == vg_simbolo_retador)
		return 1;

	if(matriz_consecutivos[2][0] == tipoSimbolo && matriz_consecutivos[2][1] == tipoSimbolo && matriz_consecutivos[2][2] == tipoSimbolo)
		return 1;

	if(matriz_consecutivos[2][0] == vg_simbolo_retador && matriz_consecutivos[2][1] == vg_simbolo_retador && matriz_consecutivos[2][2] == vg_simbolo_retador)
		return 1;
//fin de caculo horizontal

	//calculo vertical vg_simbolo_retador

	if(matriz_consecutivos[0][0] == tipoSimbolo && matriz_consecutivos[1][0] == tipoSimbolo && matriz_consecutivos[2][0] == tipoSimbolo)
		return 1;

	if(matriz_consecutivos[0][0] == vg_simbolo_retador && matriz_consecutivos[1][0] == vg_simbolo_retador && matriz_consecutivos[2][0] == vg_simbolo_retador)
		return 1;


	if(matriz_consecutivos[0][1] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[2][1] == tipoSimbolo)
		return 1;

	if(matriz_consecutivos[0][1] == vg_simbolo_retador && matriz_consecutivos[1][1] == vg_simbolo_retador && matriz_consecutivos[2][1] == vg_simbolo_retador)
		return 1;


	if(matriz_consecutivos[0][2] == tipoSimbolo && matriz_consecutivos[1][2] == tipoSimbolo && matriz_consecutivos[2][2] == tipoSimbolo)
		return 1;

	//fin de calculo vertical

	//calculo diagonal vg_simbolo_retador
	if(matriz_consecutivos[0][0] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[2][2] == tipoSimbolo)
		return 1;

	if(matriz_consecutivos[0][0] == vg_simbolo_retador && matriz_consecutivos[1][1] == vg_simbolo_retador && matriz_consecutivos[2][2] == vg_simbolo_retador)
		return 1;

	if(matriz_consecutivos[0][2] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[2][0] == tipoSimbolo)
		return 1;

	if(matriz_consecutivos[0][2] == vg_simbolo_retador && matriz_consecutivos[1][1] == vg_simbolo_retador && matriz_consecutivos[2][0] == vg_simbolo_retador)
		return 1;


	//fin de calculo diagonal

	//caso que no tenga ningun lugar consecutivo
	return 0;

}




int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante ){

	
	if(!tiene_valores_consecutivos(matriz_consecutivos,tipoSimbolo))
	{
					if(matriz_estados[cuadrante.pos1][cuadrante.pos2] == 1 )
					{
						matriz_consecutivos[cuadrante.pos1][cuadrante.pos2]=tipoSimbolo;
						matriz_estados[cuadrante.pos1][cuadrante.pos2]= 0;
						return 1;
					}
					else
					{

						//	puts("elegir otro cuadrante para dibujar, este ya esta ocupado;\n");
						return 0;

					}
				
	

	}else{

		printf("el juego ha terminado, Loser!!\n");
		exit(EXIT_FAILURE);
	}

	return 0;
			


}

 Cuadrante calcular_cuadrante(int x, int y){

Cuadrante cuadrante;
//1er cuadrante

	if((x>=C1_X1 && x<=C1_X2)&&(y>=C1_Y1 && y <=C1_Y2)){

		cuadrante.x1=C1_X1;
		cuadrante.x2=C1_X2;
		cuadrante.y1=C1_Y1;
		cuadrante.y2=C1_Y2;
		cuadrante.pos1=0;
		cuadrante.pos2=0;


		}
	



//2do cuadrante
	if((x>=C2_X1 && x<=C2_X2) &&(y>=C2_Y1 && y<= C2_Y2)){

		cuadrante.x1=C2_X1;
		cuadrante.x2=C2_X2;
		cuadrante.y1=C2_Y1;
		cuadrante.y2=C2_Y2;
		cuadrante.pos1=0;
		cuadrante.pos2=1;
	}

	
		//tercer cuadrante
	if((x>=C3_X1 && x<=C3_X2) &&(y>=C3_Y1 && y<= C3_Y2)){
		cuadrante.x1=C3_X1;
		cuadrante.x2=C3_X2;
		cuadrante.y1=C3_Y1;
		cuadrante.y2=C3_Y2;
		cuadrante.pos1=0;
		cuadrante.pos2=2;
	}
	
		//cuarto cuadrante
	if((x>=C4_X1 && x<=C4_X2) &&(y>=C4_Y1 && y<= C4_Y2)){
		cuadrante.x1=C4_X1;
		cuadrante.x2=C4_X2;
		cuadrante.y1=C4_Y1;
		cuadrante.y2=C4_Y2;
		cuadrante.pos1=1;
		cuadrante.pos2=0;
	}
	

		//5to cuadrante
		if((x>=C5_X1 && x<=C5_X2) &&(y>=C5_Y1 && y<=C5_Y2)){
			cuadrante.x1=C5_X1;
			cuadrante.x2=C5_X2;
			cuadrante.y1=C5_Y1;
			cuadrante.y2=C5_Y2;
			cuadrante.pos1=1;
			cuadrante.pos2=1;
		}

		//6to cuadrante
	
		if((x>=C6_X1 && x<=C6_X2) &&(y>=C6_Y1 && y<=C6_Y2)){
			cuadrante.x1=C6_X1;
			cuadrante.x2=C6_X2;
			cuadrante.y1=C6_Y1;
			cuadrante.y2=C6_Y2;
			cuadrante.pos1=1;
			cuadrante.pos2=2;
		}

		//7to cuadrante
	
		if((x>=C7_X1 && x<=C7_X2) &&(y>=C7_Y1 && y<=C7_Y2)){
			cuadrante.x1=C7_X1;
			cuadrante.x2=C7_X2;
			cuadrante.y1=C7_Y1;
			cuadrante.y2=C7_Y2;
			cuadrante.pos1=2;
			cuadrante.pos2=0;
		}

		//8to cuadrante
	
		if((x>=C8_X1 && x<=C8_X2) &&(y>=C8_Y1 && y<=C8_Y2)){
			cuadrante.x1=C8_X1;
			cuadrante.x2=C8_X2;
			cuadrante.y1=C8_Y1;
			cuadrante.y2=C8_Y2;
			cuadrante.pos1=2;
			cuadrante.pos2=1;
		}

		//9to cuadrante
		
		if((x>=C9_X1 && x<=C9_X2) &&(y>=C9_Y1 && y<=C9_Y2)){
			cuadrante.x1=C9_X1;
			cuadrante.x2=C9_X2;
			cuadrante.y1=C9_Y1;
			cuadrante.y2=C9_Y2;
			cuadrante.pos1=2;
			cuadrante.pos2=2;
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

 void dibujar_en_cuadrante(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo)
 {
		switch(tipoSimbolo)
		{

			case circulo:		if(dibujo_segun_estado(matriz_estados,matriz_consecutivos,tipoSimbolo,cuadrante)){

									dibujar_O(cuadrante ,img1);
									break;
									}
							
								
							
							
							

			case X:			if(dibujo_segun_estado(matriz_estados,matriz_consecutivos,tipoSimbolo,cuadrante)){
								dibujar_x(cuadrante,img1);
								break;

							}
						
						
						
						
					

			default:
				printf("%s\n","Por favor elija un cuadrante disponible, este ya no lo esta\n");
			return;

		}


}

void dibujar_en_cuadrante_desde_cliente(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo)
 {
		switch(tipoSimbolo)
		{

			case circulo:		if(dibujo_segun_estado(matriz_estados,matriz_consecutivos,tipoSimbolo,cuadrante)){

									dibujar_O(cuadrante ,img1);
									break;
									}
							
								
							
							
							

			case X:			if(dibujo_segun_estado(matriz_estados,matriz_consecutivos,tipoSimbolo,cuadrante)){
								dibujar_x(cuadrante,img1);
								break;

							}
						
						
						
						
						
					

			default:
				printf("%s\n","Tu companiero intento dibujar en un lugar no correspondiente, esperalo a que intente de nuevo.....\n");
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
	//printf("se cargaron las corrdenadas x1:%d x2:%d \n",vg_cuadrante.x1,vg_cuadrante.x2);
 
 	
 	
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
				//printf("coordenadas obtenidas para dibujar\n");
				memcpy(&vg_cuadrante,buffer,tamanioMensaje);
				vg_simbolo_retador=tipoSimbolo;
				//printf("x1:%d X2: %d \n",vg_cuadrante.x1,vg_cuadrante.x2 );
				dibujar_en_cuadrante_desde_cliente(vg_cuadrante,img1,tipoSimbolo);
				free(buffer);

			}else{
				close(vg_cliente_fd);
				printf("%s\n","El juego ha terminado Winner!!");
				exit(EXIT_FAILURE);
				
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

	//	printf("%s", "enviar mensaje al servidor:  ");
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
		//printf("tamanio de mensaje:%d\n", nuevoMensaje.tamanio);
		//printf("el tipo del mensaje %d\n",nuevoMensaje.tipo );
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