#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	if(argc!=3){
		printf("Uso: ./transporte archivo_estaciones archivo_molinetes");
		return 1;
	}

	transporteADT trans = newTransporte(argv[1], argv[2]);
}

/*
newTransporte
|
|-> leerArchivos
|   |
|   |-> addEstacion
|   |   |
|   |   |-> addLinea
|   |
|   |-> addPasajero
|
|-> procesarDatos
    |
    |-> compararLineas
*/
}
