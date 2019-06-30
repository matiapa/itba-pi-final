#ifndef TRANSPORTEADT_H
#define TRANSPORTEADT_H

typedef struct transporteCDT * transporteADT;

transporteADT newTransporte();
void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion);

void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, unsigned int id, unsigned int cant);

// Solo para testing, borrar antes de entregar
void getEstacion(transporteADT trans, int id, char *nombre, char *linea);

#endif

/*
*/
