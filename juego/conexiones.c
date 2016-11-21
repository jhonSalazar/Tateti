/*
 * conexiones.c
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */

#include <cv.h>
#include <highgui.h>
#include <string.h>
#include "conexiones.h"


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


int abrir_socket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		perror("error al abrir el descriptor :");

	return sockfd;

}


int tiene_valores_consecutivos(int matriz_consecutivos[3][3],int tipoSimbolo)
{

	// calculo horizontal vg_simbolo_retador
	if(matriz_consecutivos[0][0] == tipoSimbolo && matriz_consecutivos[0][1] == tipoSimbolo && matriz_consecutivos[0][2] == tipoSimbolo)
		return 1;
	

	if(matriz_consecutivos[1][0] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[1][2] == tipoSimbolo)
		return 1;


	if(matriz_consecutivos[2][0] == tipoSimbolo && matriz_consecutivos[2][1] == tipoSimbolo && matriz_consecutivos[2][2] == tipoSimbolo)
		return 1;

	
//fin de caculo horizontal

	//calculo vertical vg_simbolo_retador

	if(matriz_consecutivos[0][0] == tipoSimbolo && matriz_consecutivos[1][0] == tipoSimbolo && matriz_consecutivos[2][0] == tipoSimbolo)
		return 1;



	if(matriz_consecutivos[0][1] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[2][1] == tipoSimbolo)
		return 1;



	if(matriz_consecutivos[0][2] == tipoSimbolo && matriz_consecutivos[1][2] == tipoSimbolo && matriz_consecutivos[2][2] == tipoSimbolo)
		return 1;

	//fin de calculo vertical

	//calculo diagonal vg_simbolo_retador
	if(matriz_consecutivos[0][0] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[2][2] == tipoSimbolo)
		return 1;


	if(matriz_consecutivos[0][2] == tipoSimbolo && matriz_consecutivos[1][1] == tipoSimbolo && matriz_consecutivos[2][0] == tipoSimbolo)
		return 1;

	


	//fin de calculo diagonal

	//caso que no tenga ningun lugar consecutivo
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
		
		if((x>=C9_X1 && x<=C9_X2) && (y>=C9_Y1 && y<=C9_Y2)){
			cuadrante.x1=C9_X1;
			cuadrante.x2=C9_X2;
			cuadrante.y1=C9_Y1;
			cuadrante.y2=C9_Y2;
			cuadrante.pos1=2;
			cuadrante.pos2=2;
		}

		// si esta fuera del cuadrante
		if((x<C1_X1 || x>C9_X2) || (y<C1_Y1 || y>C9_Y2)){

			cuadrante.x1=POSICION_ERRONEA;
			cuadrante.x2=POSICION_ERRONEA;
			cuadrante.y1=POSICION_ERRONEA;
			cuadrante.y2=POSICION_ERRONEA;
			cuadrante.pos1=POSICION_ERRONEA;
			cuadrante.pos2=POSICION_ERRONEA;

		}

		return cuadrante;
}




int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante ){
int tamanioMensaje, tipoMensaje;
void* buffer;

	
if(vg_empate > 9){
			puts("El juego quedo en empate \n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_cliente_fd,empate,buffer ,tamanioMensaje);
			close(vg_socket_fd);
			free(buffer);
			exit(1);

	}	

if(tiene_valores_consecutivos(matriz_consecutivos,tipoSimbolo)){
			puts("Acabo de ganar el juego \n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_cliente_fd,gane,buffer ,tamanioMensaje);
			close(vg_cliente_fd);
			free(buffer);
			exit(1);
		}
		if(tiene_valores_consecutivos(matriz_consecutivos,vg_simbolo_retador)){
			puts("Acabo de perder el juego\n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_cliente_fd,perdi,buffer ,tamanioMensaje);
			close(vg_cliente_fd);
			free(buffer);
			exit(1);
		}

		
	if(!tiene_valores_consecutivos(matriz_consecutivos,tipoSimbolo) && !tiene_valores_consecutivos(matriz_consecutivos,vg_simbolo_retador))
	{
					if(matriz_estados[cuadrante.pos1][cuadrante.pos2] == 1 )
					{
						matriz_consecutivos[cuadrante.pos1][cuadrante.pos2]=tipoSimbolo;
						matriz_estados[cuadrante.pos1][cuadrante.pos2]= 0;
						vg_empate++;
						
						return 1;
					}
					else
					{

						//	puts("elegir otro cuadrante para dibujar, este ya esta ocupado;\n");
						return 0;

					}
				
	

	}else{

		//printf("el juego ha terminado, Gane!!\n");
		//exit(EXIT_FAILURE);
	}

	






	return 0;
			


}




void dibujar_O(Cuadrante cuadrante,CvArr* img1){

	
	cvCircle(img1, cvPoint( (cuadrante.x1 + cuadrante.x2)/2,(cuadrante.y1 + cuadrante.y2)/2), RADIO	, CV_RGB(0,153,0), 2, CV_AA, 0);
	cvShowImage(vg_name, img1);

}

 void dibujar_x(Cuadrante cuadrante,CvArr* img1){
 					//x1,y1										//x2,y2
		cvLine(img1, cvPoint(cuadrante.x1,cuadrante.y1),cvPoint(cuadrante.x2,cuadrante.y2), CV_RGB(255,0,0), 2, CV_AA , 0);
							//x1,y2										//x2,y1
		cvLine(img1, cvPoint(cuadrante.x1,cuadrante.y2),cvPoint(cuadrante.x2,cuadrante.y1), CV_RGB(255,0,0), 2, CV_AA , 0);
		cvShowImage(vg_name, img1);


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

int estafueraDelRango(Cuadrante cuadrante){
int tamanioMensaje, tipoMensaje;
void* buffer;
	// si esta fuera del cuadrante
		if((cuadrante.pos1 == -1) && (cuadrante.pos2 == -1))
		{
			puts("Estas fuera del rango, elige otro lugar \n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_cliente_fd,fuera_del_rango,buffer ,tamanioMensaje);
			free(buffer);
			
			return 1;
			
		}
		else{
			
			return 0;
		}
		
}

void mouseHandler(int event, int x, int y, int flags, void* param)
{	

	char horario[26];
	char* servidor="servidor";
	void* buffer;
	int tamanioMensaje;
	if (event != CV_EVENT_LBUTTONDOWN)
	{	

	}
	if(event == CV_EVENT_LBUTTONDOWN)
	{

		vg_cuadrante=calcular_cuadrante(x,y);
			if(vg_turno == 1 )
			{

							
 						if(estafueraDelRango(vg_cuadrante))
 						{
 							puts("Dibuje de nuevo por favor\n");

 						}else
 						{

 					
 							dibujar_en_cuadrante(vg_cuadrante,vg_img1,vg_simbolo_jugador);
 							calcular_hora(horario);
 							guardar_movimientos(vg_logger,vg_cuadrante,servidor,horario);


 						//	t_jugada* vg_jugada= (t_jugada*) malloc(sizeof(t_jugada));

 							tamanioMensaje=sizeof(vg_cuadrante);

 							buffer=malloc(tamanioMensaje);

							memcpy(buffer,&vg_cuadrante,tamanioMensaje);

							enviarPaquete(vg_cliente_fd,vg_simbolo_jugador,buffer,tamanioMensaje);

 							enviarPaquete(vg_cliente_fd,tu_turno,buffer,tamanioMensaje);

 
/*typedef struct jugada
{
	char* name;
	char hora_jugada[26];
	Cuadrante cuadrante;
	
}t_jugada;*/
 							vg_turno=0;

 							free(buffer);
 						//	free(tamanioMensaje);
//
 							
						//	strcpy(vg_jugada->name,servidor);
						//	printf("name: %s\n",vg_jugada->name );
//							printf("name: %s\n",vg_jugada->hora_jugada);
						//	vg_jugada->cuadrante=vg_cuadrante;
						//	agregar_datos(vg_lista_jugadas,vg_jugada);
					//		printf("el tamanio de la lista es: %d\n", tamanio_lista(vg_lista_jugadas));	
 					}

			}else{
			puts("Aun no es mi turno\n");
		}
				
	}

	
}




void transferencia_datos(){
void *buffer;
char horario[26];
char* retador="retador";
int tipoSimbolo,tamanioMensaje;
//int num;
		while(1)
		{

			buffer=recibirPaquete(vg_cliente_fd,&tipoSimbolo,&tamanioMensaje);
			if(buffer !=NULL)
			{
				/*
					typedef struct jugada
					{
					char* name[30];
					char* hora_jugada[20];
					Cuadrante cuadrante;
	
					}t_jugador*/
				switch(tipoSimbolo){

				case empate:
										puts("El juego quedo en empate\n");
										free(buffer);
										//copiar_logger(vg_lista_jugadas,vg_loggerv2);
										fclose(vg_logger);
										copiar_logger(vg_lista_jugadas,vg_loggerv2);
										fclose(vg_loggerv2);
										exit(1);
										break;

				case circulo:
								memcpy(&vg_cuadrante,buffer,tamanioMensaje);
								//vg_simbolo_retador=tipoSimbolo;
								dibujar_en_cuadrante_desde_cliente(vg_cuadrante,vg_img1,tipoSimbolo);
								calcular_hora(horario);

								//t_jugada* vg_jugada1= (t_jugada*) malloc(sizeof(t_jugada));
							//	strcpy(vg_jugada1->name,retador);
							//	strcpy(vg_jugada1->hora_jugada,horario);
							//	vg_jugada1->cuadrante=vg_cuadrante;
							//	agregar_datos(vg_lista_jugadas,vg_jugada1);


								guardar_movimientos(vg_logger,vg_cuadrante,retador,horario);
								free(buffer);
								//free(vg_jugada1);
								break;
				case X:		
						memcpy(&vg_cuadrante,buffer,tamanioMensaje);
								//vg_simbolo_retador=tipoSimbolo;
								dibujar_en_cuadrante_desde_cliente(vg_cuadrante,vg_img1,tipoSimbolo);
								calcular_hora(horario);

								//t_jugada* vg_jugada2= (t_jugada*) malloc(sizeof(t_jugada));
								//strcpy(vg_jugada2->name,retador);
							//	strcpy(vg_jugada2->hora_jugada,horario);
							//	vg_jugada2->cuadrante=vg_cuadrante;
							//	agregar_datos(vg_lista_jugadas,vg_jugada2);
								guardar_movimientos(vg_logger,vg_cuadrante,retador,horario);
								free(buffer);
							//	free(vg_jugada2);
								break;

				case perdi:
							puts("perdi el juego");
							free(buffer);
							copiar_logger(vg_lista_jugadas,vg_loggerv2);
							close(vg_cliente_fd);
							fclose(vg_logger);
							fclose(vg_loggerv2);
							exit(EXIT_FAILURE);	
							
							break;

				case gane:
							puts("Gane el juego");
							free(buffer);
							copiar_logger(vg_lista_jugadas,vg_loggerv2);
							close(vg_cliente_fd);
								fclose(vg_logger);
								fclose(vg_loggerv2);
							exit(EXIT_FAILURE);	

							break;
				case fuera_del_rango:
							puts("El retador quiso dibujar fuera del rango...esperelo a que intente de nuevo\n");
							free(buffer);
							break;

				case simbolo_elegido:
									memcpy(&vg_simbolo_retador,buffer,tamanioMensaje);
								if(vg_simbolo_retador == 1){
									printf("El simbolo del retador es circulo :%d\n",vg_simbolo_retador);
									vg_simbolo_jugador=2;
									printf("Mi simboo es X :%d\n",vg_simbolo_jugador);
								}
								if(vg_simbolo_retador ==2){
									printf("El simbolo del retador es X :%d\n",vg_simbolo_retador);
									vg_simbolo_jugador=1;
									printf("Mi simboo es circulo :%d\n",vg_simbolo_jugador);
								}
									tamanioMensaje=sizeof(tamanioMensaje);
									buffer=malloc(tamanioMensaje);
									memcpy(buffer,&tamanioMensaje,tamanioMensaje);
       								enviarPaquete(vg_cliente_fd,tu_turno,buffer,tamanioMensaje);

									free(buffer);
								

								break;
				case tu_turno:
								puts("Elige un cuadrante por favor\n");
								vg_turno=1;
								free(buffer);
								break;
	
				default:
						
				return;
					

			}

			}else{

		//			close(vg_cliente_fd);
					//printf("%s\n","El juego ha terminado Winner!!");
		//			exit(EXIT_FAILURE);
				
				return;
			}


		}

	

}


void ciclo_de_conexiones(int socket_fd){
	int tamanioMensaje,mensaje;
	void* buffer;
struct sockaddr_in cliente;
//int client_fd;
socklen_t size;
mensaje=4;
    while(1) {
        size = sizeof(struct sockaddr_in);

        if ((vg_cliente_fd = accept(socket_fd, (struct sockaddr *)&cliente, &size))==-1) {
            //fprintf(stderr,"Accept Failure\n");
            perror("accept");
            exit(1);
        }
        printf("Él servidor tiene una conexion %s\n", inet_ntoa(cliente.sin_addr));
        //buffer = "Hello World!! I am networking!!\n";
        		tamanioMensaje=sizeof(tamanioMensaje);
				buffer=malloc(tamanioMensaje);
				memcpy(buffer,&mensaje,tamanioMensaje);
       			enviarPaquete(vg_cliente_fd,simbolo_elegido,buffer,tamanioMensaje);
       			free(buffer);
        		transferencia_datos();

       close(vg_cliente_fd);
    }


}







FILE* crear_logger(const char* nombre){


FILE* archivo = fopen(nombre,"a");
if (archivo == NULL)
 {
 	puts("No se puede crear el archivo");
 	return NULL;
 } else{

 	return archivo;
 }

}




void calcular_hora(char* buffer){
	time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);	

}

void guardar_movimientos(FILE* logger,Cuadrante cuadrante, char* name,char* horario)
{

fprintf(logger,"El %s, realizo una jugada en el cuadrante\t  X1:%d \tX2:%d\t Y1:%d\t Y2:%d\t,Fecha y Hora %s\n\n", 
			name,cuadrante.x1,cuadrante.x2,cuadrante.y1,cuadrante.y2,horario);
	puts("se guardo en el archivo");

}


	
void linkear_nodos(t_nodo* anterior, t_nodo* siguiente) {
  if (anterior != NULL) {
    anterior->siguiente = siguiente;
  }
}

t_nodo* crear_nodo(void* datos) {
  t_nodo* nodo = malloc(sizeof(t_nodo));
  nodo->datos = datos;
  nodo->siguiente = NULL;
  return nodo;
}

 t_nodo* obtener_nodo(t_list* lista, int indice) {
  int cont = 0;

  if ((lista->contador > indice) && (indice >= 0)) {
    t_nodo *nodo = lista->cabeza;
    while (cont < indice) {
      nodo = nodo->siguiente;
      cont++;
    }
    return nodo;
  }
  return NULL;
}



t_list *crear_lista() {
  t_list *list = malloc(sizeof(t_list));
  list->cabeza = NULL;
  list->contador = 0;
  return list;
}

int agregar_datos(t_list *lista, void *datos) {
  t_nodo *nuevo_nodo = crear_nodo(datos);

  if (lista->contador == 0) {
  	puts("primer nodo agregado");
    lista->cabeza = nuevo_nodo;
  } else {
    linkear_nodos(obtener_nodo(lista, lista->contador - 1), nuevo_nodo);
  }
  lista->contador++;
  puts("se agrego el nodo con exito\n");
  return lista->contador - 1;
}


void* obtener_datos(t_list *lista, int indice) {
  t_nodo* nodo_in_indice = obtener_nodo(lista, indice);
  return nodo_in_indice != NULL ? nodo_in_indice->datos : NULL;
  puts("se obtuvo el primer nodo\n");
}


void *eliminar_nodo(t_list *lista, int indice) {
  void *datos = NULL;
  t_nodo *aux = NULL;

  if (lista->cabeza == NULL) return NULL;

  aux = obtener_nodo(lista, indice);
  datos = aux->datos;

  if (indice == 0) {
    lista->cabeza = aux->siguiente;
  } else {
    t_nodo* anterior = obtener_nodo(lista, indice - 1);
    linkear_nodos(anterior, aux->siguiente);
  }

  lista->contador--;
  free(aux);
  return datos;
}

int tamanio_lista(t_list *lista) {
  return lista->contador;
}


void copiar_logger(t_list* lista, FILE* logger){
int i=0;
t_jugada* jugada;

	for(i=0;i<tamanio_lista(lista);i++){
		jugada=(t_jugada*) eliminar_nodo(lista,i);

		guardar_movimientos(logger,jugada->cuadrante,jugada->name,jugada->hora_jugada);

	}

}

