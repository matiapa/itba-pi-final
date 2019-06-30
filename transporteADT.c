#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOQUE 100

typedef struct tEstacion {
	char * nombre; /* nombre de la estacion */
	unsigned int pasajeros; /* cantidad de pasajeros de la estacion */
	struct tLinea * linea; /* puntero a la linea que pertenece */
} tEstacion;


/* Las lineas van a estar ordenadas en orden alfabetico */
typedef struct tLinea {
	char * nombre; /* nombre de la linea */
	unsigned int pasajeros; /* cantidad de pasajeros que transitan la inea */
	struct estacion * max; /* Puntero a la estacion con mayor pasajeros */
	struct tLinea * next;
} tLinea;


typedef struct transporteCDT {

	tLinea * lineas_ord_alpha;
	tLinea * lineas_ord_desc;

	int cant_lineas;
	tEstacion * estaciones; /* vector con todas las estaciones donde el indice es el id de la estacion */
	unsigned int cant_estaciones; /* Cantidad de estaciones del transporte */

	unsigned int pasajeros; /* Suma de los pasajeros de todas las lineas */
	unsigned int * vec_diurno; /* la posicion 0 es domingo, 1 lunes... */
	unsigned int * vec_nocturno;

}transporteCDT;


/* Crea un nuevo transporte */
transporteADT newTransporte(char *archivo_molinetes, char *archivo_estaciones) {

	transporteADT trans = calloc(1, sizeof(transporteCDT));

	leerEstaciones(trans, archivo_estaciones);
	leerMolinetes(trans, archivo_molinetes);
	procesarDatos(trans);

	return trans;
}


void leerEstaciones(transporteADT trans, char *nombre_archivo){

	FILE * archEstacion = fopen(nombre_archivo, "r");

	// Se saltea el encabezado
	while (fgetc(archEstacion) != '\n');

	int id; char *linea = malloc(30), *estacion = malloc(30);
	while (fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion) == 3) {
		printf("Adding: %d, %s, %s\n", id, linea, estacion);
		addEstacion(trans, id, linea, estacion);
	}

}

void leerMolinetes();


/* Agrega la etacion al transporte */
void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion) {

	/* Chequea si hay espacio en el vector de estaciones, sino lo agrega */
	if (trans->cant_estaciones % BLOQUE == 0)
		trans->estaciones = realloc(trans->estaciones, (trans->cant_estaciones + BLOQUE)*sizeof(tEstacion));

	/* Agrega la linea y guarda el puntero a la linea de la estacion */
	tLinea * dir = NULL;
	trans->lineas_ord_alpha = addLinea(trans->lineas_ord_alpha, nombre_linea, &dir);

	/* Designa los valores a la estructura de la estacion */
	trans->estaciones[id - 1].pasajeros = 0;
	trans->estaciones[id - 1].linea = dir;

	trans->estaciones[id - 1].nombre = malloc(strlen(nombre_estacion));
	strcpy(trans->estaciones[id - 1].nombre, nombre_estacion);

	trans->cant_estaciones += 1;
	printf("Added: %d, %s, %s\n\n", id, trans->estaciones[id - 1].linea->nombre, trans->estaciones[id - 1].nombre);

}

/* Agrega la linea en orden alfabetico */
tLinea * addLinea(tLinea * node, char * nombre_linea, tLinea ** dir) {
	int c;
	if (node == NULL || (c = strcmp(nombre_linea, node->nombre)) < 0) {

		trans->cant_lineas += 1;
		tLinea * new_linea = calloc(1, sizeof(tLinea));

		/* copia el nombre de la linea */
		new_linea->nombre = malloc(strlen(nombre_linea));
		strcpy(new_linea->nombre, nombre_linea);

		new_linea->next = node;
		*dir = new_linea;
		return new_linea;
	}

	/* Si la linea ya existe entonces no la agrega */
	if (c == 0) {
		*dir = node;
		return node;
	}

	node->next = addLinea(node->next, nombre_linea, dir);
	return node;
}


int comparar_lineas(tLinea *l1, tLinea *l2){ return l2->pasajeros - l1->pasajeros; }

void procesarDatos(transporteADT trans){

	// Primero, completa el vector con los punteros a las líneas, que están en la lista
	trans->lineas_ord_desc[0] = trans->lineas_ord_alpha;
	for(int i=1; i<trans->cant_lineas; i++)
		trans->lineas_ord_desc[i] = trans->lineas_ord_desc[i-1].next;

	// Luego, aplica quicksort sobre el vector
	qsort(trans->lineas_ord_desc, trans->cant_lineas, sizeof(*tLinea), comparar_lineas);

}
