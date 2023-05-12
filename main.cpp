#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <ctime>
#include <locale.h>

using namespace std;

const char lib[15]="libros.dat";
const char libBKP[15]="libros.bkp";
const char lib2[15]="libros.dlt";


const char  cli[15]="clientes.dat";
const char  clibkp[15]="clientes.bkp";
const char  cli2[15]="clientes.dlt";

const char  ven[15]="ventas.dat";
const char  venbkp[15]="ventas.bkp";
const char  ven2[15]="ventas.dlt";



#include "Clases.h"
#include "checks.h"
#include "Prototipos.h"
#include "Fecha.h"
#include "Menus.h"
#include "Configuracion.h"
#include "Libro.h"
#include "Clientes.h"
#include "Venta.h"


int main()
{
    int opc;

    while(true)
    {

        Borrar();


    /*  time_t tiempo;
        struct tm *tmPtr;
        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);
        int anio=tmPtr->tm_year+1900;
        int mes=tmPtr->tm_mon+1;
        int dia=tmPtr->tm_mday;

    */


        setlocale(LC_CTYPE,"SPANISH");




        MsjMenuPrincipal();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                Menu_Libro();
            break;
            case 2:
                Menu_Cliente();
            break;
            case 3:
                Menu_Ventas();
            break;
            case 4:
                Menu_Configuracion();
            break;
            case 0:
                return 0;
            break;
            default:
                OpcionError();
            break;
        }
        ///////////////////////////////////////
        Pausa();
    }


    return 0;
}
