#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"

/*Abre una base de datos de personas guardada en un archivo csv*/
producto *abrirBDDProductos()
{

    FILE *bddpcsv;
    bddpcsv = fopen("productos.csv", "r");

    if (bddpcsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; // guarda las primeras 1024 l�neas en un buffer
    int column = 0;
    int i = 0;
    count_p[0] = 0;
    char tempPrecio[20];

    while (fgets(buff, 1024, bddpcsv))
    {

        productos[i].posProd = i;
        char *entrada = strtok(buff, ";"); // divide el buffer por entrada de datos
        while (entrada)
        {

            if (count_p[0] != 0)
            {

                if (column == 0)
                {
                    strcpy(productos[i].codigo, entrada);
                }

                else if (column == 1)
                {
                    strcpy(productos[i].descripcion, entrada);
                }

                else if (column == 2)
                {

                    strcpy(tempPrecio, entrada);
                    productos[i].precio = atof(tempPrecio);
                }

                else if (column == 3)
                {
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

        if (count_p[0] >= 8)
        {

            i++;
        }
    };

    fclose(bddpcsv);

    bddpcsv = fopen("productos.csv", "r");

    count_p[0] = 0;

    while (fgets(buff, 1024, bddpcsv))
    {
        count_p[0]++;
    }

    fclose(bddpcsv);
    return 0;
};

/*Devuelve un producto agregado*/
producto nuevoProducto()
{
    int n, i;
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
        if (nuevo.codigo[1] != '\0')
        {
            nuevo.codigo[strcspn(nuevo.codigo, "\n")] = 0;
            n = 1;
            for (i = 0; i < 100; i++)
            {
                if (strcmp(nuevo.codigo, productos[i].codigo) == 0)
                {
                    printf("\nEste codigo ya esta registrado\n");
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
    } while (n < 1);

    /*A�adir comprobaci�n si no se encuentra en la base de datos*/

    do /*Comprobaci�n descripci�n vacio*/
    {
        printf("\nIngrese descripcion del producto: ");
        fflush(stdout);
        fgets(nuevo.descripcion, 145, stdin);
        fflush(stdin);
        // system ("cls");

        if (nuevo.descripcion[1] != '\0')
        {
            nuevo.descripcion[strcspn(nuevo.descripcion, "\n")] = 0;
            n = 1;
            for (i = 0; i < 100; i++)
            {
                if (strcmp(nuevo.descripcion, productos[i].descripcion) == 0)
                {
                    printf("\nEsta descripcion ya esta registrada\n");
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
        printf("\nIngrese el precio: ");
        fflush(stdout);
        scanf("%f", &nuevo.precio);
        fflush(stdin);
        if (nuevo.precio <= 0)
        {
            printf("\nEste precio no puede ingresar, intente de nuevo\n");
            fflush(stdout);
            n = 0;
        }
        else
        {
            n = 2;
        };
        // system ("cls");
    } while (n < 1);

    /*�Comprobaci�n de stock*/
    do
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
    } while (n < 1);

    return nuevo;
}

/*Devuelve el índice de un producto*/
int buscarProducto(const char codigo[20], producto productoL[100])
{

    int i = 0;
    while (strcmp(codigo, productoL[i].codigo))
    {

        printf("Buscando cliente...\n\n");
        i++;
        if (i == 100)
        {

            printf("El cliente no se encontró\n\n");
            return 0;
        }
    }

    if (!strcmp(codigo, productoL[i].codigo))
    {
        return productoL[i].posProd;
    }
    else
    {
        return -1;
    }
}

/*Guarda un producto en la base de datos*/
int guardarProducto(producto nuevo)
{
    FILE *bddpcsv;

    abrirBDDProductos();

    bddpcsv = fopen("productos.csv", "w");

    if (bddpcsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return 1;
    }

    for (int fila = 0; fila < count_p[0] + 2; fila++)
    {

        if (fila == 0)
        {
            fprintf(bddpcsv,
                    "%s;%s;%s;%s\n",
                    "codigo",
                    "descripcion",
                    "precio",
                    "stock");
        }

        if (fila < count_p[0] && fila > 0)
        {
            fprintf(bddpcsv,
                    "%s;%s;%f;%d\n",
                    productos[fila - 1].codigo,
                    productos[fila - 1].descripcion,
                    productos[fila - 1].precio,
                    productos[fila - 1].stock);
        };

        if (fila == count_p[0])
        {

            fprintf(bddpcsv,
                    "%s;%s;%f;%d",
                    nuevo.codigo,
                    nuevo.descripcion,
                    nuevo.precio,
                    nuevo.stock);
        };

        if (ferror(bddpcsv))
        {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };
    };

    fclose(bddpcsv);
    printf("Se agrego exitosamente a la base de datos\n");
    return 0;
};

/*Modifica un producto existente*/
int modificarProducto()
{
    int cambio;
    int modificar, n, aux, i, fila,compr;
    char nuevo[20];
    int nuevoStock;
    int dat=0;
    float nuevoPrecio;
    char actual[20];
    abrirBDDProductos();

    printf("\nCual es el codigo del producto que desea modificar?:\t");
    fgets(nuevo, 30, stdin);
    fflush(stdin);
    nuevo[strcspn(nuevo, "\n")] = 0;

    for (int fila = 0; fila < 100; fila++)
    {
        if (strcmp(nuevo, productos[fila].codigo) == 0)
        {
            printf("\nCodigo encontrado\n");
            count_p[1] = fila;
            compr = 1;
            printf("\nModificara el producto\t**%s**\n", productos[count_p[1]].descripcion);
            fila = 100;
        }else{
            compr=0;
        }
    }
    if (compr != 0)
    {

        do
        {
            printf("\nQue dato quiere modificar?\n [1] Descripcion\n [2] Precio\n [3] Stock\n [4] Regresar\n");
            scanf("%d", &cambio);
            fflush(stdin);
            switch (cambio)
            {
            /*case 1:
                do //Comprobacion nombre vacio
                {
                    printf("\nIngrese codigo: ");
                    fflush(stdout);
                    fflush(stdin);
                    fgets(nuevo, 20, stdin);
                    fflush(stdin);
                    if (nuevo != '\0')
                    {
                        nuevo[strcspn(nuevo, "\n")] = 0;
                        n = 1;
                        for (i = 0; i < 100; i++)
                        {
                            if (strcmp(nuevo, productos[i].codigo) == 0)
                            {
                                printf("\nEste codigo ya esta registrado\n");
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
                } while (n < 1);
                strcpy(productos[count_p[1]].codigo, nuevo);
                n = 2;
                break;*/
            case 1:
                do
                {
                    printf("\nIngrese nueva descripcion del producto:\n");
                    fgets(nuevo, 145, stdin);
                    fflush(stdin);
                    // system ("cls");

                    if (nuevo != '\0')
                    {
                        n = 1;
                    }
                    else
                    {
                        printf("\nNo puedes ingresar datos vacios");
                        n = 0;
                    }
                } while (n < 1);
                nuevo[strcspn(nuevo, "\n")] = 0;
                strcpy(productos[count_p[1]].descripcion, nuevo);
                n = 2;
                break;
            case 2:
                do
                {
                    printf("\nIngrese el nuevo precio:\n");
                    scanf("%f", &nuevoPrecio);
                    if (nuevoPrecio <= 0)
                    {
                        printf("\nEste precio no puede ingresar, intente de nuevo");
                        aux = 0;
                    }
                    else
                    {
                        aux = 2;
                    };
                    fflush(stdin);
                } while (aux < 1);
                productos[count_p[1]].precio = nuevoPrecio;
                n = 2;
                break;
            case 3:
                do
                { /*�Comprobaci�n de stock*/
                    printf("\nIngrese la nueva cantidad de productos disponibles:\n");
                    fflush(stdin);
                    scanf("%i", &nuevoStock);
                    if (nuevoStock <= 0)
                    {
                        printf("\nOpcion invalida, intente de nuevo");
                        aux = 0;
                    }
                    else
                    {
                        aux = 2;
                    };
                    fflush(stdin);
                    // system ("cls");
                } while (aux < 1);
                productos[count_p[1]].stock = nuevoStock;
                n = 2;
                break;
            case 4:
                n=2;
                break;
            default:
                printf("\nNo es una de las opciones");
                n = 0;
            }
        } while (n < 1);
        actualizarBDProductos();
        return 0;
    }
    else{
        printf("\nEste codigo no se encuentra registrado\n");//No esta entrando
        return 0;
    }
}

/*Muestra base de datos del producto*/
void mostrarBDDProductos()
{

    abrirBDDProductos();
    printf("\nCodigo\tDescripcion\tPrecio\t\tStock\n");
    for (int i = 0; i < count_p[0] - 1; i++)
    {

        printf("%4s\t%10s\t%.2f\t\t%4d\n",
               productos[i].codigo,
               productos[i].descripcion,
               productos[i].precio,
               productos[i].stock);
    }
}

/*Muestra base de datos del producto*/
void mostrar10Productos()
{
    int p=0,opcion,a=10;
    do{
    abrirBDDProductos();
    printf("\n\nCodigo\tDescripcion\tPrecio\t\tStock\n");
    for (int i = p; i < p+a; i++)
    {

        printf("%4s\t%10s\t%.2f\t\t%4d\n",
               productos[i].codigo,
               productos[i].descripcion,
               productos[i].precio,
               productos[i].stock);
    }


    printf("\n[1] Pagina principal\t[2] Pagina anterior\t[3] Pagina siguiente\t [4]Salir\nIngrese su respuesta: ");
    scanf("%d",&opcion);
        switch (opcion)
        {
        case 1:p=0;a=10;break;//
        case 2:p=p-10;if(p<0){p=0;};a=10;break;//
        case 3:p=p+10;if(p>count_p[0]){p=p-10;};if(count_p[0]-p<10){a=count_p[0]-p-1;}else{a=10;};break;//
        case 4:return;break;
        default: printf("\nOpcion Invalida");break;
        }
    }while (opcion != 4);


}

/*Muestra base de datos de Clientes*/
void mostrarBDDClientes()
{

    abrirBDDClientes();
    for (int i = 0; i < count_c[0] - 1; i++)
    {
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
void operacionProductos()
{

    int accionCliente, n;
    do
    {
        printf("\nQue desea hacer?\n [1] Ver catalogo de productos\n [2] Modificar un producto\n [3] Agregar un producto\n [4] Ver clientes\n [5] Menu principal\n [6] Salir\nIngrese su respuesta: ");
        fflush(stdout);
        scanf("%i", &accionCliente);
        fflush(stdout);
        fflush(stdin);
        switch (accionCliente)
        {
        case 1:
            mostrar10Productos();
            n = 0;
            break;
        case 2:
            modificarProducto();
            n = 0;
            break; // Por completar
        case 3:
            guardarProducto(nuevoProducto());
            fflush(stdout);
            n = 0;
            break; // Por completar comprobación
        case 4:
            mostrarBDDClientes();
            n = 0;
            break;
        case 5:
            n = 1;
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("\n\nOpcion invalida\n");
            n = 0;
            break;
        }
    } while (n == 0);
}

void ingresarAdmin()
{

    char ClaveAdmin[10] = "admin";
    int menuPrincipal, menu2, resp;
    printf("\nIngrese clave de administrador: ");
    fflush(stdout);
    fflush(stdin);
    char clave_adm[10];
    scanf("%s", &clave_adm);
    fflush(stdin);

    if (strcmp(clave_adm, ClaveAdmin) == 0)
    {
        operacionProductos();
    }
    else
    {
        printf("\n \nClave de administrador invalida\n \n");
    };
}

/*Actualiza la base de datos de Productos*/
int actualizarBDProductos() {
    FILE *bddpcsv;

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


        if (ferror(bddpcsv)) {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };

    };

    fclose(bddpcsv);
    printf("Se actualizo exitosamente la base de datos\n");
    return 0;
}
