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

}
