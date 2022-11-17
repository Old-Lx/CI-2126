#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"


/*Abre base de datos de órdenes en csv*/
int abrirBDDOrdenes() {

 FILE *bddocsv;
    bddocsv = fopen("ordenes.csv", "r");

    if (bddocsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; //guarda las primeras 1024 líneas en un buffer
    int column = 0;
    int i = 0;
    count_o[0] = 0;
    char tempPrecio[20];

    while (fgets(buff, 1024, bddocsv)) {

        char *entrada = strtok(buff, ";"); //divide el buffer por entrada de datos
        while (entrada) {

            if (count_o[0] != 0) {

                if (column == 0) {
                    strcpy(listaO[i].codigoCliente, entrada);
                }

                else if (column == 1) {
                    strcpy(listaO[i].codigoProducto, entrada);
                }

                else if (column == 2) {

                    strcpy(listaO[i].codigoOrden, entrada);
                }

                else if (column == 3) {
                    char cant[20];
                    strcpy(cant, entrada);
                    listaO[i].cantidad = atoi(cant);
                }

                else if (column == 4) {
                    char descu[20];
                    strcpy(descu, entrada);
                    listaO[i].descuento = atoi(descu);
                }
            }
            column++;
            entrada = strtok(NULL, ";");
            count_o[0]++;
        };
        column = 0;

        if (count_o[0] >= 10) {

            i++;

        }

    };

    fclose(bddocsv);

    bddocsv = fopen("ordenes.csv", "r");

    count_o[0] = 0;

    while (fgets(buff, 1024, bddocsv)) {
        count_o[0]++;
    }

    fclose(bddocsv);
    return 0;

}


/*Inicializa un arreglo dinámico de órdenes*/
DynaOrden *dynaOrden(orden listaDeOrdenes[100]) {

    DynaOrden *ordenesL = (DynaOrden *) malloc(sizeof(DynaOrden));
    ordenesL->capacidad = 100;
    ordenesL->ordenes = (orden *) malloc(ordenesL->capacidad * sizeof(orden));
};
