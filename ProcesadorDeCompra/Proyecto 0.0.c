#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*#include <csv.h>*/

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
        fecha fechaNacimiento;
        char lugarNacimiento[20];
        char genero[10];
}cliente ;

/*Arreglo dinámico que guarda a los clientes*/
typedef struct {
    double *datos;
    size_t size;
    size_t capacidad;
} baseDeDatos ;

baseDeDatos *bddNueva(size_t N) {
    baseDeDatos *BDD = (baseDeDatos *) malloc(sizeof(baseDeDatos));
    BDD->size = N;
    BDD->capacidad = N;
    return BDD;
}


/*Crea un nuevo cliente*/
void nuevoCliente() {
    char comprClave[10];
    int n;

    cliente nuevo;
    printf("Bienvenido, solicitaremos tus datos para registrarte\n"); //Nombre
    printf("\nIngrese su nombre y apellido:\n");
    scanf("%s", &nuevo.nombre);

    printf("\nIngrese direccion de correo electrónico:\n"); //corrreo
    scanf("%s", &nuevo.correo);

    printf("\nIngrese dirección de habitación:\n"); //Direccion
    scanf("%s", &nuevo.direccion);

    printf("\nIngrese número de telefono:\n"); //telefono
    scanf("%s", &nuevo.telefono);

    printf("\nIngrese un nombre de usuario:\n"); //nombre de usuario
    scanf("%s", &nuevo.username);

    do {
        printf("\nIngrese una nueva clave de seguridad:\n"); //Clave y comprobación
        scanf("%s", &nuevo.clave);
        printf("\nCompruebe su clave de seguridad:\n");
        scanf("%s", &comprClave);
        if (strcmp(nuevo.clave, comprClave) == 0) {
            n=2;
        } else {
            printf("\n\nLas claves NO son iguales, por favor ingresa de nuevo\n");
            n=0;
        }}while (n < 1);

    printf("Ingrese día de nacimiento:\n");
    scanf("%d", &nuevo.fechaNacimiento.dia);

    printf("\nIngrese mes de nacimiento:\n");
    scanf("%d", &nuevo.fechaNacimiento.mes);

    printf("\nIngrese año de nacimiento:\n");//Fecha de nacimiento
    scanf("%d", &nuevo.fechaNacimiento.year);

    printf("\nIngrese lugar de nacimiento:\n");//Lugar de nacimiento
    scanf("%s", &nuevo.lugarNacimiento);
do{
    printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n"); //Género mediante menu
    scanf("%d", &nuevo.genero);
    if (nuevo.genero == 1 || nuevo.genero == 2 || nuevo.genero == 3 ){
           n=2;
        }else{
            printf("\n No ingresaste una opcion valida\n");
            n=0;
        };
    }while (n<1 );

do{
     printf("\nSeleccione metodo de comunicación preferido:\nTelefono[1]\nCorreo[2]"); // Modo de contacto favorito mediante menu
        scanf("%d", &nuevo.contactof);
        if (nuevo.contactof == 1 || nuevo.contactof == 2)
        {
           n=2;
        }else{
            printf("\n No ingresaste una opcion valida\n");
            n=0;
            };
    }while (n<1 );
    
}


/*printf("Ingrese día de nacimiento:\n");
    scanf("%d", &nuevo.fechaNacimiento.dia);
    printf("Ingreso el día: %d", nuevo.fechaNacimiento.dia);
    printf("\nIngrese mes de nacimiento:\n");
    scanf("%d", &nuevo.fechaNacimiento.mes);
    printf("Ingreso el mes: %d", nuevo.fechaNacimiento.mes);
    printf("\nIngrese año de nacimiento:\n");
    scanf("%d", &nuevo.fechaNacimiento.year);
    printf("Ingreso el año: %d", nuevo.fechaNacimiento.year);
    printf("\n\nExcelente, su fecha de nacimiento es: %d / %d / %d", nuevo.fechaNacimiento.dia, 
    nuevo.fechaNacimiento.mes, nuevo.fechaNacimiento.year);*/

/*      int n=0;
    int opcion;
    int i;
    do{
    printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n");
    scanf("%d", &opcion);

        switch (opcion)
        { 
            case 1 :
                nuevo.genero[10] = "Femenino";
                printf("Ingreso el día: %s", nuevo.genero);
                n=2;
                break;
            case 2 :
                nuevo.genero[10] = "Masculino";
                n=2;
                break;
            case 3 :
                nuevo.genero[10] = "Indef";
                n=2;
                break;        
            default:
                printf("\n No ingresaste una opcion valida\n");
                n=0;
                break;
        }}while (n < 1);
*/

/*
    struct clientes primero;
    printf("Ingrese día de nacimiento:\n");
    scanf("%d", &primero.fechaNacimiento.dia);
    printf("Ingreso el día: %d", primero.fechaNacimiento.dia);
    printf("\nIngrese mes de nacimiento:\n");
    scanf("%d", &primero.fechaNacimiento.mes);
    printf("Ingreso el mes: %d", primero.fechaNacimiento.mes);
    printf("\nIngrese año de nacimiento:\n");
    scanf("%d", &primero.fechaNacimiento.year);
    printf("Ingreso el año: %d", primero.fechaNacimiento.year);
    printf("\n\nExcelente, su fecha de nacimiento es: %d / %d / %d", primero.fechaNacimiento.dia, 
    primero.fechaNacimiento.mes, primero.fechaNacimiento.year);*/

