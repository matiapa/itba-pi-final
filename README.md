------------------------------------------------
                 CONSIGNA
------------------------------------------------

-----------------------
Información disponible
------------------------

estaciones.csv: id, estacion, linea
molinetes.csv: fecha, desde, hasta, estacion_id, pasajeros


---------------------
Queries solicitados
---------------------

Query 1: Pasajeros por línea. Imprime nombre_linea, cant_pasajeros, en orden descendente.
Query 2: Pasajeros por día semanal y por período. Imprime día, diurnos, nocturnos, total, en orden semanal.
Query 3: Porcentaje de pasajeros por línea. Imprime nombre_linea, porcentaje, en orden descendente.
Query 4: Estación con más pasajeros por línea. Imprime estación, línea, pasajeros, en orden alfabético de líneas.




------------------------------------------------
                 SOLUCIÓN
------------------------------------------------

--------------
TAD Propuesto
--------------

Transporte
|
|-> tlinea *lineas_list        // Lista, orden alfabético
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
- Creación de líneas (ord. alf) y estaciones (s/ord.)

Lectura de molinetes.csv:
- transporte->estaciones[estacion_id]->pasajeros_totales
- transporte->pas_sem_diurnos/nocturnos

Post-lecturas:
- Escribir en transporte[lineas_descendente] el orden descendente por pasajeros de líneas
- Recorrer todas las estaciones y actualizaar el transporte->linea->max_estacion


-----------------------
Atención de queries
-----------------------
Query 1:
Query 2:
Query 3:
Query 4: