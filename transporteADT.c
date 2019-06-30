#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOQUE 100


//------------------------------------
//     DEFINICION DE STRUCTS
//------------------------------------

typedef struct tLinea {
	char * nombre;
	unsigned int pasajeros;			// Total de pasajeros
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

	tLinea * lineas_ord_alpha;			// Lista de líneas en orden alfabético
	tLinea ** lineas_ord_desc;			// Vector de punteros a líneas en orden descendente (por pasajeros)

	int cant_lineas;
	tEstacion * estaciones; 				// Arbol binario con todas las estaciones
	unsigned int cant_estaciones;

	long int pasajeros;					// Total de pasajeros
	unsigned int vec_diurno[7];			// Cantidad de pasajeros por día de la semana en período diurno, la primer posición es domingo
	unsigned int vec_nocturno[7];

}transporteCDT;



//------------------------------------
//     DECLARACION DE PROTOTIPOS
//------------------------------------


tEstacion * addEstacionRec(tEstacion * estacion, unsigned int id, char * nombre_estacion, tLinea * dir_linea, tEstacion **dir_est);

tLinea * addLinea(transporteADT trans, tLinea * node, char * nombre_linea, tLinea ** dir);

tEstacion *getEstacion(tEstacion *estacion, unsigned int id);

int compararLineas(tLinea **l1, tLinea **l2);

void calcularMaxPorLineaRec(tEstacion *estacion);


long int get_total_pasajeros(transporteADT trans);

void get_linea(char * nombre_linea,long int * pasajeros,int pos,transporteADT trans);



void get_pasajeros_dia(long int * dia,long int * noche,int i,transporteADT trans);

tLinea_con_pasajeros ** get_pasajeros_por_linea_vec(transporteADT trans);

tEstacion_favorita ** get_favourite_vec(transporteADT trans);

//------------------------------------
//     FUNCIONES DEL TAD
//------------------------------------


transporteADT newTransporte(char *archivo_estaciones, char *archivo_molinetes){ return calloc(1, sizeof(transporteCDT)); }


void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion) {

	/* Agrega la linea y guarda el puntero a la linea de la estacion */
	tLinea * dir_linea = NULL;
	trans->lineas_ord_alpha = addLinea(trans, trans->lineas_ord_alpha, nombre_linea, &dir_linea);

	tEstacion * dir_est = NULL;
	trans->estaciones = addEstacionRec(trans->estaciones, id, nombre_estacion, dir_linea, &dir_est);
	trans->cant_estaciones += 1;

	printf("Added: %d, %s, %s\n\n", id, dir_est->linea->nombre, dir_est->nombre);

}


tEstacion * addEstacionRec(tEstacion * estacion, unsigned int id, char * nombre_estacion, tLinea * dir_linea, tEstacion **dir_est) {

	if (estacion == NULL) {

		tEstacion *new_estacion = calloc(1, sizeof(tEstacion));

		/* Designa los valores a la estructura de la estacion */
		new_estacion->id = id;
		new_estacion->pasajeros = 0;
		new_estacion->linea = dir_linea;

		new_estacion->nombre = malloc(strlen(nombre_estacion)+1);
		strcpy(new_estacion->nombre, nombre_estacion);

		*dir_est = new_estacion;
		return new_estacion;

	}

	int c = id - estacion->id;

	if (c<0)
		estacion->left = addEstacionRec(estacion->left, id, nombre_estacion, dir_linea, dir_est);

	if (c>0)
		estacion->right = addEstacionRec(estacion->right, id, nombre_estacion, dir_linea, dir_est);

	return estacion;

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
	tEstacion *estacion = getEstacion(trans->estaciones, id);
	estacion->pasajeros += cant;
	estacion->linea->pasajeros += cant;
	trans->pasajeros += cant;

}


tEstacion *getEstacion(tEstacion *estacion, unsigned int id){

	if(estacion->id == id)
		return estacion;

	if(id > estacion->id)
		return getEstacion(estacion->right, id);

	return getEstacion(estacion->left, id);

}


 void ordenarLineasDesc(transporteADT trans){

	// Primero, completa el vector con los punteros a las líneas, que están en la lista
	trans->lineas_ord_desc = malloc(trans->cant_lineas*sizeof(tLinea *));
	trans->lineas_ord_desc[0] = trans->lineas_ord_alpha;
	for(int i=1; i<trans->cant_lineas; i++)
		trans->lineas_ord_desc[i] = trans->lineas_ord_desc[i-1]->next;

	// Luego, aplica quicksort sobre el vector
	qsort(trans->lineas_ord_desc, trans->cant_lineas, sizeof(tLinea *), (int (*)(const void *, const void *)) compararLineas);

}


void calcularMaxPorLinea(transporteADT trans){ calcularMaxPorLineaRec(trans->estaciones); }


void calcularMaxPorLineaRec(tEstacion *estacion){

	// Hace un recorrido preorder del arbol binario, actualizando el máximo de cada línea

	if(estacion->pasajeros > estacion->linea->max->pasajeros)
		estacion->linea->max = estacion;

	calcularMaxPorLineaRec(estacion->left);
	calcularMaxPorLineaRec(estacion->right);

}


int compararLineas(tLinea **l1, tLinea **l2){	return (*l1)->pasajeros - (*l2)->pasajeros; }


int get_cant_lineas(transporteADT trans){return trans->cant_lineas; }
//retorna la cantidad de lineas de subterraneo.


long int get_total_pasajeros(transporteADT trans){return trans->pasajeros; }
//retorna la cantidad de pasajeros total.


void get_linea(char * nombre_linea,long int * pasajeros,int pos,transporteADT trans)
{
	nombre_linea=trans->lineas_ord_desc[pos]->nombre;
	*pasajeros=trans->lineas_ord_desc[pos]->pasajeros;
}
//escribe en punteros que recibe, la cantidad de pasajeros y el nombre de la linea de el i'esimo elemento del vector decenciente de las lineas de subterraneo.



void get_pasajeros_dia(long int * dia,long int * noche,int i,transporteADT trans){
	*dia=trans->vec_diurno[i];
	*noche=trans->vec_nocturno[i];
}
// escribe en los punteros, la cantidad de pasajeros que transidtaron durante el dia y la noche en el dia i de la semana, con domingo siendo 0.





tLinea_con_pasajeros ** get_pasajeros_por_linea_vec(transporteADT trans)
{

	tLinea ** vec_original=trans->lineas_ord_desc;

	//recupero el vector con las lineas de subte ordenadas decendientemente

	int cant_lineas=get_cant_lineas(trans);
	tLinea_con_pasajeros ** vec=malloc(sizeof(tLinea_con_pasajeros*)*cant_lineas);
	//genero el vector en el que voy a guardar los datos

	for (int i=0;i<cant_lineas;i++)
	{
		tLinea_con_pasajeros * pEstructura=malloc(sizeof(tLinea_con_pasajeros));
		vec[i]=pEstructura;
		vec[i]->nombre_linea=vec_original[i]->nombre;
		vec[i]->pasajeros=vec_original[i]->pasajeros;
		//crea espacio para la estructura y transcibe los datos del TAD a una estructura que se conoce publicamente
	}
	return vec;
	//retorna el vector nuevamente creado
}



tEstacion_favorita ** get_favourite_vec(transporteADT trans)
{
	tLinea * lista=trans->lineas_ord_alpha;
	//recuperar la lista de lineas.
	tEstacion_favorita ** nuevo_vec=malloc(sizeof(tEstacion_favorita *));
	//generar el vector que voy a retornar
	int cant_lineas=get_cant_lineas(trans);
	for(int i=0;i<cant_lineas;i++)
	{
		nuevo_vec[i]=malloc(sizeof(tEstacion_favorita));
		nuevo_vec[i]->nombre_linea=lista->nombre;
		nuevo_vec[i]->nombre_estacion=lista->max->nombre;
		nuevo_vec[i]->pasajeros=lista->max->pasajeros;
		lista=lista->next;
	}
	//transcribir los datos de la estructura del TAD al la nueva estructura generada.

	return nuevo_vec;
	//retornar el vector de punetros con la info pertinente.
}
