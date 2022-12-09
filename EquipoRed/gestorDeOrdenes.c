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
        printf("Error al abrir la base de datos\n");
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

            if (count_o[0] != 0)
            {

                if (column == 0)
                {
                    strcpy(listaO[i].codigoCliente, entrada);
                }

                else if (column == 1)
                {
                }

                else if (column == 2)
                {

                    strcpy(listaO[i].codigoOrden, entrada);
                }

                else if (column == 3)
                {
                }

                else if (column == 4)
                {
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

        if (count_o[0] >= 10)
        {

            i++;
        }
    };

    fclose(bddocsv);

    if (bddocsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    bddocsv = fopen("ordenes.csv", "r");

    count_o[0] = 0;

    while (fgets(buff, 1024, bddocsv))
    {
        count_o[0]++;
    }

    fclose(bddocsv);
    return listaO;
}

/*Inicializa un arreglo din�mico de �rdenes*/
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
    return ordenesL;
};

/*Carga los codigos de los productos de cada orden*/
const char *abrirProdPorOrd()
{

    FILE *bddPorOrd;
    bddPorOrd = fopen("codOrd.csv", "r");
    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());

    char ordProd[20][20][20];

    if (bddPorOrd == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }
    char buff[1024]; // guarda las primeras 1024 l�neas en un buffer
    int i = 0;
    int fila = 0;
    char cliFila[100][2][20];

    while (fgets(buff, 1024, bddPorOrd))
    {

        char *entrada = strtok(buff, ";"); // divide el buffer por entrada de datos
        i = 0;

        while (entrada)
        {

            switch (fila)
            {
            case 0:
                strcpy(cliFila[i][0], entrada);
                strcpy(cliFila[i][1], (const char *)fila);
                break;

            case 1:
                strcpy(ordProd[fila][i], entrada);
                break;

            case 2:
                strcpy(ordProd[fila][i], entrada);
                break;

            case 3:
                strcpy(ordProd[fila][i], entrada);
                break;

            case 4:
                strcpy(ordProd[fila][i], entrada);
                break;

            case 5:
                strcpy(ordProd[fila][i], entrada);
                break;

            case 6:
                strcpy(ordProd[fila][i], entrada);
                break;

            case 7:
                strcpy(ordProd[fila][i], entrada);
                break;

            default:
                strcpy(ordProd[fila][i], entrada);
                break;
            }
            fila++;
            entrada = strtok(NULL, ";");
        }
        i++;
    }
    fclose(bddPorOrd);
    for (int j = 0; j < fila; j++)
    {
        for (int k = 0; k < i; k++)
        {
            for (int x = 0; x < 100; x++)
            {
                if (!strcmp(cliFila[x][0], listaO[x].ordenes->codigoCliente))
                {
                    if (!strcmp(cliFila[x][1], (const char *)j))
                    {
                        strcpy(listaO[x].ordenes->productoOrden.codigoProd[fila], ordProd[fila][k]);
                    }
                }
            }
        }
    }
}

/*Devuelve la columna de productos de una orden*/
int columnOrd(DynaOrden *dynaOrden, char codOrd) {
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
    abrirProdPorOrd();
    abrirBDDClientes();
    abrirBDDProductos();
    fflush(stdin);
    printf("\n\nSolicitaremos los datos para agregar un nuevo producto:\n");

    /*do Comprobacion usuario está en base de datoss
    {

        strcpy(nueva.codigoCliente, clientes[count_c[0]].nombre);
        if (nueva.codigoCliente[1] != '\0')
        {
            nueva.codigoCliente[strcspn(nueva.codigoCliente, "\n")] = 0;
            n = 1;
            for (i = 0; i < 100; i++)
            {
                if (buscarCliente(nueva.codigoCliente, clientes))
                {
                    printf("\nEl usuario no se encuentra en nuestra base de datos\n");
                    n = 0;
                    i = 100;
                }
            }
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    } while (n < 1);*/


    do /*Comprobaci�n orden vacio*/
    {
        printf("\nIngrese codigo de la orden: ");
        fflush(stdout);
        fgets(nueva.codigoOrden, 20, stdin);
        fflush(stdin);
        // system ("cls");

        if (nueva.codigoOrden[1] != '\0')
        {
            nueva.codigoOrden[strcspn(nueva.codigoOrden, "\n")] = 0;
            n = 1;
            for (i = 0; i < 100; i++)
            {
                if (strcmp(nueva.codigoOrden, listaO->ordenes[i].codigoOrden))
                {
                    printf("\nEste codigo ya esta registrado\n");
                    n = 0;
                    i = 100;
                }
            }
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    } while (n < 1);

    do
    {
        mostrarBDDProductos();
        int numProductos;
        printf("\nIngrese cuantos tipos de producto desea: ");
        fflush(stdout);
        scanf("%d", &numProductos);
        fflush(stdin);

        for (int i = 0; i < numProductos; i++) {

            printf("\nIngrese cuales productos desea: ");
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
                n = 2;
            }
        }


        // system ("cls");
    } while (n < 1);


    do
    {
        /*printf("\nIngrese la cantidad del producto: ");
        fflush(stdout);
        scanf("%d", &nueva.productoOrden.cantidad);
        fflush(stdin);
        if (nueva.productoOrden.cantidad <= 0 || nueva.productoOrden.cantidad > (productos[buscarProducto(nueva.productoOrden.codigoProd[i], productos)].stock)) {
                printf("\nNo hay suficientes unidades\n");
                fflush(stdout);
                n = 0;
        }
        else
        {
            n = 2;
        };*/
        // system ("cls");
    } while (n < 1);

    nueva.descuento = 0;
    /*Comprobaci�n de descuento*/
    /*do
    {
        printf("\nIngrese la cantidad de productos disponibles: ");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &nuevo.stock);
        fflush(stdin);
        if (nuevo.stock < 0)
        {
            printf("\nOpcion invalida, intente de nuevo\n");
            n = 0;
        }
        else
        {
            n = 2;
        };
        // system ("cls");
    } while (n < 1);*/

    return nueva;
}

/*Guarda una orden en la base de datos*/
void guardarOrden(orden nueva)
{
    FILE *bddOrd;
    bddOrd = fopen("codOrd.csv", "w");
    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());

    if (bddOrd == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return;
    }

    for (int fila = 0; fila < listaO->tamano + 2; fila++)
    {
        if (fila == 0)
        {
            fprintf(bddOrd,
                    "%s;%s;%s\n",
                    "Codigo cliente",
                    "Codigo orden",
                    "descuento");
        }
        else if (fila < listaO->tamano && fila > 0)
        {
            fprintf(bddOrd,
                    "%s;%s;%d;%d\n",
                    listaO[fila - 1].ordenes->codigoCliente,
                    listaO[fila - 1].ordenes->descuento);
        }
        else if (fila == listaO->tamano)
        {
            fprintf(bddOrd,
                    "%s;%d\n",
                    nueva.codigoCliente,
                    nueva.descuento);
        }
        else if (ferror(bddOrd))
        {
            printf("No se pudo agregar el cliente\n");
            return;
        }
    }
    fclose(bddOrd);
    printf("Se agreg� exitosamente a la base de datos\n");
    return;
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
    orden ordenNula;
    ///ordenNula.cantidad = 0;
    strcpy(ordenNula.codigoCliente, '\0');
    strcpy(ordenNula.codigoOrden, '\0');
    ordenNula.productoOrden.codigoProd; // No esta operando
    ordenNula.descuento = 0;

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
            dynaOrden->ordenes[i] = ordenNula;
        }
    }
    dynaOrden->tamano = dynaOrden->tamano - 1;
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
/*void aggProducto(const char *codigoOrden, producto nuevo, int cant, DynaOrden *dynaOrden) {
    int tam = dynaOrden->tamano;
    if (nuevo.stock >= cant) {
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
        int prod = buscarProducto(nuevo.codigo, productos);
        productos[prod].stock = productos[prod].stock - cant;
    } else {
        printf("No hay suficientes unidades de %s para tu pedido, intenta disminuyendo la cantidad\n", nuevo.descripcion);
    }
}*/

/*Crea una orden en la base de datos*/
int crearOrd(orden nuevo)
{
    FILE *bddocsv;

    DynaOrden *listaO = dynaOrden(abrirBDOrdenes());

    bddocsv = fopen("productos.csv", "w");

    if (bddocsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return 1;
    }

    for (int fila = 0; fila < count_o[0] + 2; fila++)
    {

        if (fila == 0)
        {
            fprintf(bddocsv,
                    "%s;%s;%s;%s;%s\n",
                    "codigo cliente",
                    "codigo producto",
                    "codigo orden",
                    "cantidad",
                    "descuento");
        }

        if (fila < count_o[0] && fila > 0)
        {
            fprintf(bddocsv,
                    "%s;%s;%s;%d;%d\n",
                    listaO->ordenes[fila - 1].codigoCliente,
                    "\0",
                    listaO->ordenes[fila - 1].codigoOrden,
                    "\0",
                    listaO->ordenes[fila - 1].descuento);
        };

        if (fila == count_o[0])
        {

            fprintf(bddocsv,
                    "%s;%s;%s;%d;%d\n",
                    nuevo.codigoCliente,
                    "\0",
                    listaO->ordenes[fila - 1].codigoOrden,
                    "\0",
                    nuevo.descuento);
        };

        if (ferror(bddocsv))
        {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };
    };

    fclose(bddocsv);
    printf("Se agreg� exitosamente a la base de datos\n");
    return 0;
}
