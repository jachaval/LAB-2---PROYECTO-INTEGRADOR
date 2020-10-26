#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
using namespace std;
#include "menu.h"
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "equipo.h"
#include "jugador.h"
#include "torneo.h"

void menu_principal(){

    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("MENÚ PRINCIPAL ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        cout << "    1. INICAR TORNEO" << endl;
        cout << "    2. CONTINUAR TORNEO" << endl;
        cout << "    3. CONFIGURACIONES " << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                    cls();
                    menu_iniciar_torneo();
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

void menu_iniciar_torneo(){
    int opcion,i, cant_equipos;

	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        setColor(RED);
        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("INICIAR TORNEO");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }
        setColor(WHITE);

        gotoxy(1,6);
        cout << "    1. SELECCIONAR TORNEO" << endl;
        cout << "    2. CARGAR EQUIPO Y JUGADORES" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                FILE*pArchivo;
                pArchivo=fopen(FILE_TORNEOS,"rb");
                if (pArchivo==NULL){ /// VERFICO ATRAVES DE LA APERTURA LA EXISTENCIA DEL ARCHIVO POR LO TANTO TAMBIEN SE INICIO UN TORNEO
                    cant_equipos=seleccionar_torneo();
                }
                else {
                    cout<< "    YA HAY UN TORNEO ACTIVO"<<endl;
                    anykey();
                    fclose(pArchivo);
                }
                break;
            case 2:
                cls();
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy (1,3);
                int cantidad_equipos;
                int cant_equiposCargados;
                Torneo reg;
               /* FILE*p;
                p=fopen(FILE_TORNEOS,"rb");
                fread(&reg, sizeof (Torneo),1,p);
                */
                cantidad_equipos=informar_tipoTorneo(); ///devuelve la cantidad de equipos total del torneo seleccionado.
                cant_equiposCargados=contar_equiposCargados(); //devuelve la cantidad de los equipos cargados, si ya estan todo no permite cargar mas
                cout<< "    EQUIPOS CARGADOS HASTA EL MOMENTO: "<< cant_equiposCargados<<" de " << cantidad_equipos<<endl<<endl;
                if(cant_equiposCargados==cantidad_equipos){
                    cout<<"    YA ESTÁN TODOS LOS EQUIPOS CARGADOS. CONTINUE TORNEO"<<endl;
                    anykey();
                }
                else{
                    ingresar_equipos(cant_equipos); //agrega todos los equipos y jugadores y los guarda en equipos.dat
                }
                break;
            case 3:

                break;
            case 4:
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

int seleccionar_torneo(){
    int torneo, cant_equipos;
    char seguro;
    cout<<"    Seleccionar torneo:"<<endl<<endl;
    cout<<"    1 - 32vos = 64 EQUIPOS "<<endl;
    cout<<"    2 - 16vos = 32 EQUIPOS"<<endl;
    cout<<"    3 - 8vos  = 16 EQUIPOS"<<endl;
    cout<<"    4 - 4tos  = 8 EQUIPOS"<<endl<<endl;

    cout<<"    Opción-> ";
    cin>> torneo;

    if(torneo==1) cant_equipos=64;
    if(torneo==2) cant_equipos=32;
    if(torneo==3) cant_equipos=16;
    if(torneo==4) cant_equipos=8;

    cout<< endl<< "    HA SELECCIONADO EL TORNEO PARA "<< cant_equipos << " EQUIPOS"<<endl;
    cout<< endl<< "    ¿ESTÁ SEGURO DE LA ELECCIÓN? (S/N)"; ///FALTARIA AGREGAR VALIDACION POR INGRESOS INCORRECTOS
    cin>>seguro;
    if(seguro=='N' || seguro=='n') {
        cout<<endl << "    VUELVA A SELECCIONAR TORNEO"<<endl;
        return 0;
    }
    cout<<endl << "    TORNEO SELECCIONADO CORRECTAMENTE"<<endl;
    anykey();

    Torneo tor;
    tor.setTipo_torneo(cant_equipos);
    tor.guardarEnDisco();

    return cant_equipos;
}

void menu_ver_torneo(){


    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("RESULTADOS DEL TORNEO ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        cout << "    1. CARGAR PARTIDOS" << endl;
        cout << "    2. MOSTRAR ESTADISTICAS" << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                    cls();

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}


void menu_estadisticas(){


    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("ESTADISTICAS DEL TORNEO ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        cout << "    1. RESULTADOS  " << endl;
        cout << "    2. GOLEADORES  " << endl;
        cout << "    3. ASISTENCIAS " << endl;
        cout << "    4. TARJETAS ROJAS " << endl;
        cout << "    5. TARJETAS AMARILLAS " << endl;
        cout << "    6. BUSCAR JUGADOR " << endl;
        cout << "    7. BUSCAR EQUIPO " << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                    cls();

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}






