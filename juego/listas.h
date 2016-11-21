#include <stdlib.h>
#include <cv.h>
#include <stdio.h>
#include <highgui.h>
#include <pthread.h>

typedef  struct nodo{
    void *datos;
    struct nodo* siguiente;
  }t_nodo;
  

typedef struct {
    t_nodo *cabeza;
    int contador;
  } t_list;
t_list* vg_lista_jugadas;

void linkear_nodos(t_nodo* anterior, t_nodo* siguiente);
t_nodo* crear_nodo(void* datos);
 t_nodo* obtener_nodo(t_list* lista, int indice) ;
 t_list* crear_lista();
 int agregar_datos(t_list *lista, void *datos);
 void* obtener_datos(t_list *lista, int indice) ;
 void *eliminar_nodo(t_list *lista, int indice);
 int tamanio_lista(t_list *lista) ;
 void copiar_logger(t_list* lista, FILE* logger);