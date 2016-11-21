#include "listas.h"
#include <cv.h>
#include <highgui.h>
#include <pthread.h>
#include "conexiones.h"


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
		jugada=(t_jugada*)eliminar_nodo(lista,i);

		guardar_movimientos(logger,jugada->cuadrante,jugada->name,jugada->hora_jugada);

	}

}

