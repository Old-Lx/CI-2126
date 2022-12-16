#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"

/*Abre base de datos de �rdenes en csv*/
orden *abrirBDOrdenes()
{

    FILE *bddocsv;
    bddocsv = fopen("ordenes.csv", "r");

    if (bddocsv == NULL)
    {
        printf("Error al abrir la base de datos de ordenes\n");
        return NULL;
    }

    char buff[1024]; // guarda las primeras 1024 l�neas en un buffer
    int column = 0;
    int i = 0;
    count_o[0] = 0;
    // char tempPrecio[20]; //No se Esta usando

    while (fgets(buff, 1024, bddocsv))
    {

        char *entrada = strtok(buff, ";"); // divide el buffer por entrada de datos
        while (entrada)
        {

            if (i != 0)
            {

                if (column == 0)
                {
                    strcpy(listaO[i - 1].codigoCliente, entrada);
                }

                else if (column == 1)
                {
                    strcpy(listaO[i -1].codigoOrden, entrada);
                }

                else if (column == 2)
                {
                    char descu[20];
                    strcpy(descu, entrada);
                    listaO[i - 1].descuento = atoi(descu);  
                }

                else if (column == 3)
                {
                    char precio[20];
                    strcpy(precio, entrada);
                    listaO[i -1].precio = atoi(precio);
                }

                else if (column == 4)
                {
                    strcpy(listaO[i -1].envio, entrada);
                }

                else if (column == 5)
                {
                    strcpy(listaO[i -1].pago, entrada);
                }

                else if (column == 6)
                {
                    strcpy(listaO[i -1].estado, entrada);
                }
            }
            column++;
            entrada = strtok(NULL, ";");
        };
        column = 0;
        count_o[0]++;
        i++;
    };

    fclose(bddocsv);

    bddocsv = fopen("ordenes.csv", "r");

    if (bddocsv == NULL)
    {
        printf("Error al abrir la base de datos de ordenes\n");
        return NULL;
    }

    count_o[0] = 0;

    while (fgets(buff, 1024, bddocsv))
    {
        count_o[0]++;
    }

    fclose(bddocsv);
    return listaO;
}

/*Inicializa un arreglo dinamico de ordenes*/
DynaOrden *dynaOrden(orden listaDeOrdenes[100])
{

    DynaOrden *ordenesL = (DynaOrden *)malloc(sizeof(DynaOrden));
    ordenesL->tamano = 0;
    ordenesL->capacidad = 100;
    ordenesL->ordenes = (orden *)malloc(ordenesL->capacidad * sizeof(orden));
    for (int i = 0; i < ordenesL->capacidad; i++)
    {
        ordenesL->ordenes[i] = listaDeOrdenes[i];
        if (strcmp(listaDeOrdenes[i].codigoOrden, ""))
        {
            ordenesL->tamano++;
        }
    }
    printf("                         ");
    return ordenesL;
};

/*Carga los codigos de los productos de cada orden*/
const char *abrirProdPorOrd(DynaOrden *listaO)
{

    FILE *bddPorOrd;
    bddPorOrd = fopen("codOrdenes.csv", "r");

    if (bddPorOrd == NULL)
    {
        printf("Error al abrir la base de datos de cantidad de productos\n");
        return NULL;
    }
    char buff[1024]; // guarda las primeras 1024 lineas en un buffer
    int col = 0;
    int indOrden;
    int numProd;
    int count = 0;
    while (fgets(buff, 1024, bddPorOrd)) {
        
        char *entrada = strtok(buff, ";"); // divide el buffer por entrada de datos
        
        while (entrada) {
            if (count > 1) {
                if (col % 2 == 0) {

                    if (!strcmp(listaO->ordenes[indOrden - 1].codigoOrden, entrada) && indOrden > 0) {
                        numProd++;
                    } else {
                        numProd = 0;
                    }
                    indOrden = atoi(entrada);

                } else {
                    char *codCant = strtok(entrada, ",");
                    for (int i = 0; i < 2; i++) {
                        if (i == 0) { 
                            strcpy(listaO->ordenes[indOrden - 1].productoOrden.codigoProd[numProd], codCant);
                        } else {
                            listaO->ordenes[indOrden - 1].productoOrden.cantidad[numProd] = atoi(codCant);
                            listaO->ordenes[indOrden - 1].cantTipProd++;
                        }
                        codCant = strtok(NULL, ",");
                    }
                }
                col++;
            }
            entrada = strtok(NULL, ";");
            count++;
        }
    }
    fclose(bddPorOrd);
}

/*Actualiza BD de ordenes*/
void actualizarBDOrdenes() {
    FILE *bddocsv;

    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());
    abrirProdPorOrd(listaO);
    int tam = listaO->tamano;

    bddocsv = fopen("ordenes.csv", "w");

    if (bddocsv == NULL)
    {
        printf("Error al abrir la base de datos ordenes\n");
        return;
    }

    for (int fila = 0; fila < count_o[0] + 2; fila++)
    {

        if (fila == 0) {

            fprintf(bddocsv,
                    "%s;%s;%s;%s;%s;%s;%s\n",
                    "codigo cliente",
                    "codigo orden",
                    "descuento",
                    "precio",
                    "envio",
                    "pago",
                    "estado");
        }

        if (fila < count_o[0] && fila > 0) {

            fprintf(bddocsv,
                    "%s;%s;%d;%d;%s;%s;%s",
                    listaO->ordenes[fila - 1].codigoCliente,
                    listaO->ordenes[fila - 1].codigoOrden,
                    listaO->ordenes[fila - 1].descuento,
                    listaO->ordenes[fila - 1].precio,
                    listaO->ordenes[fila - 1].envio,
                    listaO->ordenes[fila - 1].pago,
                    listaO->ordenes[fila - 1].estado);
        };

        if (ferror(bddocsv))
        {
            printf("No se pudo agregar la orden\n");
            return;
        };
    };

    fclose(bddocsv);

    /*Guardado de la cantidad de cada producto*/
    FILE *bddordcant;

    bddordcant = fopen("codOrdenes.csv", "w");

    if (bddordcant == NULL) {
        printf("Error al abrir la base de datos con la cantidad de productos\n");
        return;
    }

    for (int fila = 0; fila < count_o[0]; fila++) {
        switch (fila) {
        case 0:
            fprintf(bddordcant,
                    "%s;%s,%s\n",
                    "Codigo de orden",
                    "Codigo de producto",
                    "Cantidad");
            break;
        
        default:
            for (int j = 0; j < listaO->ordenes[fila - 1].cantTipProd; j++) {
                fprintf(bddordcant,"%s;%s,%d\n",
                listaO->ordenes[fila - 1].codigoOrden,
                listaO->ordenes[fila - 1].productoOrden.codigoProd[j],
                listaO->ordenes[fila - 1].productoOrden.cantidad[j]);
            }
            break;
        }
    }

    fclose(bddordcant);

    printf("\n\nSe agrego exitosamente a la base de datos\n");
    return;
}

/*Devuelve la columna de productos de una orden*/
int columnOrd(DynaOrden *dynaOrden, char *codOrd) {
    for (int i = 0; i < dynaOrden->tamano; i++) {
        for (int j = 0; j < 20; j++) {
            if (!strcmp(dynaOrden->ordenes[i].productoOrden.codigoProd[0], codOrd)) {
                return j;
            }
        }
    }
}

/*Crea orden nueva*/
orden nuevaOrden() {
    int n, i;
    orden nueva;
    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());
    abrirProdPorOrd(listaO);
    ///abrirBDDClientes();
    abrirBDDProductos();
    fflush(stdin);
    printf("\n\nSolicitaremos los datos para agregar un nuevo producto:\n");


    do
    {
        /*for (int i = 0; i < listaO->capacidad; i++) {
            if (i == listaO->tamano && listaO->tamano < listaO->capacidad) {
                strcpy(nueva.codigoOrden, (char *) (atoi(listaO->ordenes[i].codigoOrden) + 1));
            } else {
                printf("No hay espacio para mas ordenes\n");
            }
        }*/
        int numProductos;
        printf("\nIngrese cuantos tipos de producto desea: ");
        fflush(stdout);
        scanf("%d", &numProductos);
        nueva.cantTipProd = numProductos;
        fflush(stdin);

        for (int i = 0; i < numProductos; i++) {

            printf("\nIngrese codigo de producto desea: ");
            fflush(stdout);
            fgets(nueva.productoOrden.codigoProd[i], 20, stdin);
            fflush(stdin);
            if (buscarProducto(nueva.productoOrden.codigoProd[i], productos))
            {
                printf("\nEse producto no se encuentra disponible\n");
                fflush(stdout);
                n = 0;
            }
            else
            {
                printf("\nIngrese cantidad que desea de [%s]: \n",
                productos[atoi(nueva.productoOrden.codigoProd[i]) - 1].descripcion);
                fflush(stdout);
                char tempCant[20];
                fgets(tempCant, 20, stdin);
                nueva.productoOrden.cantidad[i] = atoi(tempCant);
                fflush(stdin);
                if (productos[atoi(nueva.productoOrden.codigoProd[i]) - 1].stock < nueva.productoOrden.cantidad[i])
                {
                    printf("\nNo hay suficiente [%s] disponible\n", productos[atoi(nueva.productoOrden.codigoProd[i]) - 1].descripcion);
                    fflush(stdout);
                    n = 0;
                } else {
                    productos[atoi(nueva.productoOrden.codigoProd[i]) - 1].stock = productos[atoi(nueva.productoOrden.codigoProd[i]) - 1].stock - nueva.productoOrden.cantidad[i];
                    nueva.precio = nueva.precio + (productos[atoi(nueva.productoOrden.codigoProd[i]) - 1].precio * nueva.productoOrden.cantidad[i]);
                    actualizarBDProductos();
                    n = 2;
                }
            }
        }
        // system ("cls");
    } while (n < 1);

    nueva.descuento = 0;
    /*Comprobacion de descuento*/
    do
    {
        printf("\nPosee codigo de descuento?\n[1]Si\n[2]No\n ");
        fflush(stdout);
        int resp;
        scanf("%d", &resp);
        fflush(stdin);
        switch (resp) {
        case 1:
            printf("\nInserte su codigo de descuento\n");
            fflush(stdout);
            char codDescuento[20];
            scanf("%s", codDescuento);
            fflush(stdin);
            ///falta desarrollar función que chequee base de datos con
            ///códigos de descuento y confirme la exitencia del mismo
            printf("Código inválido");
            n = 0;
            break;

        case 2:
            n = 2;
            break;
        
        default:
            printf("Inserte una opción válida\n");
            n = 0;
            break;
        }
        // system ("cls");
    } while (n < 1);

    do {

        printf("\nSeleccione metodo para recibir sus productos\n[0]Pickup\n[1]Envio local\n[2]Envio nacional\n[3]Envio internacional\n");
        fflush(stdout);
        int resp;
        scanf("%d", &resp);
        fflush(stdin);
        switch (resp) {
        case 0:
            printf("\nHa seleccionado Pickup\n");
            strcpy(nueva.envio,"0");
            fflush(stdout);
            n = 2;
            break;

        case 1:
            printf("\nHa seleccionado Envio local\nPor favor, elija lugar donde desea recibir sus productos\n[1]Mi casa\n[2]Indique cual\n");
            fflush(stdout);
            strcpy(nueva.envio,"1");
            char lugar[20];
            scanf("%s", lugar);
            fflush(stdin);
            n = 2;
            break;
        
        case 2:
            printf("\nHa seleccionado Envio nacional\nPor favor, elija lugar donde desea recibir sus productos\n[1]Mi casa\n[2]Indique cual\n");
            fflush(stdout);
            strcpy(nueva.envio,"2");
            scanf("%s", lugar);
            fflush(stdin);
            n = 2;
            break;

        case 3:
            printf("\nHa seleccionado Envio internacional\nPor favor, elija tipo de transporte para sus productos\n[0]Terrestre\n[2]Maritimo\n[3]Aereo\n");
            fflush(stdout);
            strcpy(nueva.envio,"3");
            char trans[20];
            scanf("%s", trans);
            fflush(stdin);
            n = 2;
            break;
        
        default:
            printf("Inserte una opción válida\n");
            n = 0;
            break;
        }

    } while (n < 1);

    strcpy(nueva.estado,"0");

    do {
       printf("\nSeleccione metodo de pago\n[0]Efectivo\n[1]Debito\n[2]Credito\n[3]Billetera de la app\n");
        fflush(stdout);
        int resp;
        scanf("%d", &resp);
        fflush(stdin); 
        switch (resp) {
        case 0:
            printf("\nHa seleccionado Efectivo\n");
            strcpy(nueva.pago,"0");
            fflush(stdout);
            n = 2;
            break;
        
        case 1:
            printf("\nHa seleccionado Debito\n");
            strcpy(nueva.pago,"1");
            fflush(stdout);
            n = 2;
            break;
        
        case 2:
            printf("\nHa seleccionado Credito\n");
            strcpy(nueva.pago,"1");
            fflush(stdout);
            n = 2;
            break;

        case 3:
            printf("\nHa seleccionado Billetera de la app\n");
            strcpy(nueva.pago,"1");
            strcpy(nueva.estado,"1");
            fflush(stdout);
            n = 2;
            break;
        }

    } while (n < 1);

    return nueva;
}

/*Devuelve la orden en el indice i*/
orden valorOrd(int i, const DynaOrden *dynaOrden)
{
    if (dynaOrden->tamano <= i)
    {
        printf("Indice %d fuera del rango de valores de la base de datos\n", i);
    }
    else
    {
        return dynaOrden->ordenes[i];
    }
}

/*Cambia el valor de la orden en el indice i*/
void dynaCambValOrd(int i, DynaOrden *dynaOrden, orden cambio)
{
    if (dynaOrden->tamano <= i)
    {
        printf("Indice %d fuera del rango de valores de la base de datos\n", i);
        return;
    }

    dynaOrden->ordenes[i] = cambio;
}

/*Esta funcion devuelve todas las ordenes, sólo usar en modo admin*/
orden *ordGuardadas(const DynaOrden *dynaOrden)
{
    return dynaOrden->ordenes;
}

/*Devuelve la capacidad de la lista de ordenes*/
int ordCap(const DynaOrden *dynaOrden)
{
    return dynaOrden->capacidad;
}

/*Devuelve el tamano de la lista de ordenes*/
int ordTam(const DynaOrden *dynaOrden)
{
    return dynaOrden->tamano;
}

/*Libera memoria ue contiene arreglo dinamico de ordenes*/
void remDynaOrden(DynaOrden **dynaOrden)
{

    free((*dynaOrden)->ordenes);
    (*dynaOrden)->ordenes = NULL;
    free(*dynaOrden);
    *dynaOrden = NULL;
}

/*Inserta ordenes desde el indice del ultimo elemento de la lista de ordenes*/
void dynaInsOrd(DynaOrden *dynaOrden, int N, orden *nueva)
{
    int tam = ordTam(dynaOrden);
    int cap = ordCap(dynaOrden);
    if (cap - tam < N)
    {
        orden ordenes[tam];
        for (int i = 0; i < tam; i++)
        {
            ordenes[i] = dynaOrden->ordenes[i];
        }
        remDynaOrden(&dynaOrden);
        DynaOrden *dynaOrden = (DynaOrden *)malloc(sizeof(DynaOrden));
        dynaOrden->capacidad = cap + N;
        dynaOrden->tamano = tam + N;
        dynaOrden->ordenes = (orden *)malloc((cap + N) * sizeof(orden));
        for (int i = 0; i < tam + N; i++)
        {
            if (i < tam)
            {
                dynaOrden->ordenes[i] = ordenes[i];
            }
            else
            {
                dynaOrden->ordenes[i] = nueva[i];
            }
        }
    }
}

/*Elimina la orden en el indice i de la lista*/
void elimOrden(DynaOrden *dynaOrden, int pos)
{
    int tam = ordTam(dynaOrden);

    if (pos >= tam)
    {
        printf("Se debe seleccionar un índice dentro del rango de la lista\n");
        return;
    }

    for (int i = pos; i < tam; i++)
    {
        if (i < tam - 1)
        {
            dynaCambValOrd(i, dynaOrden, dynaOrden->ordenes[i + 1]);
        }
        else
        {
            for (int j = 0; j < dynaOrden->ordenes[i].cantTipProd; j++) {
                strcpy(dynaOrden->ordenes[i].productoOrden.codigoProd[j], "/0");
                dynaOrden->ordenes[i].productoOrden.cantidad[j] = 0;
            }
            printf("%s\n", dynaOrden->ordenes[i].codigoCliente);
            strcpy(dynaOrden->ordenes[i].codigoCliente, "/0");
            strcpy(dynaOrden->ordenes[i].codigoOrden, "/0");
            strcpy(dynaOrden->ordenes[i].envio, "/0");
            strcpy(dynaOrden->ordenes[i].estado, "/0");
            strcpy(dynaOrden->ordenes[i].pago, "/0");
            dynaOrden->ordenes[i].descuento = 0;
            dynaOrden->ordenes[i].precio = 0;
        }
    }
    dynaOrden->tamano = dynaOrden->tamano - 1;
    actualizarBDOrdenes();
}

/*Encuentra el indice de la string más cercano a la A*/
int indOrdAlfa(int i, int j, const char *a[])
{
    int pos = i;
    const char *min = a[pos];
    for (int k = i + 1; k < j; ++k)
    {
        if (strcmp(a[k], min) < 0)
        {
            pos = k;
            min = a[pos];
        }
    }
    return pos;
}

/*Encuentra el indice de la string que se elija*/
int indOrd(int i, DynaOrden *listaO)
{
    int pos = i;
    orden min = listaO->ordenes[pos];
    for (int k = i; k < listaO->tamano; ++k)
    {
        if (!strcmp(listaO->ordenes[k].codigoOrden, min.codigoOrden))
        {
            pos = k;
            min = listaO->ordenes[k];
            return pos;
            break;
        } else {
            return -1;
        }
    }
}

/*Cambia la posición de dos ordenes*/
void cambOrd(int i, int j, DynaOrden *dynaOrden)
{
    orden tmp = dynaOrden->ordenes[i];
    dynaOrden->ordenes[i] = dynaOrden->ordenes[j];
    dynaOrden->ordenes[j] = tmp;
}

/*Reordena de menor a mayor las ordenes segun su codigo*/
void sortOrd(DynaOrden *dynaOrden)
{
    int tam = dynaOrden->tamano;
    const char *tmp[tam]; //= {0};
    for (int i = 0; i < tam; i++)
    {
        tmp[i] = dynaOrden->ordenes[i].codigoOrden;
    }
    for (int i = 0; i < dynaOrden->tamano - 1; ++i)
    {
        int mindx = indOrdAlfa(dynaOrden->tamano - 1, i, tmp);
        printf("%d\n", mindx);
        cambOrd(i, mindx, dynaOrden);
    }
}

/*Por si acaso, función para concatenar dos listas de ordenes*/
DynaOrden *unirLisOrd(DynaOrden *dynaOrden1, DynaOrden *dynaOrden2)
{
    int tam1 = ordTam(dynaOrden1);
    int tam2 = ordTam(dynaOrden2);
    int tamEq = tam1 + tam2;
    int cap1 = ordCap(dynaOrden1);
    int cap2 = ordCap(dynaOrden2);
    int capEq = cap1 + cap2;

    DynaOrden *resultado = (DynaOrden *)malloc(sizeof(DynaOrden));
    resultado->capacidad = capEq - tamEq;
    resultado->tamano = tamEq;
    resultado->ordenes = (orden *)malloc(capEq * sizeof(orden));
    for (int i = 0; i < tamEq; i++)
    {
        if (i < tam1)
        {
            resultado->ordenes[i] = dynaOrden1->ordenes[i];
        }
        else
        {
            resultado->ordenes[i] = dynaOrden2->ordenes[i - tam1];
        }
    }
    return resultado;
}

/*Agrega un producto a la orden determinada*/
void aggProducto(char *codigoOrden, char *productoCod, char *cant, DynaOrden *dynaOrden) {
    int tam = dynaOrden->tamano;
    int indOrd = buscarOrden(dynaOrden, codigoOrden);
    abrirProdPorOrd(dynaOrden);
    strcpy(dynaOrden->ordenes[indOrd].productoOrden.codigoProd[dynaOrden->ordenes[indOrd].cantTipProd], productoCod);
    strcpy(dynaOrden->ordenes[indOrd].productoOrden.codigoProd[dynaOrden->ordenes[indOrd].cantTipProd], cant);
    actualizarBDOrdenes();
}

/*Elimina cantidad cant de un producto en la orden escogida*/
void elimProducto(char *codigoOrden, char *productoCod, char *cant) {
    DynaOrden *ordenes = dynaOrden(abrirBDOrdenes());
    int tam = ordenes->tamano;
    int indOrd = buscarOrden(ordenes, codigoOrden);
    abrirProdPorOrd(ordenes);
    int cantidad;
    for (int i = 0; i < ordenes->ordenes[indOrd].cantTipProd; i++) {
        if (!strcmp(codigoOrden, ordenes->ordenes[indOrd].productoOrden.codigoProd[i])) {
            cantidad = ordenes->ordenes[indOrd].productoOrden.cantidad[i] - atoi(cant);
        }
        if (cantidad == 0 && i < ordenes->ordenes[indOrd].cantTipProd - 1) {
            strcpy(ordenes->ordenes[indOrd].productoOrden.codigoProd[i], ordenes->ordenes[indOrd].productoOrden.codigoProd[i + 1]);
            ordenes->ordenes[indOrd].productoOrden.cantidad[i] = ordenes->ordenes[indOrd].productoOrden.cantidad[i + 1];
        } else if (cantidad == 0 && i == ordenes->ordenes[indOrd].cantTipProd - 1) {
            strcpy(ordenes->ordenes[indOrd].productoOrden.codigoProd[i], "/0");
            ordenes->ordenes[indOrd].productoOrden.cantidad[i] = 0;
        }
    }
    actualizarBDOrdenes(); 
}

/*Busca la orden de un cliente x*/
int buscarOrden(DynaOrden *listaO, char *codOrdBuscada) {
    for (int i = 1; i < listaO->tamano; i++) {
        if (!strcmp(codOrdBuscada, listaO->ordenes[i].codigoOrden)) {
            return indOrd(i, listaO);
            break;
        } else if (strcmp(codOrdBuscada, listaO->ordenes[i].codigoOrden) && i == listaO->tamano) {
            return -1;
        }
    }
}

/*Guarda una orden en la base de datos*/
void guardarOrd(orden nuevo) {
    FILE *bddocsv;

    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());
    abrirProdPorOrd(listaO);
    int tam = listaO->tamano;

    bddocsv = fopen("ordenes.csv", "w");

    if (bddocsv == NULL)
    {
        printf("Error al abrir la base de datos ordenes\n");
        return;
    }

    for (int fila = 0; fila < count_o[0] + 2; fila++)
    {

        if (fila == 0) {

            fprintf(bddocsv,
                    "%s;%s;%s;%s;%s;%s;%s\n",
                    "codigo cliente",
                    "codigo orden",
                    "descuento",
                    "precio",
                    "envio",
                    "pago",
                    "estado");
        }

        if (fila < count_o[0] && fila > 0) {

            fprintf(bddocsv,
                    "%s;%s;%d;%d;%s;%s;%s",
                    listaO->ordenes[fila - 1].codigoCliente,
                    listaO->ordenes[fila - 1].codigoOrden,
                    listaO->ordenes[fila - 1].descuento,
                    listaO->ordenes[fila - 1].precio,
                    listaO->ordenes[fila - 1].envio,
                    listaO->ordenes[fila - 1].pago,
                    listaO->ordenes[fila - 1].estado);
        };

        if (fila == count_o[0])
        {

            fprintf(bddocsv,
                    "\n%s;%d;%d;%d;%s;%s;%s",
                    usuario,
                    tam + 1,
                    nuevo.descuento,
                    nuevo.precio,
                    nuevo.envio,
                    nuevo.pago,
                    nuevo.estado);
        }

        if (ferror(bddocsv))
        {
            printf("No se pudo agregar la orden\n");
            return;
        };
    };

    fclose(bddocsv);

    /*Guardado de la cantidad de cada producto*/
    FILE *bddordcant;

    bddordcant = fopen("codOrdenes.csv", "w");

    if (bddordcant == NULL) {
        printf("Error al abrir la base de datos con la cantidad de productos\n");
        return;
    }

    for (int fila = 0; fila < count_o[0]; fila++) {
        switch (fila) {
        case 0:
            fprintf(bddordcant,
                    "%s;%s,%s\n",
                    "Codigo de orden",
                    "Codigo de producto",
                    "Cantidad");
            break;
        
        default:
            for (int j = 0; j < listaO->ordenes[fila - 1].cantTipProd; j++) {
                fprintf(bddordcant,"%s;%s,%d\n",
                listaO->ordenes[fila - 1].codigoOrden,
                listaO->ordenes[fila - 1].productoOrden.codigoProd[j],
                listaO->ordenes[fila - 1].productoOrden.cantidad[j]);
            }
            break;
        }
        if (fila == count_o[0] - 1) {
            for (int j = 0; j < nuevo.cantTipProd; j++) {
            int tempCode = atoi(nuevo.productoOrden.codigoProd[j]);
            fprintf(bddordcant,"%d;%d,%d\n",
            tam + 1,
            tempCode,
            nuevo.productoOrden.cantidad[j]);
            }
        }
    }

    fclose(bddordcant);

    printf("\n\nSe agrego exitosamente a la base de datos\n");
    return;
}

/*Mostrar detalles de orden*/
void mostrarOrden(){
    int a=0;
    abrirBDOrdenes();
    for (int i = 0; i < 100; i++)
    {
        if(strcmp(clientes[num_fila[0]].username,listaO[i].codigoCliente)==0){

                printf("\n\nSu orden es la Numero: %s", listaO[i].codigoOrden );
                printf("\nPor el usuario: %s", listaO[i].codigoCliente);
                printf("\nTiene un descuento total de: %d", listaO[i].descuento);
                switch (atoi(listaO[i].envio))
                {
                case 0:printf("\nTipo de envio: Pickup");break;
                case 1:printf("\nTipo de envio: Local ");break;
                case 2:printf("\nTipo de envio: Nacional ");break;
                case 3:printf("\nTipo de envio: Internacional");break;
                default:break;
                }
                switch (atoi(listaO[i].pago))
                {
                case 0:printf("\nTipo de pago: Efectivo");break;
                case 1:printf("\nTipo de pago: Debito ");break;
                case 2:printf("\nTipo de pago: Credito ");break;
                case 3:printf("\nTipo de pago: Billetera digital ");break;
                default:break;
                }

                printf("\nPara un precio total de: %d\n", listaO[i].precio);



                a=1;
            }
    }
    if(a==0){printf("\n\nNo has realizado pedidos\n\n");}
}