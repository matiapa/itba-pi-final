#ifndef TRANSPORTEADT_H

#define TRANSPORTEADT_H

typedef struct transporteCDT * transporteADT;

transporteADT newTransporte();


#endif

typedef struct tEstacion_favorita
{
	char * nombre_estacion;
	char * nombre_linea;
	long int pasajeros;
}tEstacion_favorita;

// estructura de intercambio entre el TAD y el front end del query 4.

typedef struct tLinea_con_pasajeros
{
	char * nombre_linea;
	long int pasajeros;
}tLinea_con_pasajeros;

//estructura de intercambio entre el TAD y el fron end del query 3.


void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion);

tEstacion * addArbol(tEstacion * estacion, unsigned int id, char * nombre_estacion, tLinea * dir);

tLinea * addLinea(transporteADT trans, tLinea * node, char * nombre_linea, tLinea ** dir);

void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, unsigned int id, unsigned int cant);

tEstacion *getEstacion(tEstacion *estacion, unsigned int id);

void ordenarLineasDesc(transporteADT trans);

void calcularMaxPorLinea(transporteADT trans);

int compararLineas(tLinea **l1, tLinea **l2);

int get_cant_lineas(transporteADT trans);

long int get_total_pasajeros(transporteADT trans);

void get_linea(char * nombre_linea,int * pasajeros,int pos,transporteADT trans);

void get_pasajeros_dia(int * dia,int * noche,int i,transporteADT trans);


void calcularMaxPorLineaRec(tEstacion *estacion);y

tLinea_con_pasajeros ** get_pasajeros_por_linea_vec(transporteADT trans);

tEstacion_favorita ** get_favourite_vec(transporteADT trans);
