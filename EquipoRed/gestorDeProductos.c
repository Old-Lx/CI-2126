#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"



/*Abre una base de datos de personas guardada en un archivo csv*/
producto *abrirBDDProductos() {


    FILE *bddpcsv;
    bddpcsv = fopen("productos.csv", "r");

    if (bddpcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; //guarda las primeras 1024 l�neas en un buffer
    int column = 0;
    int i = 0;
    count_p[0] = 0;
    char tempPrecio[20];

    while (fgets(buff, 1024, bddpcsv)) {

        char *entrada = strtok(buff, ";"); //divide el buffer por entrada de datos
        while (entrada) {

            if (count_p[0] != 0) {

                if (column == 0) {
                    strcpy(productos[i].codigo, entrada);
                }

                else if (column == 1) {
                    strcpy(productos[i].descripcion, entrada);
                }

                else if (column == 2) {

                    strcpy(tempPrecio, entrada);
                    productos[i].precio = atof(tempPrecio);
                }

                else if (column == 3) {
                    char tempStock[20];
                    strcpy(tempStock, entrada);
                    productos[i].stock = atoi(tempStock);
                };
            };
            column++;
            entrada = strtok(NULL, ";");
            count_p[0]++;
        };
        column = 0;

        if (count_p[0] >= 8) {

            i++;

        }

    };

    fclose(bddpcsv);

    bddpcsv = fopen("productos.csv", "r");

    count_p[0] = 0;

    while (fgets(buff, 1024, bddpcsv)) {
        count_p[0]++;
    }

    fclose(bddpcsv);
    return 0;
};

/*Devuelve un producto agregado*/
producto nuevoProducto() {
    int n,i;
    producto nuevo;
    abrirBDDProductos();
    printf("\n\nSolicitaremos los datos para agregar un nuevo producto:\n");

    do /*Comprobacion nombre vacio*/
    {   
        
        printf("\nIngrese codigo: ");
        fflush(stdout);
        fflush(stdin);
        fgets(nuevo.codigo, 20, stdin);
        fflush(stdin);
        if(nuevo.codigo[1] != '\0')
        {
            nuevo.codigo[strcspn(nuevo.codigo,"\n")] = 0;
            n = 1;
            for(i=0; i<100 ;i++){
                if(strcmp(nuevo.codigo,productos[i].codigo)==0){
                    printf("\nEste codigo ya esta registrado\n");
                    n=0;
                    i=100;
                }
            }         
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);

    /*A�adir comprobaci�n si no se encuentra en la base de datos*/

    do /*Comprobaci�n descripci�n vacio*/
    {
        printf("\nIngrese descripcion del producto: ");
        fflush(stdout);
        fgets(nuevo.descripcion, 145, stdin);
        fflush(stdin);
        //system ("cls");

        if(nuevo.descripcion[1] != '\0')
        {
            nuevo.descripcion[strcspn(nuevo.descripcion,"\n")] = 0;
            n = 1;
            for(i=0; i<100 ;i++){
                if(strcmp(nuevo.descripcion,productos[i].descripcion)==0){
                    printf("\nEsta descripcion ya esta registrada\n");
                    n=0;
                    i=100;
                }
            }  
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    }while (n < 1);


    do{
        printf("\nIngrese el precio: ");
        fflush(stdout);
        scanf("%f",&nuevo.precio);
        fflush(stdin);
        if(nuevo.precio > 10){
            printf("\nEste precio no puede ingresar, intente de nuevo\n");
            fflush(stdout);
            n = 0;
        }else{
            n = 2;
        };
        //system ("cls");
    }while (n < 1);

    /*�Comprobaci�n de stock*/
    do{
        printf("\nIngrese la cantidad de productos disponibles: ");
        fflush(stdout);
        fflush(stdin);
        scanf("%d", &nuevo.stock);
        fflush(stdin);
        if(nuevo.stock > 10){
            printf("\nOpcion invalida, intente de nuevo\n");
            n = 0;
        }else{
            n = 2;
        };
        //system ("cls");
    }while (n < 1);

    return nuevo;
}


/*Guarda un producto en la base de datos*/
int guardarProducto(producto nuevo) {
    FILE *bddpcsv;

    abrirBDDProductos();

    bddpcsv = fopen("productos.csv", "w");

    if (bddpcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }


    for (int fila = 0; fila < count_p[0]+2; fila++) {

        if (fila == 0) {
            fprintf(bddpcsv,
            "%s;%s;%s;%s\n",
            "codigo",
            "descripcion",
            "precio",
            "stock");
        }

        if (fila < count_p[0] && fila > 0) {
            fprintf(bddpcsv,
            "%s;%s;%f;%d\n",
            productos[fila-1].codigo,
            productos[fila-1].descripcion,
            productos[fila-1].precio,
            productos[fila-1].stock);
        };

        if (fila == count_p[0]) {

            fprintf(bddpcsv,
            "%s;%s;%f;%d",
            nuevo.codigo,
            nuevo.descripcion,
            nuevo.precio,
            nuevo.stock);

        };

        if (ferror(bddpcsv)) {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };

    };

    fclose(bddpcsv);
    printf("Se agreg� exitosamente a la base de datos\n");
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
                do /*Comprobaci�n nombre vacio*/
        {
                printf("\nIngrese nuevo c�digo:\n");
                fgets(productos[count_p[0]].codigo, 20, stdin);
                fflush(stdin);
        if(productos[count_p[0]].codigo != '\0')
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
        printf("\nIngrese nueva descripci�n del producto:\n");
        fgets(productos[count_p[0]].descripcion, 145, stdin);
        fflush(stdin);
        //system ("cls");

        if(productos[count_p[0]].descripcion[1] != '\0')
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
        scanf("%f",&productos[count_p[0]].precio);
        if(productos[count_p[0]].precio <= 0){
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
            do{/*�Comprobaci�n de stock*/
        printf("\nIngrese la nueva cantidad de productos disponibles:\n");
        scanf("%i",&productos[count_p[0]].stock);
        if(productos[count_p[0]].stock <= 0){
            printf("\nOpci�n invalida, intente de nuevo");
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

/*Muestra base de datos del producto*/
void mostrarBDDProductos() {

    abrirBDDProductos();
    printf("\nCodigo\tDescripcion\tPrecio\t\tStock\n");
    for (int i = 0; i < count_p[0]-1; i++) {

        printf("%s\t%s\t\t%f\t%d\n",
        productos[i].codigo,
        productos[i].descripcion,
        productos[i].precio,
        productos[i].stock);
    }
}

/*Muestra base de datos de Clientes*/
void mostrarBDDClientes() {

    printf("Esta funci�n se encuentra en mantenimiento\n");
    abrirBDDClientes();
    for (int i = 0; i < count_c[0]-1; i++) {
        printf("****************\nUsuario [%i]\n", i);
        printf("Nombre: %s\nCorreo: %s\nDireccion: %s\nTelefono: %lu\nModo de contacto Favorito: %s\n UserName: %s\n Clave: %s\nFecha de Nacimeinto: %s\n Lugar de nacimiento: %s\nGenero: %s\n\n",
        clientes[i].nombre,
        clientes[i].correo,
        clientes[i].direccion,
        clientes[i].telefono,
        clientes[i].contactof,
        clientes[i].username,
        clientes[i].clave,
        clientes[i].fechaNacimiento,
        clientes[i].lugarNacimiento,
        clientes[i].genero);

    }
}

/*Ejecuta una operación para un administrador*/
void operacionProductos() {
    
    int accionCliente,n;
    do{
        printf("\nQue desea hacer?\n [1] Ver catalogo de productos\n [2] Modificar un producto\n [3] Agregar un producto\n [4] Ver clientes\n [5] Salir\nIngrese su respuesta: ");
        fflush(stdout);
        scanf("%i", &accionCliente);
        fflush(stdout);
        fflush(stdin);
        switch (accionCliente)
        {
        case 1: mostrarBDDProductos();n=0 ;break;
        case 2: modificarProducto(); n=0 ;break; //Por completar
        case 3: guardarProducto(nuevoProducto()); fflush(stdout);n=0 ;break; //Por completar comprobación
        case 4: mostrarBDDClientes(); n=0 ;break; 
        case 5: n=1; break;
        default: printf("\n\nOpcion invalida\n"); n=0 ;break;
        }
    }while(n==0);
 
}

void ingresarAdmin() {

    int n = 0;
    int operacion;
    do
    {
        printf("\nDeseas realizar alguna operacion?\n [1] Si \n [2] No\nIngrese su respuesta: ");
        fflush(stdout);
        scanf("%i", &operacion);
        switch (operacion)
        {
        case 1: operacionProductos(); break;
        case 2: n=1; break;
        default: printf("\nOpcion invalida \n"); n=0; break;
        }

    } while (n == 0);
    
}
