#ifndef CONSUMO_H_INCLUDED
#define CONSUMO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define AR_CONSUMOS "consumos.dat"


typedef struct{
    int idConsumo; /// campo �nico y autoincremental
    int idCliente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a � dependiendo del mes
    int datosConsumidos; /// expresados en mb.
    int baja; /// 0 si est� activo - 1 si est� de baja
}stConsumo;

int buscaPosConsumos(int id);
void modificarConsumo(stConsumo c);
void agregarUnConsumo(stConsumo c);
int ultimoIdConsumos();
void mostrarUnConsumo(stConsumo c);


#endif // CONSUMO_H_INCLUDED
