/* ORGANIZACION DE ARCHIVOS y BASE DE DATOS I
    Práctico de máquina Nro 2 - Año 2017

-- Integrantes: MEDINA, Guadalupe
                MONTENEGRO, Luis

*/

#include <stdio.h>
#include <stdlib.h>

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

/* VARIABLES */
int opcion = -1;
/* END VARIABLES */

/* PROTOTYPE */
void encabezado();
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
        /*case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:*/
        }
    }
    return 0;
}
