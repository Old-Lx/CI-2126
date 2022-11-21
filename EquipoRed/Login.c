#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"


/*Struct de datos de clientes*/
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
    int i = 0;
    count_c[0] = 0;

    while (fgets(buff, 1024, bddcsv)) {

        /*printf("%s\n", buff);*/ //Imprime la línea leída

        char tempFecha[10];
        char tempTelf[20];

        char *entrada = strtok(buff, ";"); //divide el buffer por entrada de datos
        clientes[i].posCli = i;
        
        while (entrada) {

            if (count_c[0] != 0) {


                if (column == 0) {
                    strcpy(clientes[i].nombre, entrada);
                }

                else if (column == 1) {
                    strcpy(clientes[i].correo, entrada);
                }

                else if (column == 2) {
                    strcpy(clientes[i].direccion, entrada);
                }

                else if (column == 3) {
                    strcpy(tempTelf, entrada);
                    clientes[i].telefono = atoi(tempTelf);
                }

                else if (column == 4) {
                    strcpy(clientes[i].contactof, entrada);
                }

                else if (column == 5) {
                    strcpy(clientes[i].username, entrada);
                }

                else if (column == 6) {
                    strcpy(clientes[i].clave, entrada);
                }

                else if (column == 7) {
                    strcpy(clientes[i].fechaNacimiento, entrada);
                }

                else if (column == 8) {
                    strcpy(clientes[i].lugarNacimiento, entrada);
                }

                else if (column == 9) {
                    strcpy(clientes[i].genero, entrada);
                }
            }
            entrada = strtok(NULL, ";");
            column++;
            count_c[0]++;

        }

        column = 0;
        if (count_c[0] >= 20) {

            i++;

        }

    };

    fclose(bddcsv);

    count_c[0] = 0;

    bddcsv = fopen("clientes.csv", "r");
    while (fgets(buff, 1024, bddcsv)) {
        count_c[0]++;
    }

    return 0;
};


/*Crea un nuevo cliente*/
cliente nuevoCliente() {
    char comprClave[10];
    int n, aux, conteo, i, comp;
    cliente nuevo;
    printf("\nBienvenido, solicitaremos tus datos para registrarte\n"); //Nombre
    abrirBDDClientes();

    do /*Comprobación username vacio*/
    {   
        printf("\nIngrese un nombre de usuario: "); //nombre de usuario
        fflush(stdout);
        fgets(nuevo.username, 15, stdin);
        if(nuevo.username[1] != '\0'){
            nuevo.username[strcspn(nuevo.username,"\n")] = 0;
            conteo=1;
            for(i=0;i<100;i++){//Comprobacion en base de datos
                if(strcmp(nuevo.username, clientes[i].username)==0)
                {
                    printf("\nEste nombre de usuarios se encuentra registrado\n");
                    i=100;
                    conteo=0;
                }
            }
        }   
        else{   
                printf("Vacio NO");
                conteo = 0;
            }     

    }while(conteo == 0);



        


    do /*Verificación de correo con @ y . */
    {
        printf("\nIngrese direccion de correo electrónico: "); //correo
        fflush(stdout);
        fgets(nuevo.correo, 30, stdin);
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
                            nuevo.correo[strcspn(nuevo.correo,"\n")] = 0;
                            conteo = 3;
                            aux = 30;
                            n = 30;
                            for(i=0;i<100;i++){//Comprobacion en base de datos
                                if(strcmp(nuevo.correo, clientes[i].correo)==0)
                                {
                                    printf("\nEste corre se encuentra registrado\n");
                                    i=100;
                                    conteo=1;
                                }
                            }
                            
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
            if (conteo == 0)
            {
                printf("\nCorreo no valido, revisa que tenga el \"@\" y el \".\" ");
                printf("\n Por favor ingrese un correo Valido\n\n");
            }
        }else
        {
            printf("\nNo puedes ingresar correo vacio\n");
            conteo = 0;
            printf("\n Por favor ingrese un correo Valido\n\n");
        }
    } while (conteo < 2);

    do {/*Coincidan las claves*/
        do{/*No claves Vacias*/
            printf("\nIngrese una nueva clave de seguridad: ");
            fflush(stdout);
            fgets(nuevo.clave, 10, stdin);
            fflush(stdin);
            if(nuevo.clave[1] != '\0')
            {
                printf("\nCompruebe su clave de seguridad: ");
                fflush(stdout);
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
                printf("\nNo puedes ingresar datos vacios\n");
                n = 0;
            }
        }while (n < 1);

    }while (n < 1);





    do /*Comprobación nombre vacio*/
    {
        printf("\nIngrese su nombre y apellido: ");
        fflush(stdout);
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



    do /*Comprobación dirección vacio*/
    {
        printf("\nIngrese direccion de habitacion: "); //Direccion
        fflush(stdout);
        fgets(nuevo.direccion, 30, stdin);
        nuevo.direccion[strcspn(nuevo.direccion,"\n")] = 0;
        fflush(stdin);
        if(nuevo.direccion[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vaciosn");
            n = 0;
        }
    }while (n < 1);

    do /*Comprobación telefono vacio*/
    {
        printf("\nIngrese numero de telefono (Solo numeros): "); //telefono
        fflush(stdout);
        scanf("%lu", &nuevo.telefono);
        fflush(stdin);
        //system ("cls");
        if(nuevo.telefono != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    }while (n < 1);



    do /*Comprobación dia de nacimiento vacio*/
    {
        printf("Ingrese fecha de nacimiento: ");
        fflush(stdout);
        fgets(nuevo.fechaNacimiento, 10, stdin);
        nuevo.fechaNacimiento[strcspn(nuevo.fechaNacimiento,"\n")] = 0;
        fflush(stdin);
        if(nuevo.fechaNacimiento[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    }while (n < 1);

    do /*Comprobación lugar de nacimiento vacio*/
    {
        printf("\nIngrese lugar de nacimiento: ");//Lugar de nacimiento
        fflush(stdout);
        fgets(nuevo.lugarNacimiento, 20, stdin);
        nuevo.lugarNacimiento[strcspn(nuevo.lugarNacimiento,"\n")] = 0;
        fflush(stdin);
        if(nuevo.lugarNacimiento[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    }while (n < 1);




    do{//Género mediante menu
        printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n");
        fflush(stdout);
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
            printf("\n No ingresaste una opcion valida, selecciona nuevamente: ");
            n=0;
            break;
        }
        }while (n<1 );
        //system ("cls");

    do{// Modo de contacto favorito mediante menu
        printf("\nSeleccione metodo de comunicación preferido:\nTelefono[1]\nCorreo[2]\n");
        fflush(stdout);
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

/*Devuelve el índice de un cliente*/
int buscarCliente(const char username[20], cliente clienteL[100]) {

    int i = 0;
    while (strcmp(username, clienteL[i].username)) {

        printf("Buscando cliente...\n\n");
        i++;
        if (i == 100) {

            printf("El cliente no se encontró\n\n");
            break;
        }

    }

    if (!strcmp(username, clienteL[i].username))
    {
        return clienteL[i].posCli;
    } else {
        return -1;
    }
    
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

    for (int fila = 0; fila < count_c[0]+2; fila++) {

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

        if (fila < count_c[0] && fila > 0) {
            fprintf(bddcsv,
            "%s;%s;%s;%lu;%s;%s;%s;%s;%s;%s",
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


        if (fila == count_c[0]) {

            fprintf(bddcsv, "\n%s;%s;%s;%lu;%s;%s;%s;%s;%s;%s",
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
            fgets(clientes[num_fila[0]].nombre,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 2:
            printf("\nIngrese nueva direccion de correo electrónico:\n"); //Falta comprobacion si esta en la base de datos ya
            fgets(clientes[num_fila[0]].correo,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 3:
            printf("\nIngrese nueva dirección de habitación:\n"); //Direccion
            fgets(clientes[num_fila[0]].direccion,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 4:
            printf("\nIngrese nuevo número de telefono:\n"); //telefono
            scanf("%lu", &clientes[num_fila[0]].telefono);
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
                    strcpy(clientes[num_fila[0]].contactof, "Telefono");
                    n=2;
                    break;
                case 2:
                    strcpy(clientes[num_fila[0]].contactof, "Correo");
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
            fgets(clientes[num_fila[0]].username,20, stdin);
            fflush(stdin);
            n=2;
            break;
        case 7:
               do {/*Coincidan las claves*/
                do{/*No claves Vacias*/
                    printf("\nIngrese una nueva clave de seguridad:\n");
                    fgets(clientes[num_fila[0]].clave, 10, stdin);
                    fflush(stdin);
                    if(clientes[num_fila[0]].clave[1] != '\0')
                    {
                        printf("\nCompruebe su clave de seguridad:\n");
                        fgets(comprClave, 10, stdin);
                        fflush(stdin);
                        if (strcmp(clientes[num_fila[0]].clave, comprClave) == 0) {
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
                fgets(clientes[num_fila[0]].fechaNacimiento, 10, stdin);
                fflush(stdin);
                if(clientes[num_fila[0]].fechaNacimiento[1] != '\0')
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
            fgets(clientes[num_fila[0]].lugarNacimiento,20, stdin);
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
                strcpy(clientes[num_fila[0]].genero,"Femenino");
                n=2;
                break;
            case 2:
                strcpy(clientes[num_fila[0]].genero,"Masculino");
                n=2;
                break;
            case 3:
                strcpy(clientes[num_fila[0]].genero,"Sin especificar");
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


/*Muestra los datos del cliente*/
void mostrarDatosCliente(int filaDelCliente) {
    printf("Estos son tus datos:\nNombre: %s\nCorreo: %s\nDirección: %s\nTeléfono: %lu\nMétodo de contacto preferido: %s\n"
    "Nombre de usuario: %s\nClave: %s\nFecha de nacimiento: %s\nLugar de Nacimiento: %s\nGénero: %s\n",
    clientes[filaDelCliente].nombre,
    clientes[filaDelCliente].correo,
    clientes[filaDelCliente].direccion,
    clientes[filaDelCliente].telefono,
    clientes[filaDelCliente].contactof,
    clientes[filaDelCliente].username,
    clientes[filaDelCliente].clave,
    clientes[filaDelCliente].fechaNacimiento,
    clientes[filaDelCliente].lugarNacimiento,
    clientes[filaDelCliente].genero);
}

/*Ejecuta una operación para un cliente*/
void operacionCliente() {

    int n = 0;
    int accionCliente;
    do{
    printf("¿Qué desea hacer?\n [1] Modificar datos\n [2] Ver catálogo de compra\n [3] Ver mis datos\n [4] Salir\nIngrese su respuesta: ");
                fflush(stdout);
                scanf("%i", &accionCliente);
    switch (accionCliente)
    {
        case 1: modificarCliente(); n = 0; break;
        case 2: mostrarBDDProductos(); fflush(stdout); n= 0; break;
        case 3: mostrarDatosCliente(num_fila[0]); fflush(stdout); n= 0; break;
        case 4: n= 1; break;
        default: printf("\nOpción invalida\n"); n= 0; break;
    };
    }while (n==0);
    
}


/*Inicia sesión*/
int ingresar() {

    printf("Ingresa tu nombre de usuario:\n");
    fflush(stdout);
    char usuario[20];
    char clave[20];
    char operacion[2];
    scanf("%s", usuario);

    abrirBDDClientes();
    for (int i = 0; i < count_c[0]; i++) {
        if (!strcmp(usuario, clientes[i].username)) {

            num_fila[0] = i;
            printf("Ahora inserte su clave:\n");
            fflush(stdout);
            scanf("%s", clave);
            int n = 0;


            if (!strcmp(clave, clientes[num_fila[0]].clave)) {

                printf("Sesión iniciada\n");
                //menuUsuario()
                fflush(stdout);

                do {
                    printf("¿Deseas realizar alguna operación? [S]Sí [N]No\n");
                    fflush(stdout);
                    scanf("%s", operacion);

                    if (!strcmp("s", operacion) || !strcmp("S", operacion)) {

                        operacionCliente();

                    } else if (!strcmp("n", operacion) || !strcmp("N", operacion)) {

                        n = 1;

                    } else {

                        printf("Ingrese [S] para realizar una operacion y [N] para cerrar sesión\n");
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

                        printf("¿Deseas realizar alguna operación? [S]Sí [N]No\n");
                        fflush(stdout);
                        scanf("%s", operacion[0]);

                        if (!strcmp("s", operacion) || !strcmp("S", operacion)) {

                            operacionCliente();

                        } else if (!strcmp("n", operacion) || !strcmp("N", operacion)) {

                            n = 1;

                        } else {

                            printf("Ingrese [S] para realizar una operacion y [N] para cerrar sesión\n");
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

                            printf("¿Deseas realizar alguna operación? [S]Sí [N]No\n");
                            fflush(stdout);
                            scanf("%s", operacion[0]);

                        if (!strcmp("s", operacion) || !strcmp("S", operacion)) {

                            operacionCliente();

                        } else if (!strcmp("n", operacion) || !strcmp("N", operacion)) {

                            n = 1;

                        } else {

                            printf("Ingrese [S] para realizar una operacion y [N] para cerrar sesión\n");
                        }
                        } while (n == 0);
                    } else if (strcmp(clave, clientes[num_fila[0]].clave)) {

                        printf("Ha alcanzado el límite de intentos\n");
                        return 1;
                    }
                }
            }


        } else if (i == count_c[0]-1 && strcmp(usuario, clientes[num_fila[0]].username)) {

            printf("El usuario '%s' no se encuentra registrado %s\n", usuario);
            return 1;

        }
    };
    return 0;
}