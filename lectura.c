#include "transporteADT.h"

void cargarEstaciones(transporteADT trans, char *archivo_estaciones){

	FILE * archEstacion = fopen(archivo_estaciones, "r");

	if (archEstacion == NULLL) {
		printf("No se pudo abrir el archivo de estaciones\n");
		exit(1);
	}

	// Se saltea los encabezados
	while (fgetc(archEstacion) != '\n');

	/* Lectura de estaciones */
	int id; char *linea = malloc(30), *estacion = malloc(30);

	while (fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion) == 3) {
		//printf("Adding %d, %s, %s\n", id, linea, estacion);
		addEstacion(trans, id, linea, estacion);
	}

	fclose(archEstacion);

	printf("Se agregaron %d estaciones y %d lineas\n", trans->cant_estaciones, trans->cant_lineas);

}


void cargarMolinetes(transporteADT trans, char *archivo_molinetes){

  FILE * archMol = fopen(archivo_molinetes, "r");

	if (archMol == NULLL) {
		printf("No se pudo abrir el archivo de molinetes\n");
		exit(1);
	}

	// Se saltea los encabezados
	while (fgetc(archMol) != '\n');

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
