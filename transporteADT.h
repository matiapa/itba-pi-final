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



int get_cant_lineas(transporteADT trans);

long int get_total_pasajeros(transporteADT trans);

void get_linea(char * nombre_linea,long int * pasajeros,int pos,transporteADT trans);

void get_pasajeros_dia(long int * dia,long int * noche,int i,transporteADT trans);

tLinea_con_pasajeros ** get_pasajeros_por_linea_vec(transporteADT trans);

tEstacion_favorita ** get_favourite_vec(transporteADT trans);
