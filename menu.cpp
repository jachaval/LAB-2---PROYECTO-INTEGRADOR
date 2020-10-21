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

void menu_principal(){

    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FUTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        //gotoxy(1, 3);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("MENÚ PRINCIPAL ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        //cout << "    MENÚ PRINCIPAL" << endl<<endl;
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
    title("TORNEO DE FUTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
    int torneo, cant_equipos;
    char seguro;
    gotoxy(1,3);
    cout<<"    Seleccionar torneo:"<<endl;
    cout<<"    1 - 32vos"<<endl;
    cout<<"    2 - 16vos"<<endl;
    cout<<"    3 - 8vos"<<endl;
    cout<<"    4 - 4tos"<<endl;

    cout<<"    Opción-> ";
    cin>> torneo;

    cout<< "    ¿ESTÁ SEGURO DE LA ELECCIÓN? (S/N)";
    cin>>seguro;
    if(seguro=='N' || seguro=='n') return;



    if(torneo==1) cant_equipos=64;
    if(torneo==2) cant_equipos=32;
    if(torneo==3) cant_equipos=16;
    if(torneo==4) cant_equipos=8;

    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FUTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

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
        cout << "    1. INGRESAR EQUIPO" << endl;
        cout << "    2. CONTINUAR TORNEO" << endl;
        cout << "    3. CONFIGURACIONES " << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                    cls();
                    ingresar_equipo(cant_equipos); //agrega todos los equipos y jugadores y los guarda en equipos.dat
                    anykey();
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

