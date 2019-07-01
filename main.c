#include "transporteADT.h"
#include "lectura.h"
#include "queries.h"

#include <stdio.h>

int main(int argc, char **argv) {

	if(argc!=3){
		printf("Uso: ./transporte archivo_estaciones archivo_molinetes");
		return 1;
	}

	transporteADT trans = newTransporte();

	// Carga de datos
	cargarEstaciones(trans, argv[1]);
	cargarMolinetes(trans, argv[2]);


	// Procesamiento de datos
	ordenarLineasDesc(trans);
	calcularMaxPorLinea(trans);

	//
	// printf("Carga de datos completa \n");
	//
	// query1(trans);
	// printf("query1 terminado \n");
	//
	// query2(trans);
	// printf("query2 terminado \n");
	//
	// query3(trans);
	// printf("query3 terminado \n");

	//query4(trans);

}
