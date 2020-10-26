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
        cout << "    3. ESTADÍSTICAS E INFORMES " << endl;
        cout << "    4. CONFIGURACIONES " << endl;
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
                system("cls");
                title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
                gotoxy(1,3);

                listar_equipos();
                anykey();
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

                cantidad_equipos=informar_tipoTorneo(); ///devuelve la cantidad de equipos total del torneo seleccionado.
                cant_equiposCargados=contar_equiposCargados(); //devuelve la cantidad de los equipos cargados, si ya estan todo no permite cargar mas

                if(cant_equiposCargados==cantidad_equipos){
                    if(cantidad_equipos>0){
                        cout<<"    YA ESTÁN TODOS LOS EQUIPOS CARGADOS. CONTINUE TORNEO"<<endl;
                        anykey();
                    }
                    else{
                        cout<<"    PRIMERO SELECCIONE EL TORNEO PARA PODER CARGAR LOS EQUIPOS"<<endl;
                        anykey();
                    }
                }
                else{
                    cout<< "    EQUIPOS CARGADOS HASTA EL MOMENTO: "<< cant_equiposCargados<<" de " << cantidad_equipos<<endl<<endl;
                    ingresar_equipos(cant_equipos); //agrega todos los equipos y jugadores y los guarda en equipos.dat
                }
                break;
            case 3:
                    listar_equipos();
                break;
            case 4:
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}


