/* ORGANIZACION DE ARCHIVOS y BASE DE DATOS I
    Práctico de máquina Nro 2 - Año 2017

-- Grupo Nº 1
-- Integrantes: MEDINA, Guadalupe
                MONTENEGRO, Luis

------------------------------------------ NOTAS y ACLARACIONES: ------------------------------------------

 * M = N/p, N=650, p=0.75, como M tomo el numero primo mas proximo al techo del resultado de la division
   M = techo(650/0.75)= 867, entonces M = 877.

-- RAL:
 * "*" celda virgen (nunca usada).
 * "#" celda libre (antes ocupada, ahora libre).
 * Inicializamos el RAL poniendo "*" en el campo Cod_socio.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P 0.75  //Ro
#define N 650
#define M 877   //M = N/P = 866.66. El Nº primo siguiente a M es 877
//#define M 11   // M=8/0.75= 10.66 -> M=11

typedef struct
{
    char Cod_socio[8];
    char Cod_copia[8];
    char P_fecha_prestamo[10];
    char P_fecha_dev[10];
} Prestamo;

/* VARIABLES */
int opcion = -1;
Prestamo RAL[M]; //Definicion del Rebalse Abierto Lineal, de dimensión M.
int cant_Prestamos = 0; // Cantidad de elementos almacenados en el RAL.

char x_int[8];
int i_int;
int consultas;
int celda_libre;
Prestamo buscar;
/* END VARIABLES */

/* PROTOTYPE */
void encabezado();
void init();
int localizar(char codSoc[],char codCop[]);
void Inicio(char cod_s[]);
int Hay_mas();
void Deme_otro();
int hashing (char codSoc[]);
int alta(Prestamo nuevo);
int baja(Prestamo borrar);
void evocacion_multiple(char codSoc[]);
void mostrar_tupla(Prestamo prestamo);
void mostrar();
void guardar();
void cargar();
void memorizacion_previa();
/* END PROTOTYPE */

int main()
{
    init();
    while (opcion != 0)
    {
        encabezado();
        // MENU
        printf("\n\t[1] Memorizacion previa"
               "\n\t[2] Evocacion"
               "\n\t[3] Alta"
               "\n\t[4] Baja"
               "\n\t[5] Mostrar"
               "\n\t[6] Cargar"
               "\n\n\t[0] Salir\n"
               "\n\tElija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0: { // Salir
                guardar();
                system("pause");
                break;
            }
            case 1: { // Memorizacion Previa
                memorizacion_previa();
                system("pause");
                break;
            }
            case 2: { // Evocacion
                encabezado();
                if (cant_Prestamos != 0)
                {
                    char codigo[8];
                    printf("\n Ingrese el Codigo de Socio que desea consultar: ");
                    fflush(stdin);
                    scanf("%s", codigo);
                    strupr(codigo);
                    evocacion_multiple(codigo);
                }
                else printf("\n\t Estructura VACIA...\n\n");
                system("pause");
                break;
            }
            case 3: { // Alta
                encabezado();
                Prestamo nuevo;
                printf("\n Nuevo Prestamo"       // Ingreso de datos del nuevo prestamo
                       "\n\n Codigo de Socio: ");
                fflush(stdin);
                scanf(" %[^\n]", nuevo.Cod_socio);
                strupr(nuevo.Cod_socio);
                printf(" Codigo de Copia: ");
                fflush(stdin);
                scanf(" %[^\n]",nuevo.Cod_copia);
                printf(" Fecha de Prestamo (DD/MM/AA): ");
                fflush(stdin);
                scanf(" %[^\n]",nuevo.P_fecha_prestamo);
                printf(" Fecha de Devolucion (DD/MM/AA: ");
                fflush(stdin);
                scanf(" %[^\n]",nuevo.P_fecha_dev);
                if(alta(nuevo) == 1) printf("\n El prestamo fue agregado con exito\n\n"); // Alta exitosa
                else printf("\nError!!\n\n");          // Alta fracasa
                system("pause");
                break;
            }
            case 4: { // Baja
                encabezado();
                if (cant_Prestamos != 0)
                {
                    Prestamo borrar;
                    printf("\n Eliminar Prestamo"   // Ingreso datos del prestamo que quiero dar de baja
                           "\n\n Codigo de Socio: ");
                    fflush(stdin);
                    scanf(" %[^\n]", borrar.Cod_socio);
                    strupr(borrar.Cod_socio);
                    printf(" Codigo de Copia: ");
                    fflush(stdin);
                    scanf(" %[^\n]", borrar.Cod_copia);
                    strupr(borrar.Cod_copia);
                    if(baja(borrar) == 1) printf("\nEl pretamo fue eliminado con exito\n\n"); // Baja exitosa
                    else printf("\nError!!\n\n"); // Baja no exitosa
                }
                else printf("\n\t Estructura VACIA...\n\n");
                system("pause");
                break;
            }
            case 5: { // Mostrar Estructura
                printf("\n Mostrar Estructura\n");
                if (cant_Prestamos == 0)
                {
                    encabezado();
                    printf("\n\t Estructura VACIA...\n\n");
                }
                else mostrar();
                system("pause");
                break;
            }
            case 6: { // Cargar
                cargar();
                system("pause");
                break;
            }
        }
    }
    return 0;
}

void encabezado()
{
    system("cls");
    printf("\n **************************************************\n"
           " *** ORGANIZACION DE ARCHIVOS Y BASE DE DATOS I ***\n"
           " **************************************************\n");
}

void init() // Inicializa la estructura
{
    cant_Prestamos = 0;
    int i;
    for(i = 0; i < M; i++)      // Inicializo el RAL con la marca de celda virgen
        strcpy(RAL[i].Cod_socio, "*");
}

int localizar(char codSoc[],char codCop[]) // Se usa para altas y bajas.
{
    Inicio(codSoc);
    while (Hay_mas() != 0)
    {
        Deme_otro();
        if (strcmp(buscar.Cod_copia, codCop) == 0) {return 1;}

    }
    return 0;
}

void Inicio(char cod_s[])
{
    strcpy(x_int, cod_s);
    i_int = hashing(x_int);
    consultas = 0;
    celda_libre = -1;
}

int Hay_mas() // Devuelve 1 si encontro una tupla con el codigo buscado, sino devuelve 0.
{
    while (strcmp(RAL[i_int].Cod_socio, x_int) != 0 && strcmp(RAL[i_int].Cod_socio, "*") != 0 && consultas < M)
    {
        if (strcmp(RAL[i_int].Cod_socio, "#") == 0 && celda_libre == -1) {celda_libre = i_int;}
        i_int = (i_int + 1) % M;
        consultas++;
    }
    if(strcmp(RAL[i_int].Cod_socio, x_int) == 0) return 1;
    else
    {
        if(strcmp(RAL[i_int].Cod_socio, "*") == 0 && celda_libre == -1) {celda_libre = i_int;}
        return 0;
    }
}

void Deme_otro() // Devuelve la tupla encontrada en la variale buscar
{
    strcpy(buscar.Cod_socio, x_int);
    strcpy(buscar.Cod_copia, RAL[i_int].Cod_copia);
    strcpy(buscar.P_fecha_prestamo, RAL[i_int].P_fecha_prestamo);
    strcpy(buscar.P_fecha_dev, RAL[i_int].P_fecha_dev);
    i_int = (i_int + 1) % M;
}

int hashing (char codSoc[])
{
    int longitud,i;
    int acumulador=0;
    longitud=strlen(codSoc);
    for (i=0; i< longitud ; i++)
        acumulador+=( ((int) codSoc[i] ) * (i+1) );
    return((acumulador)% M );
}

int alta(Prestamo nuevo) //Da de alta en la estructura la tupla del parametro.
{
    if(cant_Prestamos < M)
    {
        if(localizar(nuevo.Cod_socio, nuevo.Cod_copia) == 0)
        {
            RAL[celda_libre] = nuevo;
            cant_Prestamos++;
            return 1;
        }
        else return 0;
    }
    else return 0;
}

int baja(Prestamo borrar) // Da de baja de la estructura la tupla del parametro
{
    if(localizar(borrar.Cod_socio, borrar.Cod_copia) == 1)
    {
        char c = 'N';

        mostrar_tupla(buscar);
        printf("\n Confirma que desea eliminar este prestamo? Y/N. ");
        fflush(stdin);
        scanf("%c", &c);
        if (c == 'Y' || c == 'y')
        {
            strcpy(RAL[i_int-1].Cod_socio, "#"); // i_int -1 porque cuando en localizar() se llama a deme_otro el indice queda en la siguiente celda
            cant_Prestamos--;
            return 1;
        }
        else return 0;
    }
    else return 0;
}

void evocacion_multiple(char codSoc[]) // Muestra las tuplas que encuentra con el Codigo de Socio codSoc.
{
    int cant = 0;
    Inicio(codSoc);
    while (Hay_mas() != 0)
    {
        Deme_otro();
        mostrar_tupla(buscar);
        cant++;
    }
    if (cant == 0) printf("\n El Codigo de Socio %s no existe\n", codSoc);
    else printf("\n Se encontraron %d coincidencias\n", cant);
    printf("\n");
}

void mostrar_tupla(Prestamo prestamo) // Muestra por pantalla la tupla del parametro
{
    printf("\n\t Codigo Socio: \t\t%s"
           "\n\t Codigo Copia: \t\t%s"
           "\n\t Fecha Prestamo: \t%s"
           "\n\t Fecha Devolucion: \t%s\n",
           prestamo.Cod_socio,
           prestamo.Cod_copia,
           prestamo.P_fecha_prestamo,
           prestamo.P_fecha_dev);
}

void mostrar() // Muestra la estructura completa.
{
    int i, j = 1;    // j es para limitar las celdas que se muestran
    encabezado();
    printf("\n\t----------LISTA DE PRESTAMOS----------\n"
           "\n\t     Cantidad de prestamos: %d\n", cant_Prestamos);
    for(i = 0; i < M; i++)
    {
        printf("\n Posicion: %d", i);
        if(strcmp(RAL[i].Cod_socio, "*") == 0) // Celdaa virgen
        {
            printf("\t * Celda nunca usada\n");
            j++;
        }
        else
        {
            if(strcmp(RAL[i].Cod_socio, "#") == 0) // Celda libre
            {
                printf("\t # Celda libre\n");
                j++;
            }

            else        // Celda ocupada
            {
                printf("\t - Celda ocupada por:");
                mostrar_tupla(RAL[i]);
                j++;    //Limitador de articulos a mostrar
            }
        }
        if(j % 8 == 0)
        {
            printf("\n");
            system("pause");
            j = 0;
        }
    }
}

void guardar() // Guarda la estructura en un archivo
{
    FILE *fp;
    encabezado();
    if ((fp = fopen ( "prestamo.str", "w+" )) == NULL)
        printf("\n\nERROR: no se pudo guardar el archivo\n\n");
    else
    {
        fprintf(fp,"%d",cant_Prestamos);
        fwrite(RAL,sizeof(Prestamo),M,fp);
        printf("\n\n\t El archivo se guardo con exito\n\n");
    }
    fclose(fp);
}

void cargar() // Carga los datos del archivo en la estructura
{
    FILE *fp;
    encabezado();
    if ((fp = fopen ( "prestamo.str", "r+" )) == NULL)
        printf("\n\nERROR: no se pudo leer el archivo\n\n");
    else
    {
        fscanf(fp,"%d",&cant_Prestamos);
        fread(RAL,sizeof(Prestamo),M,fp);
        printf("\n\n\t Carga de archivo exitosa\n\n");
        //printf("cant prestamos %d\n",cant_Prestamos);
    }
    fclose(fp);
}

void memorizacion_previa() // Lee tuplas de un archivo y los da de alta en la estructura.
{
    Prestamo nuevo;
    FILE *fp;

    if ((fp = fopen("Lote_prestamo.txt", "r")) == NULL)
        printf("\n\nERROR: no se pudo abrir el archivo\n\n");
    else
    {
        while(!(feof(fp)))
        {
            fscanf(fp," %[^\n]", nuevo.Cod_socio);
            strupr(nuevo.Cod_socio);
            fscanf(fp," %[^\n]", nuevo.Cod_copia);
            strupr(nuevo.Cod_copia);
            fscanf(fp," %[^\n]", nuevo.P_fecha_prestamo);
            fscanf(fp," %[^\n]", nuevo.P_fecha_dev);
            alta(nuevo);
        }
        encabezado();
        printf("\n\nLa memorizacion se ha llevado a cabo\n\n");
    }
    fclose(fp);
}

