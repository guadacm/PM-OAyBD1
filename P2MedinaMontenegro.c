/* ORGANIZACION DE ARCHIVOS y BASE DE DATOS I
    Práctico de máquina Nro 2 - Año 2017

-- Integrantes: MEDINA, Guadalupe
                MONTENEGRO, Luis

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P 0.75  //Ro
#define N 650
#define M 877   //M = N/P = 866.66. El Nº primo siguiente a M es 877

typedef struct
{
    char Cod_Socio[8];
    char Cod_copia[8];
    char P_fecha_prestamo[10];
    char P_fecha_dev[10];
} Prestamo;

Prestamo RAL[M];
int cant_Prestamos = 0;

/* VARIABLES */
int opcion = -1;
/* END VARIABLES */

/* PROTOTYPE */
void encabezado();
void init();
int hashing (char[]);
int alta(Prestamo);
int localizar(char[], char[], int*, int*);
void mostrar();
void memorizacion_previa();
/* END PROTOTYPE */

void encabezado()
{
    system("cls");
    printf("\n **************************************************\n"
           " *** ORGANIZACION DE ARCHIVOS Y BASE DE DATOS I ***\n"
           " **************************************************\n");
}

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
        case 0:
            break;

        case 1:
            memorizacion_previa();
            system("pause");
            break;

        case 5:
            printf("\n[4] Mostrar Estructura\n");
            if (cant_Prestamos==0) printf("\n\t Estructura VACIA...\n");
            else mostrar();
            system("pause");
            break;

            /*case 2:
            case 3:
            case 4:
            case 5:
            case 6:*/


        }
    }
    return 0;
}

void init()
{
    int i;
    for(i = 0; i < M; i++)      // Inicializo el RAL con la marca de celda virgen
        strcpy(RAL[i].Cod_Socio, "*");
}

int localizar(char codSoc[],char codCop[],int *h, int *pos) // en h guardo el valor que me da la funcion hashing, en pos, la posicion donde debe/deberia estar el elemento que busco
{
    *h = hashing(codSoc);
    *pos = *h;
    if(cant_Prestamos > 0)
    {
        int i = *h;
        int f = 0; // si esta en 1 me dice que ya guardo en pos una celda libre
        while((strcmp(RAL[i].Cod_Socio, codSoc)!= 0 || strcmp(RAL[i].Cod_copia, codCop)!= 0) && strcmp(RAL[i].Cod_Socio, "*")!= 0)
        {
            if(strcmp(RAL[i].Cod_Socio, "#") == 0 && f == 0)
            {
                *pos = i;
                f = 1;
            }
            i = (i + 1) % M;
        }
        if(strcmp(RAL[i].Cod_Socio, "*") == 0 && f == 0)
            *pos = i;
        if(strcmp(RAL[i].Cod_Socio, codSoc)== 0 && strcmp(RAL[i].Cod_copia, codCop)== 0)
        {
            *pos = i;
            return 1;
        }
        else
        {
            return 0;
        }

    }
    else
    {
        return 0;
    }
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

int alta(Prestamo nuevo)
{
    int h, pos;
    if(cant_Prestamos < M)
    {
        if(localizar(nuevo.Cod_Socio,nuevo.Cod_copia, &h, &pos) == 0)
        {
            RAL[pos] = nuevo;
            cant_Prestamos++;
            return 1;
        }
        else return 0;
    }
    else return 0;
}

void imprimirArt(Prestamo prestamo)
{
    printf("\n Codigo Socio: \t\t%s"
           "\n Codigo Copia: \t\t%s"
           "\n Fecha Prestamo: \t%s"
           "\n Fecha Devolucion: \t%s\n",
           prestamo.Cod_Socio,
           prestamo.Cod_copia,
           prestamo.P_fecha_prestamo,
           prestamo.P_fecha_dev);
}

void mostrar()
{
    int i, j = 1;    // j es para limitar las celdas que se muestran
    printf("\n\t----------LISTA DE PRESTAMOS----------\n"
           "\n\t     Cantidad de prestamos: %d\n", cant_Prestamos);
    for(i = 0; i < M; i++)
    {
        printf("\n Posicion: %d", i);
        if(strcmp(RAL[i].Cod_Socio, "*") == 0) // Celdaa virgen
        {
            printf("\t * Celda nunca usada\n");
            j++;
        }
        else
        {
            if(strcmp(RAL[i].Cod_Socio, "#") == 0) // Celda libre
            {
                printf("\t # Celda libre\n");
                j++;
            }

            else        // Celda ocupada
            {
                printf("\t - Celda ocupada por:");
                imprimirArt(RAL[i]);
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

void memorizacion_previa()
{
    Prestamo nuevo;
    FILE *fp;

    if ((fp = fopen("Lote_prestamo.txt", "r")) == NULL)
        printf("\n\nERROR: no se pudo abrir el archivo\n\n");
    else
    {
        while(!(feof(fp)))
        {
            fscanf(fp," %[^\n]",nuevo.Cod_Socio);
            strupr(nuevo.Cod_Socio);
            fscanf(fp," %[^\n]",nuevo.Cod_copia);
            fscanf(fp," %[^\n]",nuevo.P_fecha_prestamo);
            fscanf(fp," %[^\n]",nuevo.P_fecha_dev);
            alta(nuevo);
        }
        printf("\n\nLa memorizacion se ha llevado a cabo\n\n");
    }
    fclose(fp);
}

