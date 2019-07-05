#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


//------------------------------------
//     DEFINICION DE STRUCTS
//------------------------------------

typedef struct tLinea {
	char * nombre;
	long int pasajeros;			// Total de pasajeros
	struct tEstacion * max; 			// Puntero a la estacion con mas pasajeros
	struct tLinea * next;
} tLinea;

typedef struct tEstacion {
	unsigned int id;
	int pasajeros;		// Total de pasajeros
	char *nombre;
	tLinea *linea; 		// Puntero a la linea que pertenece
	struct tEstacion * left;
	struct tEstacion * right;
} tEstacion;


typedef struct transporteCDT {

	tLinea * lineas_ord_alpha;			// Lista de lineas en orden alfabetico
	tLinea ** lineas_ord_desc;			// Vector de punteros a lineas en orden descendente (por pasajeros)

	int cant_lineas;
	tEstacion * estaciones; 				// Arbol binario con todas las estaciones
	unsigned int cant_estaciones;

	long int pasajeros;					// Total de pasajeros
	unsigned int vec_diurno[DIAS_SEMANA];			// Cantidad de pasajeros por dia de la semana en periodo diurno, la primer posicion es domingo
	unsigned int vec_nocturno[DIAS_SEMANA];

}transporteCDT;



//----------------------------------------------------
//     PROTOTIPOS DE FUNCIONES PROPIAS DEL TAD
//----------------------------------------------------


tEstacion * addEstacionRec(tEstacion * estacion, const unsigned int id, const char * nombre_estacion, tLinea * dir_linea);

tLinea * addLinea(transporteADT trans, tLinea * node, const char * nombre_linea, tLinea ** dir);

tEstacion *getEstacion(tEstacion *estacion, const unsigned int id);

void calcularMax(tEstacion *estacion);

int compararLineas(const tLinea **l1, const tLinea **l2);

void postorderExecute(tEstacion *estacion, void (*execute)(tEstacion *));

void freeLinea(tLinea *linea);

void freeEstacion(tEstacion *estacion);



//-------------------------------------------------------------------
//     FUNCIONES DEL TAD - ALMACENAMIENTO Y PROCESAMIENTO
//-------------------------------------------------------------------


void *smalloc(int bytes, char *err_msg){

	void *address = malloc(bytes);

	if(address==NULL || errno==ENOMEM){
		printf("%s", err_msg);
		exit(1);
	}

	return address;

}

void *scalloc(int cant, int bytes, char *err_msg){

	void *address = calloc(cant, bytes);

	if(address==NULL || errno==ENOMEM){
		printf("%s", err_msg);
		exit(1);
	}

	return address;

}


transporteADT newTransporte(){
	transporteADT trans = scalloc(1, sizeof(transporteCDT), "Fallo al reservar memoria para crear transporteADT\n");
	return  trans;
}


void addEstacion(transporteADT trans, const unsigned int id, const char * nombre_linea, const char * nombre_estacion) {

	/* Agrega la linea y guarda el puntero a la linea de la estacion */
	tLinea * dir_linea = NULL;
	trans->lineas_ord_alpha = addLinea(trans, trans->lineas_ord_alpha, nombre_linea, &dir_linea);

	trans->estaciones = addEstacionRec(trans->estaciones, id, nombre_estacion, dir_linea);
	trans->cant_estaciones += 1;

	#if DEBUG
		tEstacion * dir_est = getEstacion(trans->estaciones, id);
		printf("\nEstacion agregada: %d, %s, %s", id, dir_est->linea->nombre, dir_est->nombre);
	#endif

}


tEstacion * addEstacionRec(tEstacion * estacion, const unsigned int id, const char * nombre_estacion, tLinea * dir_linea) {

	if (estacion == NULL) {

		tEstacion *new_estacion = scalloc(1, sizeof(tEstacion), "Fallo al reservar memoria para almacenar estacion");

		// Designa los valores a la estructura de la estacion
		new_estacion->id = id;
		new_estacion->linea = dir_linea;

		new_estacion->nombre = smalloc(strlen(nombre_estacion)+1, "Fallo al reservar memoria para almacenar estacion");
		strcpy(new_estacion->nombre, nombre_estacion);

		return new_estacion;

	}

	int c = id - estacion->id;

	if (c<0)
		estacion->left = addEstacionRec(estacion->left, id, nombre_estacion, dir_linea);

	if (c>0)
		estacion->right = addEstacionRec(estacion->right, id, nombre_estacion, dir_linea);

	return estacion;

}


tLinea * addLinea(transporteADT trans, tLinea * node, const char * nombre_linea, tLinea ** dir) {

	/* Agrega la linea en orden alfabetico */

	int c;
	if (node == NULL || (c = strcmp(nombre_linea, node->nombre)) < 0) {

		trans->cant_lineas += 1;
		tLinea * new_linea = scalloc(1, sizeof(tLinea), "Fallo al reservar memoria para agregar linea\n");

		/* copia el nombre de la linea */
		new_linea->nombre = smalloc(strlen(nombre_linea)+1, "Fallo al reservar memoria para agregar linea\n");

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


void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, const unsigned int id, const unsigned int cant) {

	// Calcula el dia de la semana
	// Formula obtenida de https://stackoverflow.com/questions/6054016/c-program-to-find-day-of-week-given-date
	int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;

	// Si la hora esta entre las 6:00 y las 17:00 lo suma al vector diurno, sino al nocturno
	if (hora > 0600 && hora <= 1700)
		trans->vec_diurno[weekday] += cant;
	else
		trans->vec_nocturno[weekday] += cant;

	// Incrementa la cantidad de pasajeros de la estacion, linea y total
	tEstacion *estacion = getEstacion(trans->estaciones, id);
	estacion->pasajeros += cant;
	estacion->linea->pasajeros += cant;
	trans->pasajeros += cant;
}


tEstacion *getEstacion(tEstacion *estacion, const unsigned int id){

	if(estacion == NULL){
		printf("\nLa estacion %d no fue encontrada, abortando.\n", id);
		exit(1);
	}

	if(estacion->id == id)
		return estacion;

	if(id > estacion->id)
		return getEstacion(estacion->right, id);

	return getEstacion(estacion->left, id);

}


void ordenarLineasDesc(transporteADT trans){

	// Primero, completa el vector con los punteros a las lineas, que estan en la lista
	trans->lineas_ord_desc = smalloc(trans->cant_lineas*sizeof(tLinea *), "Fallo al reservar memoria para crear vector de lineas descendente.\n");

	trans->lineas_ord_desc[0] = trans->lineas_ord_alpha;
	for(int i=1; i<trans->cant_lineas; i++)
		trans->lineas_ord_desc[i] = trans->lineas_ord_desc[i-1]->next;

	// Luego, aplica quicksort sobre el vector
	qsort(trans->lineas_ord_desc, trans->cant_lineas, sizeof(tLinea *), (int (*)(const void *, const void *)) compararLineas);

	#if DEBUG
		printf("\n\nOrden descendente: ");
		for(int i=1; i<trans->cant_lineas; i++)
		 	printf("%s: %d, ", trans->lineas_ord_desc[i]->nombre, trans->lineas_ord_desc[i]->pasajeros);
	#endif

}


int compararLineas(const tLinea **l1, const tLinea **l2){	return -((*l1)->pasajeros - (*l2)->pasajeros); }


void calcularMaxPorLinea(transporteADT trans){
	 postorderExecute(trans->estaciones, calcularMax);

	 #if DEBUG
	 printf("\n\nMaximos por linea: ");
	 for(int i=0; i<trans->cant_lineas; i++)
	   	printf("%s: %d, ", trans->lineas_ord_desc[i]->max->nombre, trans->lineas_ord_desc[i]->max->pasajeros);
	 printf("\n\n");
	 #endif
 }


void calcularMax(tEstacion *estacion){
	if(estacion->linea->max == NULL || estacion->pasajeros > estacion->linea->max->pasajeros)
	 	estacion->linea->max = estacion;
}


// Hace un recorrido preorder del arbol binario de estaciones, ejecutando execute sobre cada estacion
void postorderExecute(tEstacion *estacion, void (*execute)(tEstacion *)){

	if(estacion==NULL)
		return;

	postorderExecute(estacion->left, execute);
	postorderExecute(estacion->right, execute);

	execute(estacion);

}


void freeTransporte(transporteADT trans){

	for(int i=0; i<trans->cant_lineas; i++)
		freeLinea(trans->lineas_ord_desc[i]);
	free(trans->lineas_ord_desc);

	postorderExecute(trans->estaciones, (void (*)(tEstacion *)) freeEstacion);

	free(trans);

}


void freeLinea(tLinea *linea){
	free(linea->nombre);
	free(linea);
}


void freeEstacion(tEstacion *estacion){
	free(estacion->nombre);
	free(estacion);
}



//-----------------------------------------------------
//     FUNCIONES DEL TAD - OBTENCION DE DATOS
//-----------------------------------------------------

int get_cant_lineas(const transporteADT trans){return trans->cant_lineas; }


void get_linea(char ** nombre_linea, long int * pasajeros, const int pos, const transporteADT trans){

	// Devuelve la cantidad de pasajeros y el nombre de la linea de el i'esimo elemento del vector de lineas en orden descendente
	*nombre_linea = smalloc(strlen(trans->lineas_ord_desc[pos]->nombre)+1, "Fallo al reservar memoria en get_linea()\n");

	strcpy(*nombre_linea, trans->lineas_ord_desc[pos]->nombre);
	*pasajeros = trans->lineas_ord_desc[pos]->pasajeros;

}


// Escribe en los punteros, la cantidad de pasajeros que transidtaron durante el dia y la noche en el dia i de la semana, con domingo siendo 0.
void get_pasajeros_por_dia(long int * dia, long int * noche, const int i, const transporteADT trans){
	*dia=trans->vec_diurno[i];
	*noche=trans->vec_nocturno[i];
}


tLinea_con_pasajeros ** get_pasajeros_por_linea(const transporteADT trans){

	// Recupera el vector con las lineas de subte ordenadas decendentemente
	tLinea ** lineas_original=trans->lineas_ord_desc;
	int cant_lineas=trans->cant_lineas;

	// Genera el vector en el que se guardaran las lineas
	tLinea_con_pasajeros ** lineas=smalloc(sizeof(tLinea_con_pasajeros*)*cant_lineas, "Fallo al reservar memoria en get_pasajeros_por_linea\n");

	// Copia las lineas del vector original al nuevo vector de estructuras conocidas publicamente
	for (int i=0;i<cant_lineas;i++){

		lineas[i] = smalloc(sizeof(tLinea_con_pasajeros), "Fallo al reservar memoria en get_pasajeros_por_linea\n");

		lineas[i]->nombre_linea=smalloc(strlen(lineas_original[i]->nombre)+1, "Fallo al reservar memoria en get_pasajeros_por_linea");
		strcpy(lineas[i]->nombre_linea, lineas_original[i]->nombre);

		lineas[i]->pasajeros=lineas_original[i]->pasajeros;
	}

	return lineas;
}


long int get_total_pasajeros(const transporteADT trans){return trans->pasajeros; }


tEstacion_favorita ** get_favourite_vec(transporteADT trans){

	tLinea * lineas=trans->lineas_ord_alpha;
	int cant_lineas=trans->cant_lineas;

	tEstacion_favorita ** estaciones_favs=smalloc(sizeof(tEstacion_favorita *)*cant_lineas, "Fallo al reservar memoria en get_favourite_vec");

	// Transcribe los datos de la estructura del TAD al la nueva estructura generada conocida publicamente.
	for(int i=0;i<cant_lineas;i++)
	{
		estaciones_favs[i]=smalloc(sizeof(tEstacion_favorita), "Fallo al reservar memoria en get_favourite_vec");

		estaciones_favs[i]->nombre_linea=smalloc(strlen(lineas->nombre)+1, "Fallo al reservar memoria en get_favourite_vec");
		strcpy(estaciones_favs[i]->nombre_linea, lineas->nombre);

		estaciones_favs[i]->nombre_estacion=smalloc(strlen(lineas->max->nombre)+1, "Fallo al reservar memoria en get_favourite_vec");
		strcpy(estaciones_favs[i]->nombre_estacion, lineas->max->nombre);

		estaciones_favs[i]->pasajeros=lineas->max->pasajeros;
		lineas=lineas->next;
	}

	return estaciones_favs;
}
