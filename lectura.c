#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cargarEstaciones(transporteADT trans, const char *archivo_estaciones){

	FILE * archEstacion = fopen(archivo_estaciones, "r");

	if (archEstacion == NULL) {
		printf("No se pudo abrir el archivo de estaciones\n");
		exit(1);
	}

	// Se saltea el encabezado
	while (fgetc(archEstacion) != '\n');

	/* Lectura de estaciones */
	int id; char linea[40], estacion[40];

	while (fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion) == 3) {
		//printf("Adding %d, %s, %s\n", id, linea, estacion);
		addEstacion(trans, id, linea, estacion);
	}

	fclose(archEstacion);

}


void cargarMolinetes(transporteADT trans, const char *archivo_molinetes){

	FILE * archMol = fopen(archivo_molinetes, "r");

	if (archMol == NULL) {
		printf("No se pudo abrir el archivo de molinetes\n");
		exit(1);
	}

	// Se saltea el encabezado
	while (fgetc(archMol) != '\n');

	/* Lectura de molinetes */
	unsigned int hora, min, hrs, cant, d, m, y, id;

	// Solo se leera la hora de finalizacion del intervalo, la de inicio no es necesaria
	while (fscanf(archMol, "%u/%u/%u,%*[^,],%u:%u,%u,%u", &d, &m, &y, &hrs, &min, &id, &cant) == 7) {
		hora = hrs*100 + min;
		//printf("Adding %d/%d/%d %d:%d - %d: %d\n", d, m, y, hrs, min, id, cant);
		addPasajero(trans, d, m, y, hora, id, cant);
	}

	fclose(archMol);

}
