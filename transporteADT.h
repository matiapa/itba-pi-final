#ifndef TRANSPORTEADT_H
#define TRANSPORTEADT_H

typedef struct transporteCDT * transporteADT;

transporteADT newTransporte();
void addEstacion(transporteADT trans, unsigned int id, char * linea, char * estacion);

#endif
