#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOQUE 100


//------------------------------------
//     DEFINICION DE STRUCTS
//------------------------------------


typedef struct tEstacion {
	unsigned int id;
	char * nombre;
	unsigned int pasajeros;		// Total de pasajeros
	struct tLinea * linea; 		// Puntero a la linea que pertenece
	struct tEstacion * left;
	struct tEstacion * right;
} tEstacion;


typedef struct tLinea {
	char * nombre;
	unsigned int pasajeros;			// Total de pasajeros
	tEstacion * max; 			// Puntero a la estacion con mas pasajeros
	struct tLinea * next;
} tLinea;


typedef struct transporteCDT {

	tLinea * lineas_ord_alpha;			// Lista de líneas en orden alfabético
	tLinea ** lineas_ord_desc;			// Vector de punteros a líneas en orden descendente (por pasajeros)

	int cant_lineas;
	tEstacion * root;				// Vector con todas las estaciones donde el indice es el id de la estacion
	unsigned int cant_estaciones;

	unsigned int pasajeros;					// Total de pasajeros
	unsigned int vec_diurno[7];			// Cantidad de pasajeros por día de la semana en período diurno, la primer posición es domingo
	unsigned int vec_nocturno[7];

}transporteCDT;



//------------------------------------
//     DECLARACION DE PROTOTIPOS
//------------------------------------


void leerArchivos(transporteADT trans, char *archivo_estaciones, char *archivo_molinetes);

void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion);

tLinea * addLinea(transporteADT trans, tLinea * node, char * nombre_linea, tLinea ** dir);

void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, unsigned int id, unsigned int cant);

void procesarDatos(transporteADT trans);

int compararLineas(tLinea **l1, tLinea **l2);



//------------------------------------
//     FUNCIONES DEL TAD
//------------------------------------


transporteADT newTransporte(char *archivo_estaciones, char *archivo_molinetes) {

	transporteADT trans = calloc(1, sizeof(transporteCDT));

	leerArchivos(trans, archivo_estaciones, archivo_molinetes);
	procesarDatos(trans);

	return trans;
}


void leerArchivos(transporteADT trans, char *archivo_estaciones, char *archivo_molinetes){

	FILE * archEstacion = fopen(archivo_estaciones, "r");
	FILE * archMol = fopen(archivo_molinetes, "r");

	if (archEstacion == NULL || archMol == NULL) {
		printf("No se pudo abrir uno de los archivos\n");
		exit(1);
	}

	// Se saltea los encabezados
	while (fgetc(archEstacion) != '\n');
	while (fgetc(archMol) != '\n');


	/* Lectura de estaciones */
	int id; char *linea = malloc(30), *estacion = malloc(30);

	while (fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion) == 3) {
		//printf("Adding %d, %s, %s\n", id, linea, estacion);
		addEstacion(trans, id, linea, estacion);
	}

	fclose(archEstacion);


	printf("Se agregaron %d estaciones y %d lineas\n", trans->cant_estaciones, trans->cant_lineas);


	/* Lectura de molinetes */
	unsigned int hora, min, hrs, cant, d, m, y;

	// Solo se leera la hora de finalizacion del intervalo, la de inicio no es necesaria
	while (fscanf(archMol, "%d/%d/%d,%*[^,],%d:%d,%d,%d", &d, &m, &y, &hrs, &min, &id, &cant) == 7) {
		hora = hrs*100 + min;
		//printf("Adding %d/%d/%d %d:%d - %d: %d\n", d, m, y, hrs, min, id, cant);
		addPasajero(trans, d, m, y, hora, id, cant);
	}

	fclose(archMol);

	printf("Se agregaron %d pasajeros\n", trans->pasajeros);

}

tEstacion * addArbol(tEstacion * estacion, unsigned int id, char * nombre_estacion, tLinea * dir) {
	
	if (estacion == NULL) {
		tEstacion * new = calloc(1, sizeof(*estacion));
		new->linea = dir;
		new->id = id;
		new->nombre = malloc(strlen(nombre_estacion)+1);
		strcpy(new->nombre, nombre_estacion);
		return new;
	}
	
	int c = id - estacion->id;
	if (c < 0) {
		estacion->left = addArbol(estacion->left, id, nombre_estacion, dir);
	}
	if (c > 0) {
		estacion->right = addArbol(estacion->right, id, nombre_estacion, dir);
	}
	return estacion;
}

void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion) {

	/* Chequea si hay espacio en el vector de estaciones, sino lo agrega */
	if (trans->cant_estaciones % BLOQUE == 0)
		trans->estaciones = realloc(trans->estaciones, (trans->cant_estaciones + BLOQUE)*sizeof(tEstacion));

	/* Agrega la linea y guarda el puntero a la linea de la estacion */
	tLinea * dir = NULL;
	trans->lineas_ord_alpha = addLinea(trans, trans->lineas_ord_alpha, nombre_linea, &dir);

	/* Designa los valores a la estructura de la estacion */
	trans->root = addArbol(trans->root, id, nombre_estacion, dir);

	trans->cant_estaciones += 1;
	//printf("Added: %d, %s, %s\n\n", id, trans->estaciones[id].linea->nombre, trans->estaciones[id].nombre);

}


tEstacion *getEstacion(testacion *estacion, unsigned int id){

	if(estacion->id == id)
		return estacion;

	if(id > estacion->id)
		return getEstacion(estacion->right, id);

	return getEstacion(estacion->left, id);

}


tLinea * addLinea(transporteADT trans, tLinea * node, char * nombre_linea, tLinea ** dir) {

	/* Agrega la linea en orden alfabetico */

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

	node->next = addLinea(trans, node->next, nombre_linea, dir);
	return node;
}


void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, unsigned int id, unsigned int cant) {

	// Calcula el dia de la semana
	int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;

	// Si la hora esta entre las 6:00 y las 17:00 lo suma al vector diurno, sino al nocturno
	if (hora > 6000 && hora <= 1700)
		trans->vec_diurno[weekday] += cant;
	else
		trans->vec_nocturno[weekday] += cant;

	// Incrementa la cantidad de pasajeros de esa estacion, linea y total
	trans->estaciones[id].pasajeros += cant;
	trans->estaciones[id].linea->pasajeros += cant;
	trans->pasajeros += cant;

}


void procesarDatos(transporteADT trans){

	// Primero, completa el vector con los punteros a las líneas, que están en la lista
	trans->lineas_ord_desc = malloc(trans->cant_lineas*sizeof(tLinea *));
	trans->lineas_ord_desc[0] = trans->lineas_ord_alpha;
	for(int i=1; i<trans->cant_lineas; i++)
		trans->lineas_ord_desc[i] = trans->lineas_ord_desc[i-1]->next;

	// Luego, aplica quicksort sobre el vector
	qsort(trans->lineas_ord_desc, trans->cant_lineas, sizeof(tLinea *), (int (*)(const void *, const void *)) compararLineas);


	// Finalmente, calcula la maxima estacion por linea
	for(int i=1; i<trans->cant_estaciones; i++){
		//printf("%s %d vs %d\n", trans->estaciones[i].nombre, trans->estaciones[i].pasajeros, trans->estaciones[i].linea->max->pasajeros);
		 if(trans->estaciones[i].linea->max == NULL || trans->estaciones[i].pasajeros > trans->estaciones[i].linea->max->pasajeros);
		 	trans->estaciones[i].linea->max = trans->estaciones + i;
	}

	for(int i=0; i<trans->cant_lineas; i++){
		printf("%s - Pasajeros: %d - Max: %s, %d\n", trans->lineas_ord_desc[i]->nombre, trans->lineas_ord_desc[i]->pasajeros,
		trans->lineas_ord_desc[i]->max->nombre, trans->lineas_ord_desc[i]->max->pasajeros);
	}
}


int compararLineas(tLinea **l1, tLinea **l2){	return (*l1)->pasajeros - (*l2)->pasajeros; }
