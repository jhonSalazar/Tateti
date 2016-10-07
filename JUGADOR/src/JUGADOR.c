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
#include "conexiones_cliente.h"
int main(void) {
	int socket_fd;


	    socket_fd =abrir_socket();
	    conectar(socket_fd);
}
