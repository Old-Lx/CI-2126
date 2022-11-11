#include "gestorDeProductos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


producto *prueba[100];
producto productos[100];
int count[1];

/*Abre una base de datos de personas guardada en un archivo csv*/
producto *abrirBDDProductos() {


    FILE *bddpcsv;
    bddpcsv = fopen("productos.csv", "r");

    if (bddpcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; //guarda las primeras 1024 líneas en un buffer
    int column = 0;
    int i = 0;
    count[0] = 0;

    while (fgets(buff, 1024, bddpcsv)) {


        char *entrada = strtok(buff, ";"); //divide el buffer por entrada de datos

        while (entrada) {

            if (count[0] != 0) {


                if (column == 0) {
                    strcpy(productos[i-1].codigo, entrada);
                }

                else if (column == 1) {
                    strcpy(productos[i-1].descripcion, entrada);
                }

                else if (column == 2) {

                    char temp[20];
                    strcpy(temp, entrada);
                    productos[i-1].precio = (int) temp;
                }

                else if (column == 3) {
                    char tempStock[20];
                    strcpy(tempStock, entrada);
                    productos[i-1].stock = (int) tempStock;
                };


            entrada = strtok(NULL, ";");
            column++;
            count[0]++;
            };
        };

        column = 0;
        i++;

    };

    fclose(bddpcsv);

    bddpcsv = fopen("productos.csv", "r");

    count[0] = 0;

    while (fgets(buff, 1024, bddpcsv)) {
        count[0]++;
    }

    fclose(bddpcsv);
    return 0;
};

/*Devuelve un producto agregado*/
producto nuevoProducto() {
    int n,aux;
    producto nuevo;
    printf("Solicitaremos los datos para añadir un nuevo producto:\n");

    do /*Comprobación nombre vacio*/
    {
        printf("\nIngrese código:\n");
        fgets(nuevo.codigo, 20, stdin);
        nuevo.codigo[strcspn(nuevo.codigo,"\n")] = 0;
        fflush(stdin);
        //system ("cls");
        if(nuevo.codigo[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);

    /*Añadir comprobación si no se encuentra en la base de datos*/

    do /*Comprobación descripción vacio*/
    {
        printf("\nIngrese descripción del producto:\n");
        fgets(nuevo.descripcion, 145, stdin);
        nuevo.descripcion[strcspn(nuevo.descripcion,"\n")] = " ";
        fflush(stdin);
        //system ("cls");

        if(nuevo.descripcion[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);


    do{
        printf("\nIngrese el precio:\n");
        scanf("%f",&nuevo.precio);
        if(nuevo.precio <= 0){
            printf("\nEste precio no puede ingresar, intente de nuevo");
            aux = 0;
        }else{
            aux = 2;
        };
        fflush(stdin);
        //system ("cls");
    }while (aux < 1);

    do{/*¨Comprobación de stock*/
        printf("\nIngrese la cantidad de productos disponibles:\n");
        scanf("%i",&nuevo.stock);
        if(nuevo.stock <= 0){
            printf("\nOpción invalida, intente de nuevo");
            aux = 0;
        }else{
            aux = 2;
        };
        fflush(stdin);
        //system ("cls");
    }while (aux < 1);
    return nuevo;
}


/*Guarda un producto en la base de datos*/
int guardarProducto(producto nuevo) {

    FILE *bddpcsv;

    if (bddpcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }


    abrirBDDProductos();

    bddpcsv = fopen("productos.csv", "w");

    if (bddpcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }


    for (int fila = 0; fila < count[0]+2; fila++) {

        if (fila == 0) {
            fprintf(bddpcsv,
            "%s;%s;%s;%s\n",
            "codigo",
            "descripcion",
            "precio",
            "stock");
        }

        if (fila < count[0] && fila > 0) {
            fprintf(bddpcsv,
            "%s;%s;%f;%d",
            productos[fila-1].codigo,
            productos[fila-1].descripcion,
            productos[fila-1].precio,
            productos[fila-1].stock);
        };


        if (fila == count[0]) {

            if (productos[count[0]-1].codigo != NULL) {
            fprintf(bddpcsv, "%s;%s;%f;%d",
            nuevo.codigo,
            nuevo.descripcion,
            nuevo.precio,
            nuevo.stock);
            } else {

            fprintf(bddpcsv,
            "\n%s;%s;%f;%d",
            nuevo.codigo,
            nuevo.descripcion,
            nuevo.precio,
            nuevo.stock);

            };


        };

        if (ferror(bddpcsv)) {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };

    };

    fclose(bddpcsv);
    printf("Se agregó exitosamente a la base de datos\n");
    return 0;
};

/*Modifica un producto existente*/
int modificarProducto(){
    int cambio;
    int modificar, n, aux;
    printf("\nDesea modificar un producto?:\n [1] SI\n [2] NO\n");
    scanf("%d", &modificar);
    if (modificar==1)
    {
        do{

        printf("\nQue dato quiere modificar?:\n [1] Codigo\n [2] Descripcion\n [3] Precio\n [4] Stock\n");
        scanf("%d", &cambio);
        switch (cambio){
        case 1:
                do /*Comprobación nombre vacio*/
        {
                printf("\nIngrese nuevo código:\n");
                fgets(productos[count[0]].codigo, 20, stdin);
                fflush(stdin);
        if(productos[count[0]].codigo != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
        }while (n < 1);
            n=2;
            break;
        case 2:
            do
        {
        printf("\nIngrese nueva descripción del producto:\n");
        fgets(productos[count[0]].descripcion, 145, stdin);
        fflush(stdin);
        //system ("cls");

        if(productos[count[0]].descripcion[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
        }while (n < 1);
            n=2;
            break;
        case 3:
            do{
        printf("\nIngrese el nuevo precio:\n");
        scanf("%f",&productos[count[0]].precio);
        if(productos[count[0]].precio <= 0){
            printf("\nEste precio no puede ingresar, intente de nuevo");
            aux = 0;
        }else{
            aux = 2;
        };
        fflush(stdin);
        //system ("cls");
        }while (aux < 1);
            n=2;
            break;
        case 4:
            do{/*¨Comprobación de stock*/
        printf("\nIngrese la nueva cantidad de productos disponibles:\n");
        scanf("%i",&productos[count[0]].stock);
        if(productos[count[0]].stock <= 0){
            printf("\nOpción invalida, intente de nuevo");
            aux = 0;
        }else{
            aux = 2;
        };
        fflush(stdin);
        //system ("cls");
    }while (aux < 1);
            n=2;
            break;
        default:
            printf("\nNo es una de las opciones");
            n=0;
            }
        } while (n<1 );

    }
        return 0;

}
