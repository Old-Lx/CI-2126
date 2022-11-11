#include "Login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


cliente *prueba[100];
int count[1];

/*Fila donde se encuentra almacenado el usuario*/
int num_fila[1];


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
    int i = 0;
    count[0] = 0;

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
                    strcpy(clientes[i-1].fechaNacimiento, entrada);
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
            count[0]++;

        }

        column = 0;
        i++;

    };

    fclose(bddcsv);

    count[0] = 0;

    bddcsv = fopen("clientes.csv", "r");
    while (fgets(buff, 1024, bddcsv)) {
        count[0]++;
    }

    return 0;
};


/*Crea un nuevo cliente*/
cliente nuevoCliente() {
    char comprClave[10];
    int n, aux, conteo;
    cliente nuevo;
    printf("Bienvenido, solicitaremos tus datos para registrarte\n"); //Nombre

    do /*Comprobación nombre vacio*/
    {
        printf("\nIngrese su nombre y apellido:\n");
        fflush(stdin);
        fgets(nuevo.nombre, 20, stdin);
        nuevo.nombre[strcspn(nuevo.nombre,"\n")] = 0;
        fflush(stdin);
        if(nuevo.nombre[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);



    do /*Verificación de correo con @ y . */
    {
        printf("\nIngrese direccion de correo electrónico:\n"); //corrreo
        fflush(stdin);
        fgets(nuevo.correo, 30, stdin);
        nuevo.correo[strcspn(nuevo.correo,"\n")] = 0;
        fflush(stdin);
        if(nuevo.correo[1] != '\0')
        {
            for (n = 0 ; n < 30 ; n++)
            {
                if (nuevo.correo[n] == '@')
                {
                    for (aux = n + 1 ; aux < 30 ; aux++ )
                    {
                        if (nuevo.correo[aux] == '.')
                        {
                                conteo = 1;
                                aux = 30;
                                n = 30;
                        }
                        else
                        {
                            conteo = 0;
                        }
                    }
                }
                else
                {
                    conteo = 0;
                }
            }
            if (conteo != 1)
            {
                printf("\nCorreo no valido, revisa que tenga el \"@\" y el \".\" ");
                printf("\n Por favor ingrese un correo Valido\n\n");
            }
        }else
        {
            printf("\nNo puedes ingresar correo vacio");
            conteo = 0;
            printf("\n Por favor ingrese un correo Valido\n\n");
        }
    } while (conteo < 1);


    do /*Comprobación dirección vacio*/
    {
        printf("\nIngrese direcci�n de habitación:\n"); //Direccion
        fflush(stdin);
        fgets(nuevo.direccion, 30, stdin);
        nuevo.direccion[strcspn(nuevo.direccion,"\n")] = 0;
        fflush(stdin);
        if(nuevo.direccion[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);

    do /*Comprobación telefono vacio*/
    {
        printf("\nIngrese número de telefono (Solo números):\n"); //telefono
        fflush(stdin);
        scanf("%d", &nuevo.telefono);
        fflush(stdin);
        //system ("cls");
        if(nuevo.telefono != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);

    do /*Comprobación username vacio*/
    {
        printf("\nIngrese un nombre de usuario:\n"); //nombre de usuario
        fflush(stdin);
        fgets(nuevo.username, 15, stdin);
        nuevo.username[strcspn(nuevo.username,"\n")] = 0;
        fflush(stdin);
        //system ("cls");
        if(nuevo.username[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);



    do {/*Coincidan las claves*/
        do{/*No claves Vacias*/
            printf("\nIngrese una nueva clave de seguridad:\n");
            fflush(stdin);
            fgets(nuevo.clave, 10, stdin);
            fflush(stdin);
            if(nuevo.clave[1] != '\0')
            {
                printf("\nCompruebe su clave de seguridad:\n");
                fgets(comprClave, 10, stdin);
                fflush(stdin);
                if (strcmp(nuevo.clave, comprClave) == 0) {
                    n=2;
                    nuevo.clave[strcspn(nuevo.clave,"\n")] = 0;
                } else {
                    printf("\n\nLas claves NO son iguales, por favor ingresa de nuevo\n");
                    n=0;
                }
            }
            else
            {
                printf("\nNo puedes ingresar datos vacios");
                n = 0;
            }
        }while (n < 1);

    }while (n < 1);


    do /*Comprobación dia de nacimiento vacio*/
    {
        printf("Ingrese fecha de nacimiento:\n");
        fflush(stdin);
        fgets(nuevo.fechaNacimiento, 10, stdin);
        nuevo.fechaNacimiento[strcspn(nuevo.fechaNacimiento,"\n")] = 0;
        fflush(stdin);
        if(nuevo.fechaNacimiento[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);

    do /*Comprobación lugar de nacimiento vacio*/
    {
        printf("\nIngrese lugar de nacimiento:\n");//Lugar de nacimiento
        fgets(nuevo.lugarNacimiento, 20, stdin);
        nuevo.lugarNacimiento[strcspn(nuevo.lugarNacimiento,"\n")] = 0;
        fflush(stdin);
        if(nuevo.lugarNacimiento[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    }while (n < 1);




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
int guardarCliente(cliente nuevo) {


    FILE *bddcsv;


    abrirBDDClientes();

    bddcsv = fopen("clientes.csv", "w");

    if (bddcsv == NULL) {
        printf("Error al abrir la base de datos\n");
        return 1;
    }

    for (int fila = 0; fila < count[0]+2; fila++) {

        if (fila == 0) {
            fprintf(bddcsv,
            "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
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

        if (fila < count[0] && fila > 0) {
            fprintf(bddcsv,
            "%s;%s;%s;%d;%s;%s;%s;%s;%s;%s",
            clientes[fila-1].nombre,
            clientes[fila-1].correo,
            clientes[fila-1].direccion,
            clientes[fila-1].telefono,
            clientes[fila-1].contactof,
            clientes[fila-1].username,
            clientes[fila-1].clave,
            clientes[fila-1].fechaNacimiento,
            clientes[fila-1].lugarNacimiento,
            clientes[fila-1].genero);

        };


        if (fila == count[0]) {

            fprintf(bddcsv, "\n%s;%s;%s;%d;%s;%s;%s;%s;%s;%s",
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

        if (ferror(bddcsv)) {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };

    };

    fclose(bddcsv);
    printf("Se agregó exitosamente a la base de datos\n");
    return 0;
};



/*Inicia sesión*/
int ingresar() {

    printf("Ingresa tu nombre de usuario:\n");
    fflush(stdout);
    char usuario[20];
    char clave[20];
    scanf("%s", usuario);

    abrirBDDClientes();
    for (int i = 0; i < count[0]; i++) {
        if (!strcmp(usuario, clientes[i].username)) {

            num_fila[0] = i;
            printf("Ahora inserte su clave:\n");
            fflush(stdout);
            scanf("%s", clave);
            int n = 0;
            char accionCliente[1];


            if (!strcmp(clave, clientes[num_fila[0]].clave)) {

                printf("Sesión iniciada\n");
                fflush(stdout);

                do {

                    printf("¿Qué desea hacer?\n[1] Modificar datos\n[2] Ver catálogo de compra\n");
                    fflush(stdout);
                    scanf("%s", accionCliente);

                    if (!strcmp(accionCliente, "1")) {

                        /*modificarCliente();*/
                        n = 1;

                    } else if (!strcmp(accionCliente, "2")) {

                        printf("****Esta función se encuentra en mantenimiento****\n");
                        fflush(stdout);

                    } else {

                        printf("Opción inválida\n");
                        fflush(stdout);

                    }
                } while (n == 0);
            } else if (strcmp(clave, clientes[num_fila[0]].clave)) {

                printf("Clave incorrecta 2 intentos restantes\nIngrese su clave:\n");
                fflush(stdout);
                scanf("%s", clave);

                if (!strcmp(clave, clientes[num_fila[0]].clave)) {

                    printf("Sesión iniciada\n");
                    fflush(stdout);

                    do {

                        printf("¿Qué desea hacer?\n[1] Modificar datos\n[2] Ver catálogo de compra\n");
                        fflush(stdout);
                        scanf("%s", accionCliente);

                        if (!strcmp(accionCliente, "1")) {

                            /*modificarCliente();*/
                            n = 1;

                        } else if (!strcmp(accionCliente, "2")) {

                            printf("Esta función se encuentra en mantenimiento\n");
                            fflush(stdout);

                        } else {

                            printf("Opción inválida\n");
                            fflush(stdout);

                        }
                    } while (n == 0);
                } else if (strcmp(clave, clientes[num_fila[0]].clave)) {

                    printf("Clave incorrecta 1 intentos restantes\nIngrese su clave:\n");
                    fflush(stdout);
                    scanf("%s", clave);

                    if (!strcmp(clave, clientes[num_fila[0]].clave)) {

                        printf("Sesión iniciada\n");
                        fflush(stdout);

                        do {

                            printf("¿Qué desea hacer?\n[1] Modificar datos\n[2] Ver catálogo de compra\n");
                            fflush(stdout);
                            scanf("%s", accionCliente);

                            if (!strcmp(accionCliente, "1")) {

                                /*modificarCliente();*/
                                n = 1;

                            } else if (!strcmp(accionCliente, "2")) {

                                printf("Esta función se encuentra en mantenimiento\n");
                                fflush(stdout);

                            } else {

                                printf("Opción inválida\n");
                                fflush(stdout);

                            }
                        } while (n == 0);
                    } else if (strcmp(clave, clientes[num_fila[0]].clave)) {

                        printf("Ha alcanzado el límite de intentos\n");
                        return 1;
                    }
                }
            }


        } else if (i == count[0]) {

            printf("El usuario no se encuentra registrado\n");
            return 1;

        }
    };
    return 0;
}

/*Modifica datos de un cliente*/
int modificarCliente(){
    int cambiar;
    int dato;
    int n, aux;
    char comprClave[10];
    printf("\nDesea cambiar un dato?:\n [1] SI\n [2] NO\n");
    scanf("%d", &cambiar);
    if (cambiar==1)
    {

        do{
        printf("\nQue dato quiere cambiar?:\n [1] Nombre\n [2] Correo\n [3] Direccion\n [4] Telefono\n [5] Contactof\n [6] Username\n [7] Clave\n [8] Fecha de Nacimiento\n [9] Lugar de Nacimiento\n [10] Genero");
        scanf("%d", &dato);
        switch (dato){
        case 1:
            printf("\nIngrese su nuevo nombre y apellido");
            fgets(clientes[num_fila[1]].nombre,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 2:
            printf("\nIngrese nueva direccion de correo electrónico:\n"); //Falta comprobacion si esta en la base de datos ya
            fgets(clientes[num_fila[1]].correo,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 3:
            printf("\nIngrese nueva dirección de habitación:\n"); //Direccion
            fgets(clientes[num_fila[1]].direccion,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 4:
            printf("\nIngrese nuevo número de telefono:\n"); //telefono
            scanf("%d", &clientes[num_fila[1]].telefono);
            fflush(stdin);
            n=2;
            break;
        case 5:
            do{// Modo de contacto favorito mediante menu
            printf("\nSeleccione metodo de comunicación preferido:\nTelefono[1]\nCorreo[2]\n");
            scanf("%d", &aux);
            switch (aux)
            {
                case 1:
                    strcpy(clientes[num_fila[1]].contactof, "Telefono");
                    n=2;
                    break;
                case 2:
                    strcpy(clientes[num_fila[1]].contactof, "Correo");
                    n=2;
                    break;
                default:
                    printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
                    n=0;
                    break;
            }
            }while (n<1 );
                fflush(stdin);
                n=2;
                break;
        case 6:
            printf("\nIngrese nuevo Nombre de usuario:\n");//Falta comprobacion si esta en la base de datos ya
            fgets(clientes[num_fila[1]].username,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 7:
               do {/*Coincidan las claves*/
                do{/*No claves Vacias*/
                    printf("\nIngrese una nueva clave de seguridad:\n");
                    fgets(clientes[num_fila[1]].clave, 10, stdin);
                    fflush(stdin);
                    if(clientes[num_fila[1]].clave[1] != '\0')
                    {
                        printf("\nCompruebe su clave de seguridad:\n");
                        fgets(comprClave, 10, stdin);
                        fflush(stdin);
                        if (strcmp(clientes[num_fila[1]].clave, comprClave) == 0) {
                            n=2;
                        } else {
                            printf("\n\nLas claves NO son iguales, por favor ingresa de nuevo\n");
                            n=0;
                        }
                    }
                    else
                    {
                        printf("\nNo puedes ingresar datos vacios");
                        n = 0;
                    }
                }while (n < 1);
            }while (n < 1);
            n=2;
            break;
        case 8:
             do /*Comprobación dia de nacimiento vacio*/
            {
                printf("Ingrese nueva fecha de nacimiento:\n");
                fgets(clientes[num_fila[1]].fechaNacimiento, 10, stdin);
                fflush(stdin);
                if(clientes[num_fila[1]].fechaNacimiento[1] != '\0')
                {
                    n = 1;
                }
                else
                {
                    printf("\nNo puedes ingresar datos vacios");
                    n = 0;
                }
            }while (n < 1);
        case 9:
            printf("\nIngrese nuevo lugar de nacimiento:\n");
            fgets(clientes[num_fila[1]].lugarNacimiento,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 10:
            do{
            printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n"); //Género mediante menu
            scanf("%d", &aux);
            switch (aux)
            {
            case 1:
                strcpy(clientes[num_fila[1]].genero,"Femenino");
                n=2;
                break;
            case 2:
                strcpy(clientes[num_fila[1]].genero,"Masculino");
                n=2;
                break;
            case 3:
                strcpy(clientes[num_fila[1]].genero,"Sin especificar");
                n=2;
                break;
            default:
                printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
                n=0;
                break;
            }
            }while (n<1 );
            fflush(stdin);
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
