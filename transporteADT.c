#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOQUE 100

typedef struct estacion {
	char * nombre; /* nombre de la estacion */
	unsigned int cant; /* cantidad de pasajeros de la estacion */
	struct tLinea * linea; /* puntero a la linea que pertenece */
} estacion;

/* Las lineas van a estar ordenadas en orden alfabetico */
typedef struct tLinea {
	char * nombre; /* nombre de la linea */
	unsigned int cant_linea; /* cantidad de pasajeros que transitan la inea */
	struct estacion * max; /* Puntero a la estacion con mayor pasajeros */
	struct tLinea * next; 
} tLinea;

typedef struct transporteCDT {
	tLinea * first;
	unsigned int total_pas; /* Suma de los pasajero de todas las lineas */
	unsigned int * vec_diurno; /* la posicion 0 es domingo, 1 lunes... */
	unsigned int * vec_noc; 
	struct estacion * vec_estac; /* vector con todas las estaciones donde el indice es el id de la estacion */
	unsigned int size; /* Cantidad de estaciones del transporte */
}transporteCDT;

/* Crea un nuevo transporte */
transporteADT newTransporte() {
	return calloc(1, sizeof(transporteCDT));
}

/* Agrega la linea en orden alfabetico */
tLinea * addLinea(tLinea * node, char * linea, tLinea * dir) {
	int c;
	if (node == NULL || (c = strcmp(linea, node->nombre) < 0)) {
		tLinea * aux = calloc(1, sizeof(*aux));

		/* copia el nombre de la linea */
		aux->nombre = malloc(strlen(linea));
		strcpy(aux->nombre, linea);

		aux->next = node;
		dir = aux;
		return aux;
	}

	node->next = addLinea(node->next, linea, dir);
	return node;
}

/* Agrega la etacion al transporte */
void addEstacion(transporteADT trans, unsigned int id, char * linea, char * estacion) {
	/* Chequea si hay espacio en el vector de estaciones, sino lo agrega */
	if (trans->size % BLOQUE == 0) {
		trans->vec_estac = realloc(trans->vec_estac, (trans->size + BLOQUE)*sizeof(trans->vec_estac));
	}

	/* Agrego la linea y guardo el puntero a la linea de la estacion */
	tLinea * dir = NULL;
	trans->first = addLinea(trans->first, linea, dir);

	/* Designa los valores a la estructura de la estacion */
	trans->vec_estac[id - 1].cant = 0;
	printf("Success\n");
	trans->vec_estac[id - 1].linea = dir; /* Me esta fallando esta linea */
	printf("Success\n");
	printf("%d, %s\n", trans->vec_estac[id - 1].cant, trans->vec_estac[id - 1].linea->nombre);
	strcpy(trans->vec_estac[id - 1].nombre, estacion);
	trans->size += 1;
}
