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
        char genero[20];
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

/*Abre una base de datos de personas guardada en un archivo csv*/
int abrirBDDClientes() {

    FILE *bddcsv;
    bddcsv = fopen("clientes.csv", "r");
    
    if (bddcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }

    cliente clientes[100];

    char buff[1024]; //guarda las primeras 1024 líneas en un buffer
    int filas = 0;
    int column = 0;
    int count = 0;

    for (int i = 0; i < 9; i++) {

        while (fgets(buff, 1024, bddcsv)) {
            printf("%s\n", buff); //Imprime la línea leída
            
            char tempFecha[10];
            char tempTelf[20];

            char *entrada = strtok(buff, ";"); //divide el buffer por entrada de datos
        
            while (entrada) {
                if (column == 0) {
                    strcpy(clientes[i].nombre, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 1) {
                    strcpy(clientes[i].correo, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 2) {
                    strcpy(clientes[i].direccion, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 3) {
                    strcpy(tempTelf, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 4) {
                    strcpy(clientes[i].contactof, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 5) {
                    strcpy(clientes[i].username, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 6) {
                    strcpy(clientes[i].clave, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 7) {
                    strcpy(tempFecha, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 8) {
                    strcpy(clientes[i].lugarNacimiento, entrada);
                    printf("%d\n%s\n", column, entrada);
                }

                else if (column == 9) {
                    strcpy(clientes[i].genero, entrada);
                    printf("%d\n%s\n", column, entrada);
                }
                entrada = strtok(NULL, ";");
                column++;
                count++;
            }
            column = 0;
        };
    };

    fclose(bddcsv);

    for (int i = 0; i < 3; i++) {
        printf("Nombre-> %s correo-> %s direccion-> %s contactofav-> %s username-> %s clave-> %s lugarNac-> %s genero-> %s\n",
        clientes[i].nombre,
        clientes[i].correo,
        clientes[i].direccion,
        clientes[i].contactof,
        clientes[i].username,
        clientes[i].clave,
        clientes[i].lugarNacimiento,
        clientes[i].genero);
    };

    printf("\n%d entradas leídas\n\n", count);    

}


/*Crea un nuevo cliente*/
void nuevoCliente() {
    char comprClave[10];
    int n,aux;

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
    scanf("%d", &aux);
    switch (aux)
    {
    case 1:
        strcpy(nuevo.genero,"Femenino");
        n=2;
        break;
    case 2:
        strcpy(nuevo.genero,"Masculino");
        n=2;
        break;
    case 3:
        strcpy(nuevo.genero,"Sin especificar");
        n=2;
        break;
    default:
        printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
        n=0;
        break;
    }
    }while (n<1 );

do{
    printf("\nSeleccione metodo de comunicación preferido:\nTelefono[1]\nCorreo[2]"); // Modo de contacto favorito mediante menu
        scanf("%d", &aux);
        switch (aux)
    {
    case 1:
        strcpy(nuevo.contactof,"Telefono");
        n=2;
        break;
    case 2:
        strcpy(nuevo.contactof,"Correo");
        n=2;
        break;
    default:
        printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
        n=0;
        break;
    }
    }while (n<1 );
    
}


int main() {
    /*printf("¿Ya te registraste?\n Escribe s si te registraste y n si no estás registrado\n");*/

    abrirBDDClientes();

    /*if (strcmp(answer, s)) {
        ingresar();
    }

    else {
        nuevoCliente();
        guardarCliente();
        abrirBDDClientes();
    }*/
    return 0;
}