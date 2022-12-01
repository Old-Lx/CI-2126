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
cliente *abrirBDDClientes()
{

    FILE *bddcsv;
    bddcsv = fopen("clientes.csv", "r");

    if (bddcsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    char buff[1024]; // guarda las primeras 1024 líneas en un buffer
    int column = 0;
    int i = 0;
    count_c[0] = 0;

    while (fgets(buff, 1024, bddcsv))
    {

        /*printf("%s\n", buff);*/ // Imprime la línea leída

        char tempFecha[10];
        char tempTelf[20];

        char *entrada = strtok(buff, ";"); // divide el buffer por entrada de datos
        clientes[i].posCli = i;

        while (entrada)
        {

            if (count_c[0] != 0)
            {

                if (column == 0)
                {
                    strcpy(clientes[i].nombre, entrada);
                }

                else if (column == 1)
                {
                    strcpy(clientes[i].correo, entrada);
                }

                else if (column == 2)
                {
                    strcpy(clientes[i].direccion, entrada);
                }

                else if (column == 3)
                {
                    strcpy(tempTelf, entrada);
                    clientes[i].telefono = atoi(tempTelf);
                }

                else if (column == 4)
                {
                    strcpy(clientes[i].contactof, entrada);
                }

                else if (column == 5)
                {
                    strcpy(clientes[i].username, entrada);
                }

                else if (column == 6)
                {
                    strcpy(clientes[i].clave, entrada);
                }

                else if (column == 7)
                {
                    strcpy(clientes[i].fechaNacimiento, entrada);
                }

                else if (column == 8)
                {
                    strcpy(clientes[i].lugarNacimiento, entrada);
                }

                else if (column == 9)
                {
                    strcpy(clientes[i].genero, entrada);
                }
            }
            entrada = strtok(NULL, ";");
            column++;
            count_c[0]++;
        }

        column = 0;
        if (count_c[0] >= 20)
        {

            i++;
        }
    };

    fclose(bddcsv);

    count_c[0] = 0;

    bddcsv = fopen("clientes.csv", "r");
    while (fgets(buff, 1024, bddcsv))
    {
        count_c[0]++;
    }

    return 0;
};

/*Crea un nuevo cliente*/
cliente nuevoCliente()
{
    char comprClave[10];
    int n, aux, conteo, i, comp;
    cliente nuevo;
    printf("\nBienvenido, solicitaremos tus datos para registrarte\n"); // Nombre
    abrirBDDClientes();

    do /*Comprobación username vacio*/
    {
        printf("\nIngrese un nombre de usuario: "); // nombre de usuario
        fflush(stdout);
        fgets(nuevo.username, 15, stdin);
        if (nuevo.username[1] != '\0')
        {
            nuevo.username[strcspn(nuevo.username, "\n")] = 0;
            conteo = 1;
            for (i = 0; i < 100; i++)
            { // Comprobacion en base de datos
                if (strcmp(nuevo.username, clientes[i].username) == 0)
                {
                    printf("\nEste nombre de usuarios se encuentra registrado\n");
                    i = 100;
                    conteo = 0;
                }
            }
        }
        else
        {
            printf("\nInserte un dato\n");
            conteo = 0;
        }

    } while (conteo == 0);

    do /*Verificación de correo con @ y . */
    {
        printf("\nIngrese direccion de correo electrónico: "); // correo
        fflush(stdout);
        fgets(nuevo.correo, 30, stdin);
        fflush(stdin);
        if (nuevo.correo[1] != '\0')
        {
            for (n = 0; n < 30; n++)
            {
                if (nuevo.correo[n] == '@')
                {
                    for (aux = n + 1; aux < 30; aux++)
                    {
                        if (nuevo.correo[aux] == '.')
                        {
                            nuevo.correo[strcspn(nuevo.correo, "\n")] = 0;
                            conteo = 3;
                            aux = 30;
                            n = 30;
                            for (i = 0; i < 100; i++)
                            { // Comprobacion en base de datos
                                if (strcmp(nuevo.correo, clientes[i].correo) == 0)
                                {
                                    printf("\nEste corre se encuentra registrado\n");
                                    i = 100;
                                    conteo = 1;
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
        }
        else
        {
            printf("\nNo puedes ingresar correo vacio\n");
            conteo = 0;
            printf("\n Por favor ingrese un correo Valido\n\n");
        }
    } while (conteo < 2);

    do
    { /*Coincidan las claves*/
        do
        { /*No claves Vacias*/
            printf("\nIngrese una nueva clave de seguridad: ");
            fflush(stdout);
            fgets(nuevo.clave, 10, stdin);
            fflush(stdin);
            if (nuevo.clave[1] != '\0')
            {
                printf("\nCompruebe su clave de seguridad: ");
                fflush(stdout);
                fgets(comprClave, 10, stdin);
                fflush(stdin);
                if (strcmp(nuevo.clave, comprClave) == 0)
                {
                    n = 2;
                    nuevo.clave[strcspn(nuevo.clave, "\n")] = 0;
                }
                else
                {
                    printf("\n\nLas claves NO son iguales, por favor ingresa de nuevo\n");
                    n = 0;
                }
            }
            else
            {
                printf("\nNo puedes ingresar datos vacios\n");
                n = 0;
            }
        } while (n < 1);

    } while (n < 1);

    do /*Comprobación nombre vacio*/
    {
        printf("\nIngrese su nombre y apellido: ");
        fflush(stdout);
        fgets(nuevo.nombre, 20, stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;
        fflush(stdin);
        if (nuevo.nombre[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios");
            n = 0;
        }
    } while (n < 1);

    do /*Comprobación dirección vacio*/
    {
        printf("\nIngrese direccion de habitacion: "); // Direccion
        fflush(stdout);
        fgets(nuevo.direccion, 30, stdin);
        nuevo.direccion[strcspn(nuevo.direccion, "\n")] = 0;
        fflush(stdin);
        if (nuevo.direccion[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vaciosn");
            n = 0;
        }
    } while (n < 1);

    do /*Comprobación telefono vacio*/
    {
        printf("\nIngrese numero de telefono (Solo numeros): "); // telefono
        fflush(stdout);
        scanf("%lu", &nuevo.telefono);
        fflush(stdin);
        // system ("cls");
        if (nuevo.telefono != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    } while (n < 1);

    do /*Comprobación dia de nacimiento vacio*/
    {
        printf("Ingrese fecha de nacimiento: ");
        fflush(stdout);
        fgets(nuevo.fechaNacimiento, 10, stdin);
        nuevo.fechaNacimiento[strcspn(nuevo.fechaNacimiento, "\n")] = 0;
        fflush(stdin);
        if (nuevo.fechaNacimiento[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    } while (n < 1);

    do /*Comprobación lugar de nacimiento vacio*/
    {
        printf("\nIngrese lugar de nacimiento: "); // Lugar de nacimiento
        fflush(stdout);
        fgets(nuevo.lugarNacimiento, 20, stdin);
        nuevo.lugarNacimiento[strcspn(nuevo.lugarNacimiento, "\n")] = 0;
        fflush(stdin);
        if (nuevo.lugarNacimiento[1] != '\0')
        {
            n = 1;
        }
        else
        {
            printf("\nNo puedes ingresar datos vacios\n");
            n = 0;
        }
    } while (n < 1);

    do
    { // Género mediante menu
        printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n");
        fflush(stdout);
        scanf("%d", &aux);
        switch (aux)
        {
        case 1:
            strcpy(nuevo.genero, "Femenino");
            n = 2;
            break;
        case 2:
            strcpy(nuevo.genero, "Masculino");
            n = 2;
            break;
        case 3:
            strcpy(nuevo.genero, "Sin especificar");
            n = 2;
            break;
        default:
            printf("\n No ingresaste una opcion valida, selecciona nuevamente: ");
            n = 0;
            break;
        }
    } while (n < 1);
    // system ("cls");

    do
    { // Modo de contacto favorito mediante menu
        printf("\nSeleccione metodo de comunicación preferido:\nTelefono[1]\nCorreo[2]\n");
        fflush(stdout);
        scanf("%d", &aux);
        switch (aux)
        {
        case 1:
            strcpy(nuevo.contactof, "Telefono");
            n = 2;
            break;
        case 2:
            strcpy(nuevo.contactof, "Correo");
            n = 2;
            break;
        default:
            printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
            n = 0;
            break;
        }
    } while (n < 1);
    // system ("cls");
    return nuevo;
}

/*Devuelve el índice de un cliente*/
int buscarCliente(const char username[20], cliente clienteL[100])
{

    int i = 0;
    while (strcmp(username, clienteL[i].username))
    {

        printf("Buscando cliente...\n\n");
        i++;
        if (i == 100)
        {

            printf("El cliente no se encontró\n\n");
            return 0;
        }
    }

    if (!strcmp(username, clienteL[i].username))
    {
        return clienteL[i].posCli;
    }
    else
    {
        return 0;
    }
}

/*Guarda un cliente en la base de datos*/
int guardarCliente(cliente nuevo)
{

    FILE *bddcsv;

    abrirBDDClientes();

    bddcsv = fopen("clientes.csv", "w");

    if (bddcsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return 1;
    }

    for (int fila = 0; fila < count_c[0] + 2; fila++)
    {

        if (fila == 0)
        {
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

        if (fila < count_c[0] && fila > 0)
        {
            fprintf(bddcsv,
                    "%s;%s;%s;%lu;%s;%s;%s;%s;%s;%s",
                    clientes[fila - 1].nombre,
                    clientes[fila - 1].correo,
                    clientes[fila - 1].direccion,
                    clientes[fila - 1].telefono,
                    clientes[fila - 1].contactof,
                    clientes[fila - 1].username,
                    clientes[fila - 1].clave,
                    clientes[fila - 1].fechaNacimiento,
                    clientes[fila - 1].lugarNacimiento,
                    clientes[fila - 1].genero);
        };

        if (fila == count_c[0])
        {

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

        if (ferror(bddcsv))
        {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };
    };

    fclose(bddcsv);
    printf("Se agregó exitosamente a la base de datos\n");
    return 0;
};

/*Modifica datos de un cliente*/
int modificarCliente()
{
    int cambiar;
    int dato;
    int n, aux, conteo, i;
    char nuevo[20];
    char comprClave[10];

    do
    {
        printf("\nQue dato quieres cambiar?\n [1] Nombre\n [2] Correo\n [3] Direccion\n [4] Telefono\n [5] Contactof\n" 
        " [6] Clave\n [7] Fecha de Nacimiento\n [8] Lugar de Nacimiento\n [9] Genero\n [10] Salir\n");
        printf("Seleccione una opcion:\t");
        scanf("%d", &dato);
        fflush(stdin);
        switch (dato)
        {
        case 1:
            do
            {
                printf("\nIngrese su nuevo nombre y apellido:\t");
                fgets(nuevo, 20, stdin);
                nuevo[strcspn(nuevo, "\n")] = 0;
                if (nuevo[1] != '\0')
                {
                    strcpy(clientes[num_fila[0]].nombre, nuevo);
                    fflush(stdin);
                    n = 2;
                }
                else
                {
                    printf("\n\nPor Favor introduzca un dato\n\n");
                    n = 0;
                }
            } while (n == 0);

            break;
        case 2:
            do /*Verificación de correo con @ y . */
            {
                printf("\nIngrese nueva direccion de correo electrónico:\t");
                fflush(stdout);
                fgets(nuevo, 30, stdin);
                nuevo[strcspn(nuevo, "\n")] = 0;
                fflush(stdin);
                if (nuevo[1] != '\0')
                {
                    for (n = 0; n < 30; n++)
                    {
                        if (nuevo[n] == '@')
                        {
                            for (aux = n + 1; aux < 30; aux++)
                            {
                                if (nuevo[aux] == '.')
                                {

                                    conteo = 3;
                                    aux = 30;
                                    n = 30;
                                    for (i = 0; i < 100; i++)
                                    { // Comprobacion en base de datos
                                        if (strcmp(nuevo, clientes[i].correo) == 0)
                                        {
                                            printf("\nEste corre se encuentra registrado\n");
                                            i = 100;
                                            conteo = 1;
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
                }
                else
                {
                    printf("\nNo puedes ingresar correo vacio\n");
                    conteo = 0;
                    printf("\n Por favor ingrese un correo Valido\n\n");
                }
            } while (conteo < 2);

            strcpy(clientes[num_fila[0]].correo, nuevo);
            fflush(stdin);
            n = 2;
            fgets(nuevo, 20, stdin);

            break;
        case 3:
            do /*Comprobación dirección vacio*/
            {
                printf("\nIngrese nueva direccion de habitación:\n"); // Direccion
                fflush(stdout);
                fgets(nuevo, 30, stdin);
                nuevo[strcspn(nuevo, "\n")] = 0;
                fflush(stdin);
                if (nuevo[1] != '\0')
                {
                    strcpy(clientes[num_fila[0]].direccion, nuevo);
                    n = 1;
                }
                else
                {
                    printf("\nNo puedes ingresar datos vacios\n");
                    n = 0;
                }
            } while (n < 1);

            break;
        case 4:
            printf("\nIngrese nuevo numero de telefono:\n"); // telefono
            scanf("%lu", &clientes[num_fila[0]].telefono);
            fflush(stdin);
            n = 2;
            break;
        case 5:
            do
            { // Modo de contacto favorito mediante menu
                printf("\nSeleccione metodo de comunicacion preferido:\n [1] Telefono\n [2] Correo\n");
                scanf("%d", &aux);
                switch (aux)
                {
                case 1:
                    strcpy(clientes[num_fila[0]].contactof, "Telefono");
                    n = 2;
                    break;
                case 2:
                    strcpy(clientes[num_fila[0]].contactof, "Correo");
                    n = 2;
                    break;
                default:
                    printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
                    n = 0;
                    break;
                }
            } while (n < 1);
            fflush(stdin);
            n = 2;
            break;
        /*case 6:
            do //Comprobación username vacio
            {
                printf("\nIngrese nuevo nombre de usuario: "); // nombre de usuario
                fflush(stdout);
                fgets(nuevo, 15, stdin);
                if (nuevo[1] != '\0')
                {
                    nuevo[strcspn(nuevo, "\n")] = 0;
                    conteo = 1;
                    for (i = 0; i < 100; i++)
                    { // Comprobacion en base de datos
                        if (strcmp(nuevo, clientes[i].username) == 0)
                        {
                            printf("\nEste nombre de usuarios se encuentra registrado\n");
                            i = 100;
                            conteo = 0;
                        }
                    }
                }
                else
                {
                    printf("\nInserte un dato\n");
                    conteo = 0;
                }

            } while (conteo == 0);

            strcpy(clientes[num_fila[0]].username, nuevo);
            fflush(stdin);
            n = 2;
            break;*/
        case 6:
            do
            { /*Coincidan las claves*/
                do
                { /*No claves Vacias*/
                    printf("\nIngrese una nueva clave de seguridad:\n");
                    fgets(nuevo, 20, stdin);
                    nuevo[strcspn(nuevo, "\n")] = 0;
                    strcpy(clientes[num_fila[0]].clave, nuevo);
                    fflush(stdin);
                    if (clientes[num_fila[0]].clave[1] != '\0')
                    {
                        printf("\nCompruebe su clave de seguridad:\n");
                        fgets(comprClave, 10, stdin);
                        comprClave[strcspn(comprClave, "\n")] = 0;
                        fflush(stdin);
                        if (strcmp(clientes[num_fila[0]].clave, comprClave) == 0)
                        {
                            n = 2;
                        }
                        else
                        {
                            printf("\n\nLas claves NO son iguales, por favor ingresa de nuevo\n");
                            n = 0;
                        }
                    }
                    else
                    {
                        printf("\nNo puedes ingresar datos vacios");
                        n = 0;
                    }
                } while (n < 1);
            } while (n < 1);
            n = 2;
            break;
        case 7:
            do /*Comprobación dia de nacimiento vacio*/
            {
                printf("Ingrese nueva fecha de nacimiento:\n");
                fgets(nuevo, 20, stdin);
                nuevo[strcspn(nuevo, "\n")] = 0;
                strcpy(clientes[num_fila[0]].fechaNacimiento, nuevo);
                fflush(stdin);
                if (clientes[num_fila[0]].fechaNacimiento[1] != '\0')
                {
                    n = 1;
                }
                else
                {
                    printf("\nNo puedes ingresar datos vacios");
                    n = 0;
                }
            } while (n < 1);
        case 8:
            do /*Comprobación lugar de nacimiento vacio*/
            {
                printf("\nIngrese lugar de nacimiento: "); // Lugar de nacimiento
                fflush(stdout);
                fgets(nuevo, 20, stdin);
                nuevo[strcspn(nuevo, "\n")] = 0;
                fflush(stdin);
                if (nuevo != '\0')
                {
                    n = 1;
                }
                else
                {
                    printf("\nNo puedes ingresar datos vacios\n");
                    n = 0;
                }
            } while (n < 1);
            nuevo[strcspn(nuevo, "\n")] = 0;
            strcpy(clientes[num_fila[0]].lugarNacimiento, nuevo);
            fflush(stdin);
            n = 2;
            break;
        case 9:
            do
            {
                printf("\nSeleccione su género:\nFemenino[1]\nMasculino[2]\nNo especificar[3]\n"); // Género mediante menu
                scanf("%d", &aux);
                switch (aux)
                {
                case 1:
                    strcpy(clientes[num_fila[0]].genero, "Femenino");
                    n = 2;
                    break;
                case 2:
                    strcpy(clientes[num_fila[0]].genero, "Masculino");
                    n = 2;
                    break;
                case 3:
                    strcpy(clientes[num_fila[0]].genero, "Sin especificar");
                    n = 2;
                    break;
                default:
                    printf("\n No ingresaste una opcion valida, selecciona nuevamente:");
                    n = 0;
                    break;
                }
            } while (n < 1);
            fflush(stdin);
            n = 2;
            break;
        case 10: return;break;    
        default:
            printf("\nNo es una de las opciones");
            n = 0;
        }
    } while (n < 1);
    actualizarBDClientes();
    return 0;
}

/*Muestra los datos del cliente*/
void mostrarDatosCliente(int filaDelCliente)
{
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
void operacionCliente()
{

    int n = 0;
    int accionCliente;
    do
    {
        printf("\nQue deseas Realizar? \n");
        printf(" [1] Modificar datos\n [2] Ver catalogo de compra\n [3] Ver mis datos\n [4] Realizar pedido\n [5] Menu principal\n [6] Salir\nIngrese su respuesta:\t");
        fflush(stdout);
        scanf("%i", &accionCliente);
        switch (accionCliente)
        {
        case 1:
            modificarCliente();
            n = 0;
            break;
        case 2:
            mostrar10Productos();
            fflush(stdout);
            n = 0;
            break;
        case 3:
            mostrarDatosCliente(num_fila[0]);
            fflush(stdout);
            n = 0;
            break;
        case 4:
            printf("\n\n**Operacion en construccion**\n\n");
            //crearOrd(nuevaOrden());
            n = 0;
            break;
        case 5:
            n = 1;
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("\nOpción invalida\n");
            n = 0;
            break;
        };
    } while (n == 0);
}

/*Inicia sesión*/
int ingresar()
{

    printf("\nIngresa tu nombre de usuario:\t");
    fflush(stdout);
    char usuario[20];
    char clave[20];
    char operacion[2];
    scanf("%s", usuario);

    abrirBDDClientes();
    for (int i = 0; i < count_c[0]; i++)
    {
        if (!strcmp(usuario, clientes[i].username))
        {

            num_fila[0] = i;
            printf("Ahora inserte su clave:\n");
            fflush(stdout);
            scanf("%s", clave);
            int n = 4, i;
            for (i = 0; i < 3; i++)
            {
                if (!strcmp(clave, clientes[num_fila[0]].clave))
                {

                    printf("\n\n****Sesion iniciada****\n\n");
                    fflush(stdout);
                    operacionCliente();
                }
                else
                {
                    n--;
                    printf("Clave incorrecta %d intentos restantes\nIngrese su clave:\n", n);
                    fflush(stdout);
                    scanf("%s", clave);
                }
            }
            printf("\nHa alcanzado el limite de intentos\n");
            main();
        }
        else if (i == count_c[0] - 1 && strcmp(usuario, clientes[num_fila[0]].username))
        {

            printf("\nEl usuario '%s' no se encuentra registrado\n", usuario);
            return 1;
        }
    };
    return 0;
}

/*Actualiza la base de datos con datos modificados*/
int actualizarBDClientes()
{

    FILE *bddcsv;

    bddcsv = fopen("clientes.csv", "w");

    if (bddcsv == NULL)
    {
        printf("Error al abrir la base de datos\n");
        return 1;
    }

    for (int fila = 0; fila < count_c[0] + 2; fila++)
    {

        if (fila == 0)
        {
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

        if (fila < count_c[0] && fila > 0)
        {
            fprintf(bddcsv,
                    "%s;%s;%s;%lu;%s;%s;%s;%s;%s;%s",
                    clientes[fila - 1].nombre,
                    clientes[fila - 1].correo,
                    clientes[fila - 1].direccion,
                    clientes[fila - 1].telefono,
                    clientes[fila - 1].contactof,
                    clientes[fila - 1].username,
                    clientes[fila - 1].clave,
                    clientes[fila - 1].fechaNacimiento,
                    clientes[fila - 1].lugarNacimiento,
                    clientes[fila - 1].genero);
        };

        if (ferror(bddcsv))
        {
            printf("No se pudo agregar el cliente\n");
            return 1;
        };
    };

    fclose(bddcsv);
    printf("\nSe actualizo exitosamente a la base de datos\n");
    return 0;
};

/*Inicia sesión Invitado*/
int ingresarInvitado()
{

    int n = 0;
    int accionCliente;
    do
    {
        printf("\nQue deseas Realizar? \n");
        printf(" [1] Registrarte\n [2] Iniciar sesion\n [3] Ver catalogo de productos\n [4] Menu principal\n [5] Salir\nIngrese su respuesta:\t");
        fflush(stdout);
        scanf("%i", &accionCliente);
        fflush(stdin);
        switch (accionCliente)
        {
        case 1:
            guardarCliente(nuevoCliente());
            n = 0;
            break;
        case 2:
            ingresar();
            n = 0;
            break;
        case 3:
            mostrarBDDProductos();
            fflush(stdout);
            n = 0;
            break;
        case 4:
            n = 1;
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\nOpción invalida\n");
            n = 0;
            break;
        };
    } while (n == 0);
}

/*Inicia sesión NuevoRegistro*/
int ingresarNuevoRegistro()
{

    int n = 0;
    int accionCliente;
    do
    {
        printf("\nQue deseas Realizar? \n");
        printf(" [1] Iniciar sesion\n [2] Ingresar como invitado\n [3] Menu principal\n [4] Salir\nIngrese su respuesta:\t");
        fflush(stdout);
        scanf("%i", &accionCliente);
        fflush(stdin);
        switch (accionCliente)
        {
        case 1:
            ingresar();
            n = 0;
            break;
        case 2:
            ingresarInvitado();
            n = 0;
            break;
        case 3:
            n = 1;
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nOpción invalida\n");
            n = 0;
            break;
        };
    } while (n == 0);
}