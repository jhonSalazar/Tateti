/*
 * conexiones.c
 *
 *  Created on: 6/10/2016
 *      Author: utnso
 */



#include "conexiones.h"
 #include <cv.h>
#include <highgui.h>
 #include <pthread.h>
void cargar_matrices(){
int i,j;
	for(i=0;i<3;i++){
  		for(j=0;j<3;j++){
  			matriz_estados[i][j]=1;
  			matriz_consecutivos[i][j]=8;
  		}
  	}
}
void barra_procentaje(){

			int p;
  	     for(p = 0; p <= 100; p++)
    {
        int h;
        for(h = 0; h <= h/10; h++)
            printf("\rConectandose con el servidor.........................%d%s",p,"%");
         	fflush(stdout);
      		 usleep(100000);
      
    }

    puts("\n");
}
int abrir_socket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		perror("error al abrir el descriptor :");

	return sockfd;

}










void conectar(){
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=inet_addr(vg_ip);
	server.sin_port = htons(PORT);

	//client  connect to server on port

	if (connect(vg_socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("no me puedo conectar\n");
		exit(1);
	}
    else
    {
    	
    	transferencia_datos_server();
    }


}




void transferencia_datos_server(){
	int tipoSimbolo,tamanioMensaje;
	void* buffer;
	
	while(1){

		
		buffer =recibirPaquete(vg_socket_fd,&tipoSimbolo,&tamanioMensaje);
		if(buffer != NULL)
		{	
			//pregunto si es un empate	
			switch(tipoSimbolo){


				case tu_turno:
       								printf("Elige tu Jugada %s\n"," " );
       								vg_turno=1;
       							
       								break;			



				case empate:
										puts("El juego quedo en empate\n");
										exit(1);
										break;

				case circulo:
								memcpy(&vg_cuadrante,buffer,tamanioMensaje);
								vg_simbolo_retador=tipoSimbolo;
								dibujar_en_cuadrante_desde_servidor(vg_cuadrante,vg_img1,vg_simbolo_retador);
								free(buffer);
								break;
				case X:		
						memcpy(&vg_cuadrante,buffer,tamanioMensaje);
								vg_simbolo_retador=tipoSimbolo;
								dibujar_en_cuadrante_desde_servidor(vg_cuadrante,vg_img1,vg_simbolo_retador);
								free(buffer);
								break;


				case perdi:
							puts("Acabo de perder  el juego");
							close(vg_socket_fd);
							exit(EXIT_FAILURE);	
							break;	

				case gane:
								puts("Acabo de ganar  el juego");
								close(vg_socket_fd);
								exit(EXIT_FAILURE);	
								break;	
				case fuera_del_rango:
								puts("Tu companiero quiso dibujar fuera del rango...esperelo a que intente de nuevo\n");
							
								break;

				case simbolo_elegido:
									//puts("Bienvenido al juego, elige el simbolo que deseas utilizar por favor 2 para X y 1 para O:\n");
								
									//scanf("%d",&vg_simbolo_jugador);
									vg_simbolo_jugador=2;
									tamanioMensaje=sizeof(tamanioMensaje);
									buffer=malloc(tamanioMensaje);
									memcpy(buffer,&vg_simbolo_jugador,tamanioMensaje);
       								enviarPaquete(vg_socket_fd,simbolo_elegido,buffer,tamanioMensaje);
       								free(buffer);
       								//free(tamanioMensaje);
       								break;
       					
				default:
						
				return;
					

			}
			
		}else{
						close(vg_socket_fd);
					//	printf("%s\n","El juego ha terminado Ganaste");
						exit(EXIT_FAILURE);
			
		}
		

	}

}

int enviarPorSocket(int fdCliente, const void * mensaje, int tamanio) {
	int bytes_enviados;
	int total = 0;

	while (total < tamanio){
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
	//printf("tamanio:%d tipo:%d\n",nuevoMensaje.tamanio,nuevoMensaje.tipo );
	enviarPorSocket(fdCliente, (void *) &nuevoMensaje, sizeof(cabeceraMensaje));
	enviarPorSocket(fdCliente, mensaje, nuevoMensaje.tamanio);
}



void * recibirPaquete(int fdCliente, int * tipoMensaje, int * tamanioMensaje){
	cabeceraMensaje nuevoMensaje;
	int recibido = recibirPorSocket(fdCliente, &nuevoMensaje, sizeof(cabeceraMensaje));
	if (recibido > 0) {
	//	printf("el tamanioMensaje es:%d\n", nuevoMensaje.tamanio);
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


/*************************************************************************
calculo si mi simbolo y la del retador ya tiene 3 cuadrantes consecutivos*
**************************************************************************/
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


int dibujo_segun_estado(int matriz_estados[3][3],int matriz_consecutivos[3][3],int tipoSimbolo,Cuadrante cuadrante ){
int tamanioMensaje, tipoMensaje;
void* buffer;

	if(vg_empate >=9){
			puts("El juego quedo en empate \n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_socket_fd,empate,buffer ,tamanioMensaje);
			free(buffer);
			close(vg_socket_fd);
			exit(1);
	}	

	if(tiene_valores_consecutivos(matriz_consecutivos,tipoSimbolo)){
			puts("Acabo de ganar el juego \n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_socket_fd,gane,buffer ,tamanioMensaje);
			free(buffer);
			close(vg_socket_fd);
			exit(1);
		}
		if(tiene_valores_consecutivos(matriz_consecutivos,vg_simbolo_retador)){
			puts("Acabo de perder el juego\n");
			tamanioMensaje=sizeof(tipoMensaje);
			buffer=malloc(tamanioMensaje);
			memcpy(buffer,&tipoMensaje,tamanioMensaje);
			enviarPaquete(vg_socket_fd,perdi,buffer ,tamanioMensaje);
			free(buffer);
			close(vg_socket_fd);
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

	//	printf("el juego ha terminado,gane!!\n");
	//	exit(EXIT_FAILURE);
	}


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
		cuadrante.pos1=0;
		cuadrante.pos2=0;
	}



//2do cuadrante
	if((x>=107 && x<=197) &&(y>=16 && y<= 105)){

		cuadrante.x1=107;
		cuadrante.x2=197;
		cuadrante.y1=16;
		cuadrante.y2=105;
		cuadrante.pos1=0;
		cuadrante.pos2=1;
	}

		
		//tercer cuadrante
	if((x>=197 && x<=285) &&(y>=16 && y<= 105)){
		cuadrante.x1=197;
		cuadrante.x2=285;
		cuadrante.y1=16;
		cuadrante.y2=105;
		cuadrante.pos1=0;
		cuadrante.pos2=2;
	}

		//cuarto cuadrante
	if((x>=18 && x<=107) &&(y>=105 && y<= 194)){
		cuadrante.x1=18;
		cuadrante.x2=107;
		cuadrante.y1=105;
		cuadrante.y2=194;
		cuadrante.pos1=1;
		cuadrante.pos2=0;
	}
	

		//5to cuadrante
		if((x>=107 && x<=200) &&(y>=105 && y<=194)){
			cuadrante.x1=107;
			cuadrante.x2=200;
			cuadrante.y1=105;
			cuadrante.y2=194;
			cuadrante.pos1=1;
			cuadrante.pos2=1;
		}

		//6to cuadrante

		if((x>=200 && x<=285) &&(y>=105 &&

		 y<=194)){
			cuadrante.x1=200;
			cuadrante.x2=285;
			cuadrante.y1=105;
			cuadrante.y2=194;
			cuadrante.pos1=1;
			cuadrante.pos2=2;
		}

		//7to cuadrante

		if((x>=18 && x<=107) &&(y>=194 && y<=285)){
			cuadrante.x1=18;
			cuadrante.x2=107;
			cuadrante.y1=194;
			cuadrante.y2=285;
			cuadrante.pos1=2;
			cuadrante.pos2=0;
		}

		//8to cuadrante

		if((x>=107 && x<=200) &&(y>=194 && y<=285)){
			cuadrante.x1=107;
			cuadrante.x2=200;
			cuadrante.y1=194;
			cuadrante.y2=285;
			cuadrante.pos1=2;
			cuadrante.pos2=1;
		}

		//9to cuadrante

		if((x>=200 && x<=285) &&(y>=194 && y<=285)){
			cuadrante.x1=200;
			cuadrante.x2=285;
			cuadrante.y1=194;
			cuadrante.y2=285;
			cuadrante.pos1=2;
			cuadrante.pos2=2;
		}

		// si esta fuera del cuadrante
		if((x<18 || x>285) || (y<16 || y>285)){

			cuadrante.x1=POSICION_ERRONEA;
			cuadrante.x2=POSICION_ERRONEA;
			cuadrante.y1=POSICION_ERRONEA;
			cuadrante.y2=POSICION_ERRONEA;
			cuadrante.pos1=POSICION_ERRONEA;
			cuadrante.pos2=POSICION_ERRONEA;

		}



		return cuadrante;
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
		

  void dibujar_en_cuadrante_desde_servidor(Cuadrante cuadrante,CvArr* img1,int tipoSimbolo)
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
			enviarPaquete(vg_socket_fd,fuera_del_rango,buffer ,tamanioMensaje);
			free(buffer);
			return 1;
			
		}else{
			
			return 0;
		}

		
}

void mouseHandler(int event, int x, int y, int flags, void* param)
{	
	void* buffer;
	int tamanioMensaje;
	if (event != CV_EVENT_LBUTTONDOWN)
	{	
	

	}
	if(event == CV_EVENT_LBUTTONDOWN )
	{
		vg_cuadrante=calcular_cuadrante(x,y);
		if(vg_turno==1)
		{
					

 					if(estafueraDelRango(vg_cuadrante))
 					{
 						puts("Dibuje de nuevo por favor\n");
 					}else
 					{

 					dibujar_en_cuadrante(vg_cuadrante,vg_img1,vg_simbolo_jugador);
 					tamanioMensaje=sizeof(Cuadrante);
					buffer=malloc(tamanioMensaje);
					memcpy(buffer,&vg_cuadrante,tamanioMensaje);
					enviarPaquete(vg_socket_fd,vg_simbolo_jugador,buffer,tamanioMensaje);
					enviarPaquete(vg_socket_fd,tu_turno,buffer,tamanioMensaje);
					vg_turno=0;
					free(buffer);
 					
					//printf("se cargaron las corrdenadas x1:%d x2:%d \n",vg_cuadrante.x1,vg_cuadrante.x2);

 					}

 	
 	
 		}else
 		{
 			puts("aun no es tu turno, espere a que juegue tu companiero\n");

 		}
 	
	}
	
	
}



