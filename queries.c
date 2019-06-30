#include <stdio.h>
#define DIAS_SEMANA 7

int main()
{

	
	char * nombre_linea;
	long int pasajeros;
	get_linea(&nommbre_linea,&pasajeros,
}
void query1(transporteADT trans)
{
	char * nombre_linea;
        long int pasajeros;
	int cant_lineas=cant_lineas(trans);
	//conseguir cantidad de lineas de subte para saber cuantas lineas agregar al archivo.
	
	FILE *fptr=fopen("./query1.csv","w");
	//generar el archivo

	for (int i=0,i<cant_lineas,i++){
		get_linea(&nombre_linea,&pasajeros,i,trans);
		fprintf(fptr,"%s,%ld\n", nombre_linea, pasajeros);
		}
	//agregar linea por linea los dats al archivo
	
	fclose(fptr);
	//cerrar el archivo
	

}
void query2(transporteADT trans)
{
	char ** dias={"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
	long int dia,noche;
	

	FILE *fptr=fopen("./query2.csv","w");
	         //generar el archivo
	for (int i=0,i<DIAS_SEMANA,i++){
		get_pasajeros_dia(&dia,&noche,i,trans);
		fprintf(ftpr,"%s,%ld,%ld,%ld \n",dias[i],dia,noche,dia+noche);
	}
	//agregar cada linea al archivo
	fclose(fptr);
	//cerrar el archivo
}

void query3(transporteADT trans){


