------------------------------------------------
                 CONSIGNA
------------------------------------------------

-----------------------
Informaci�n disponible
------------------------

estaciones.csv: id, estacion, linea
molinetes.csv: fecha, desde, hasta, estacion_id, pasajeros


---------------------
Queries solicitados
---------------------

Query 1: Pasajeros por l�nea. Imprime nombre_linea, cant_pasajeros, en orden descendente.
Query 2: Pasajeros por d�a semanal y por per�odo. Imprime d�a, diurnos, nocturnos, total, en orden semanal.
Query 3: Porcentaje de pasajeros por l�nea. Imprime nombre_linea, porcentaje, en orden descendente.
Query 4: Estaci�n con m�s pasajeros por l�nea. Imprime estaci�n, l�nea, pasajeros, en orden alfab�tico de l�neas.




------------------------------------------------
                 SOLUCI�N
------------------------------------------------

--------------
TAD Propuesto
--------------

Transporte
|
|-> tlinea *lineas_list        // Lista, orden alfab�tico
|-> tlinea **lineas_vec        // Vector, orden descendente
|-> testacion *estaciones
|-> int[7] pas_sem_diurnos     // Dom->Sab
|-> int[7] pas_sem_diarios     // Dom->Sab
|-> int pasajeros_totales


Testacion
|
|-> int id
|-> char *nombre
|-> tlinea *linea
|-> int pasajeros_totales


Tlinea
|
|-> char *nombre
|-> int pasajeros_totales
|-> tstation *max_estacion
|-> tlinea *next_linea



-----------------------
Procesamiento de datos
-----------------------

Lectura de estaciones.csv:
- Creaci�n de l�neas (ord. alf) y estaciones (s/ord.)

Lectura de molinetes.csv:
- transporte->estaciones[estacion_id]->pasajeros_totales
- transporte->pas_sem_diurnos/nocturnos

Post-lecturas:
- Escribir en transporte[lineas_descendente] el orden descendente por pasajeros de l�neas
- Recorrer todas las estaciones y actualizaar el transporte->linea->max_estacion


-----------------------
Atenci�n de queries
-----------------------
Query 1:
Query 2:
Query 3:
Query 4: