#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gestorDeProductos.h"

/*Declaramos una struct para almacenar fechas*/
typedef struct {
    int dia;
    int mes;
    int year;
} fecha ;

/*Declaramos un struct para guardar clientes*/
typedef struct {   
    char nombre[20];
    char correo[20];
    char direccion[30];
    int telefono;
    char contactof[20];
    char username[15];
    char clave[10];
    char fechaNacimiento[10];
    char lugarNacimiento[20];
    char genero[20];
} cliente ;

/*Declaramos el arreglo de todos los clientes*/
cliente clientes[100];



/*Arreglo din�mico que guarda a los clientes*/
typedef struct {
    double *datos;
    size_t size;
    size_t capacidad;
} baseDeDatos ;



baseDeDatos *bddNueva(size_t N);

/*Abre una base de datos de personas guardada en un archivo csv*/
cliente *abrirBDDClientes();

/*Crea un nuevo cliente*/
cliente nuevoCliente();

/*Guarda un cliente en la base de datos*/
int guardarCliente(cliente nuevo);

/*Crea un nuevo cliente*/
producto nuevoProducto();

baseDeDatos *bddNueva(size_t N) {
    baseDeDatos *BDD = (baseDeDatos *) malloc(sizeof(baseDeDatos));
    BDD->size = N;
    BDD->capacidad = N;
    return BDD;
}

cliente *prueba[100];
cliente clientes[100];

/*Abre una base de datos de personas guardada en un archivo csv*/
cliente *abrirBDDClientes() {


    FILE *bddcsv;
    bddcsv = fopen("clientes.csv", "r");
    
    if (bddcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; //guarda las primeras 1024 líneas en un buffer
    int column = 0;
    int count = 0;
    int i = 0;

    while (fgets(buff, 1024, bddcsv)) {

        /*printf("%s\n", buff);*/ //Imprime la línea leída

        char tempFecha[10];
        char tempTelf[20];

        char *entrada = strtok(buff, ";"); //divide el buffer por entrada de datos
    
        while (entrada) {

            if (count != 0) {
                
                
                if (column == 0) {
                    strcpy(clientes[i-1].nombre, entrada);
                }

                else if (column == 1) {
                    strcpy(clientes[i-1].correo, entrada);
                }

                else if (column == 2) {
                    strcpy(clientes[i-1].direccion, entrada);
                }

                else if (column == 3) {
                    strcpy(tempTelf, entrada);
                }

                else if (column == 4) {
                    strcpy(clientes[i-1].contactof, entrada);
                }

                else if (column == 5) {
                    strcpy(clientes[i-1].username, entrada);
                }

                else if (column == 6) {
                    strcpy(clientes[i-1].clave, entrada);
                }

                else if (column == 7) {
                    strcpy(tempFecha, entrada);
                }

                else if (column == 8) {
                    strcpy(clientes[i-1].lugarNacimiento, entrada);
                }

                else if (column == 9) {
                    strcpy(clientes[i-1].genero, entrada);
                }
            }
            entrada = strtok(NULL, ";");
            column++;
            count++;

        }
        
        column = 0;
        i++;

    };
    
    fclose(bddcsv);

}


/*Crea un nuevo cliente*/
cliente nuevoCliente() {
    char comprClave[10];
    int n,aux;
    cliente nuevo;
    printf("Bienvenido, solicitaremos tus datos para registrarte\n"); //Nombre
    printf("\nIngrese su nombre y apellido:\n");
    fgets(nuevo.nombre, 20, stdin);
    fflush(stdin);
    //system ("cls");

    printf("\nIngrese direccion de correo electrónico:\n"); //corrreo
    fgets(nuevo.correo, 20, stdin);
    fflush(stdin);
    //system ("cls");

    printf("\nIngrese direcci�n de habitación:\n"); //Direccion
    fgets(nuevo.direccion, 30, stdin);
    fflush(stdin);
    //system ("cls");

    printf("\nIngrese número de telefono:\n"); //telefono
    scanf("%d", &nuevo.telefono);
    fflush(stdin);
    //system ("cls");

    printf("\nIngrese un nombre de usuario:\n"); //nombre de usuario
    fgets(nuevo.username, 15, stdin);
    fflush(stdin);
    //system ("cls");

    do {
        printf("\nIngrese una nueva clave de seguridad:\n"); //Clave y comprobaci�n
        fgets(nuevo.clave, 10, stdin);
        fflush(stdin);
        printf("\nCompruebe su clave de seguridad:\n");
        fgets(comprClave, 10, stdin);
        fflush(stdin);
        if (strcmp(nuevo.clave, comprClave) == 0) {
            n=2;
        } else {
            printf("\n\nLas claves NO son iguales, por favor ingresa de nuevo\n");
            n=0;
        }}while (n < 1);
        //system ("cls");

    printf("Ingrese día de nacimiento:\n");
    fgets(nuevo.lugarNacimiento, 20, stdin);
    fflush(stdin);

    printf("\nIngrese lugar de nacimiento:\n");//Lugar de nacimiento
    fgets(nuevo.lugarNacimiento, 20, stdin);
    fflush(stdin);
    //system ("cls");

    do{//Género mediante menu
        printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n");
        scanf("%d", &aux);
        switch (aux)
        {
        case 1:
            strcpy(nuevo.genero, "Femenino");
            n=2;
            break;
        case 2:
            strcpy(nuevo.genero, "Masculino");
            n=2;
            break;
        case 3:
            strcpy(nuevo.genero, "Sin especificar");
            n=2;
            break;
        default:
            printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
            n=0;
            break;
        }
        }while (n<1 );
        //system ("cls");

    do{// Modo de contacto favorito mediante menu
        printf("\nSeleccione metodo de comunicación preferido:\nTelefono[1]\nCorreo[2]\n");
            scanf("%d", &aux);
            switch (aux)
        {
        case 1:
            strcpy(nuevo.contactof, "Telefono");
            n=2;
            break;
        case 2:
            strcpy(nuevo.contactof, "Correo");
            n=2;
            break;
        default:
            printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
            n=0;
            break;
        }
        }while (n<1 );
        //system ("cls");
    return nuevo;
}

/*Guarda un cliente en la base de datos*/
int guardarCliente( cliente nuevo) {
    

    /*strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->correo, correo);
    strcpy(nuevo->direccion, direccion);
    nuevo->telefono = 7855;
    strcpy(nuevo->contactof, contactof);
    strcpy(nuevo->username, username);
    strcpy(nuevo->clave, clave);
    nuevo->fechaNacimiento.dia = 9;
    nuevo->fechaNacimiento.mes = 9;
    nuevo->fechaNacimiento.year = 1972;
    strcpy(nuevo->lugarNacimiento, lugarNacimiento);
    strcpy(nuevo->genero, genero);*/

    FILE *bddcsv;
    bddcsv = fopen("clientes.csv", "r");

    if (bddcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }
    
    char buff[1024];
    int count = 0;

    while (fgets(buff, 1024, bddcsv)) {

        count++;

    };

    fclose(bddcsv);

    printf("%d\n", count);

    abrirBDDClientes();
    
    bddcsv = fopen("clientes.csv", "w");
    
    printf("%s\n", clientes[0].lugarNacimiento);

    for (int fila = 0; fila < count+2; fila++) {

        if (fila == 0) {
            fprintf(bddcsv, 
            "%s;%s;%s;%d;%s;%s;%s;%s;%s;%s\n",
            "nombre",
            "correo",
            "direccion",
            "telefono",
            "contactofav",
            "username",
            "clave",
            "fechaNac",
            "lugarNac",
            "genero");
        }

        if (fila < count && fila > 0) {
            fprintf(bddcsv, 
            "%s;%s;%s;%d;%s;%s;%s;%s;%s;%s",
            clientes[fila-1].nombre,
            clientes[fila-1].correo,
            clientes[fila-1].direccion,
            clientes[fila-1].telefono,
            clientes[fila-1].contactof,
            clientes[fila-1].username,
            clientes[fila-1].clave,
            "fecha",
            clientes[fila-1].lugarNacimiento,
            clientes[fila-1].genero);
        }; 
        

        if (fila == count) {

            if (clientes[count-1].nombre != NULL) {
            fprintf(bddcsv, "%s;%s;%s;%d;%s;%s;%s;%s;%s;%s",
            nuevo.nombre,
            nuevo.correo,
            nuevo.direccion,
            nuevo.telefono,
            nuevo.contactof,
            nuevo.username,
            nuevo.clave,
            nuevo.fechaNacimiento,
            nuevo.lugarNacimiento,
            nuevo.genero);
            } else {

            fprintf(bddcsv, 
            "\n%s;%s;%s;%d;%s;%s;%s;%s;%s;%s",
            nuevo.nombre,
            nuevo.correo,
            nuevo.direccion,
            nuevo.telefono,
            nuevo.contactof,
            nuevo.username,
            nuevo.clave,
            nuevo.fechaNacimiento,
            nuevo.lugarNacimiento,
            nuevo.genero);

            };
            
            
        };
        
        if (ferror(bddcsv)) {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };

    };

    fclose(bddcsv);
    printf("Se agregó exitosamente a la base de datos\n");

};

/*Crea un nuevo cliente*/
producto nuevoProducto() {
    int n,aux;
    producto nuevo;
    printf("Solicitaremos los datos para añadir un nuevo producto:\n"); 
    printf("\nIngrese código:\n");
    fgets(nuevo.codigo, 20, stdin);

    /*Añadir comprobación si no se encuentra en la base de datos*/

    fflush(stdin);
    //system ("cls");

    printf("\nIngrese descripción del producto:\n"); 
    fgets(nuevo.descripcion, 145, stdin);
    fflush(stdin);
    //system ("cls");

    do{
        printf("\nIngrese el precio:\n"); 
        scanf("%f",&nuevo.precio);
        if(nuevo.precio <= 0){
            printf("\nOpción invalida, intente de nuevo");
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
}

#endif // LOGIN_H_INCLUDED