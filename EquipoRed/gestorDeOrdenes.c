#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"


/*Abre base de datos de �rdenes en csv*/
orden *abrirBDOrdenes() {

 FILE *bddocsv;
    bddocsv = fopen("ordenes.csv", "r");

    if (bddocsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; //guarda las primeras 1024 l�neas en un buffer
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
    return listaO;

}


/*Inicializa un arreglo din�mico de �rdenes*/
DynaOrden *dynaOrden(orden listaDeOrdenes[100]) {

    DynaOrden *ordenesL = (DynaOrden *) malloc(sizeof(DynaOrden));
    ordenesL->tamano = 0;
    ordenesL->capacidad = 100;
    ordenesL->ordenes = (orden *) malloc(ordenesL->capacidad * sizeof(orden));
    for (int i = 0; i < ordenesL->capacidad; i++) {
        ordenesL->ordenes[i] = listaDeOrdenes[i];
        if (strcmp(listaDeOrdenes[i].codigoOrden, "")) {
            ordenesL->tamano++;
        } 
    }

    return ordenesL;
};

/*Devuelve la orden en el indice i*/
orden valorOrd(int i, const DynaOrden *dynaOrden) {
    if (dynaOrden->tamano <= i) {
        printf("Indice %d fuera del rango de valores de la base de datos\n", i);
    } else {
        return dynaOrden->ordenes[i];
    }

}

/*Cambia el valor de la orden en el indice i*/
void dynaCambValOrd(int i, DynaOrden *dynaOrden, orden cambio) {
    if (dynaOrden->tamano <= i) {
        printf("Indice %d fuera del rango de valores de la base de datos\n", i);
        return;
    }

    dynaOrden->ordenes[i] = cambio;
}

/*Esta funcion devuelve todas las ordenes, sólo usar en modo admin*/
orden *ordGuardadas(const DynaOrden *dynaOrden) {
    return dynaOrden->ordenes;
}

/*Devuelve la capacidad de la lista de ordenes*/
int ordCap(const DynaOrden *dynaOrden) {
    return dynaOrden->capacidad;
}

/*Devuelve el tamano de la lista de ordenes*/
int ordTam(const DynaOrden *dynaOrden) {
    return dynaOrden->tamano;
}

/*Libera memoria ue contiene arreglo dinamico de ordenes*/
void remDynaOrden(DynaOrden **dynaOrden) {
    
    free((*dynaOrden)->ordenes);
    (*dynaOrden)->ordenes = NULL;
    free(*dynaOrden);
    *dynaOrden = NULL;

}

/*Inserta ordenes desde el indice del ultimo elemento de la lista de ordenes*/
void dynaInsOrd(DynaOrden *dynaOrden, int N, orden *nueva) {
    int tam = ordTam(dynaOrden);
    int cap = ordCap(dynaOrden);
    if (cap-tam < N) {
        orden ordenes[tam];
        for (int i = 0; i < tam; i++) {
            ordenes[i] = dynaOrden->ordenes[i];
        }
        remDynaOrden(&dynaOrden);
        DynaOrden *dynaOrden = (DynaOrden *) malloc(sizeof(DynaOrden));
        dynaOrden->capacidad = cap + N;
        dynaOrden->tamano = tam + N;
        dynaOrden->ordenes = (orden *) malloc((cap + N) * sizeof(orden));
        for (int i = 0; i < tam + N; i++) {
            if (i < tam) {
                dynaOrden->ordenes[i] = ordenes[i];
            } else {
                dynaOrden->ordenes[i] = nueva[i];
            }
        }
    }
}

/*Elimina la orden en el indice i de la lista*/
void elimOrden(DynaOrden *dynaOrden, int pos) {
    int tam = ordTam(dynaOrden);
    orden ordenNula;
    ordenNula.cantidad = 0;
    strcpy(ordenNula.codigoCliente,'\0');
    strcpy(ordenNula.codigoOrden, '\0');
    ordenNula.codigoProducto;
    ordenNula.descuento = 0;

    if (pos >= tam) {
        printf("Se debe seleccionar un índice dentro del rango de la lista\n");
        return;
    }

    for (int i = pos; i < tam; i++) {
        if (i < tam - 1) {
            dynaCambValOrd(i, dynaOrden, dynaOrden->ordenes[i + 1]);
        } else {
            dynaOrden->ordenes[i] = ordenNula;
        }
    }
    dynaOrden->tamano = dynaOrden->tamano - 1;
}

/*Encuentra el indice de la string más cercano a la A*/
int indOrdAlfa(int i, int j, const char *a[]) {
  int pos = i;
  const char *min = a[pos];
  for (int k = i+1; k < j; ++k) {
    if (strcmp(a[k], min) < 0) {
      pos = k;
      min = a[pos];
    }
  }
  return pos;
}

/*Cambia la posición de dos ordenes*/
static void cambOrd(int i, int j, DynaOrden *dynaOrden) {
  orden tmp = dynaOrden->ordenes[i];
  dynaOrden->ordenes[i] = dynaOrden->ordenes[j];
  dynaOrden->ordenes[j] = tmp;
}

/*Reordena de menor a mayor las ordenes segun su codigo*/
void sortOrd(DynaOrden *dynaOrden) {
    int tam = dynaOrden->tamano;
    const char *tmp[tam] = {0};
    for (int i = 0; i < tam; i++) {
        tmp[i] = dynaOrden->ordenes[i].codigoOrden;
    }
    for (int i = 0; i < dynaOrden->tamano - 1; ++i) {
        int mindx = indOrdAlfa(dynaOrden->tamano - 1, i, tmp);
        printf("%d\n", mindx);
        cambOrd(i, mindx, dynaOrden);
    }
}

/*Por si acaso, función para concatenar dos listas de ordenes*/
DynaOrden *unirLisOrd(DynaOrden *dynaOrden1, DynaOrden *dynaOrden2) {
    int tam1 = ordTam(dynaOrden1);
    int tam2 = ordTam(dynaOrden2);
    int tamEq = tam1 + tam2;
    int cap1 = ordCap(dynaOrden1);
    int cap2 = ordCap(dynaOrden2);
    int capEq = cap1 + cap2;

    DynaOrden *resultado = (DynaOrden *) malloc(sizeof(DynaOrden));
    resultado->capacidad = capEq - tamEq;
    resultado->tamano = tamEq;
    resultado->ordenes = (orden *) malloc (capEq * sizeof(orden));
    for (int i = 0; i < tamEq; i++) {
        if (i < tam1) {
            resultado->ordenes[i] = dynaOrden1->ordenes[i];
        } else {
            resultado->ordenes[i] = dynaOrden2->ordenes[i - tam1];
        }
    }
    return resultado;
}


/*Crea una orden en la base de datos*/
int crearOrd(orden nuevo) {
    FILE *bddocsv;

    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());

    bddocsv = fopen("productos.csv", "w");

    if (bddocsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }


    for (int fila = 0; fila < count_o[0]+2; fila++) {

        if (fila == 0) {
            fprintf(bddocsv,
            "%s;%s;%s;%s;%s\n",
            "codigo cliente",
            "codigo producto",
            "codigo orden",
            "cantidad",
            "descuento");
        }

        if (fila < count_o[0] && fila > 0) {
            fprintf(bddocsv,
            "%s;%s;%s;%d;%d\n",
            listaO->ordenes[fila-1].codigoCliente,
            "\0",
            listaO->ordenes[fila-1].codigoOrden,
            listaO->ordenes[fila-1].cantidad,
            listaO->ordenes[fila-1].descuento);
        };

        if (fila == count_o[0]) {

            fprintf(bddocsv,
            "%s;%s;%s;%d;%d\n",
            nuevo.codigoCliente,
            nuevo.codigoProducto,
            "\0",
            nuevo.cantidad,
            nuevo.descuento);

        };

        if (ferror(bddocsv)) {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };

    };

    fclose(bddocsv);
    printf("Se agreg� exitosamente a la base de datos\n");
    return 0;
};

/*Agrega un producto a la orden determinada*/
void aggProducto(const char *codigoOrden, producto nuevo, DynaOrden *dynaOrden) {
    int tam = dynaOrden->tamano;
    for (int i = 0; i < tam; i++) {
        if (!strcmp(codigoOrden, dynaOrden->ordenes[i].codigoOrden)) {
            int j = 0;
            while(dynaOrden->ordenes[i].codigoOrden[j]) {
                strcpy(dynaOrden->ordenes[i].codigoProducto[i],dynaOrden->ordenes[i].codigoProducto[i]);
                j++;
                break;
            }
            if (!dynaOrden->ordenes[i].codigoOrden[j]) {
                strcpy(dynaOrden->ordenes[i].codigoProducto[i],nuevo.codigo);
            }   
        }
    }
}
