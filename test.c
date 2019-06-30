#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	transporteADT trans = newTransporte();

	// Lectura de estaciones.csv

	FILE * archEstacion = fopen("estaciones.csv", "r");
	FILE * archMol = fopen("molinetes2.csv", "r");
	
	if (archEstacion == NULL || archMol == NULL) {
		printf("No se pudo abrir uno de los archivos\n");
		exit(1);
	}

	// Se saltea el encabezado
	while (fgetc(archEstacion) != '\n');
	while (fgetc(archMol) != '\n');
	
	/* Lectura de estaciones.csv */
	int id; char *linea = malloc(30), *estacion = malloc(30);
	while (fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion) == 3) {
		printf("Adding: %d, %s, %s\n", id, linea, estacion);
		addEstacion(trans, id, linea, estacion);
	}
	
	/* Lectura de molinetes2.csv */
	unsigned int hora, min, hrs, cant, d, m, y;
	while (fscanf(archMol, "%d/%d/%d,%*[^,],%d:%d,%d,%d", &d, &m, &y, &hrs, &min, &id, &cant) == 7) {
		hora = hrs*100 + min;
		addPasajero(trans, d, m, y, hora, id, cant);
	}
}
