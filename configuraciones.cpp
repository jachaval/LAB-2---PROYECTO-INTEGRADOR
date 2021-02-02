#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <fstream>
using namespace std;
#include "configuraciones.h"
#include "equipo.h"
#include "interfaz.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
#include <ctime>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"
#include "partido.h"
#include "equipo.h"

void exportar_a_texto(){

    int opcion,i;
	do{
        system("cls");
        title("TORNEO DE FÚTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);

        for (i = 0; i < 24; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(9, 4); printf("EXPORTAR DATOS ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(27, 4); printf("*");
        }

        gotoxy(1,6);
        cout << "    1. EXPORTAR EQUIPOS" << endl;
        cout << "    2. EXPORTAR JUGADORES" << endl;
        cout << "    3. EXPORTAR PARTIDOS" << endl;
        cout << "    4. EXPORTAR TORNEOS " << endl;
        cout << "    0. SALIR" << endl;
        cout << "    ------------------------------" << endl;

        cout <<"    Opción-> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls();
                exportar_equipos();
                break;
            case 2:
                cls();
                exportar_jugadores();
                break;
            case 3:
                cls();
                exportar_partidos();
                break;
            case 4:
                cls();
                exportar_torneos();
                break;
            case 0:	return;
            break;
        }
	} while (opcion != 0);
}

void exportar_equipos(){
    ofstream archivo;
    archivo.open("datos texto/equipos.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_EQUIPOS,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Equipo eq;

    archivo<<"NRO EQUIPO,NOMBRE,PG,PP,GF,GC"<<endl;
	while(fread(&eq, sizeof (Equipo), 1 , p)){
        archivo<<eq.getNro_equipo()<<","<<eq.getNombre_equipo()<<","<<eq.getPartidos_ganados()<<","<<eq.getPartidos_perdidos()<<","<<eq.getGoles_afavor()<<","<<eq.getGoles_encontra()<<endl;
    }
	fclose(p);
    archivo.close();

    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void exportar_jugadores(){
    ofstream archivo;
    archivo.open("datos texto/jugadores.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_JUGADORES,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Jugador ju;

    archivo<<"NRO EQUIPO,NOMBRE,APELLIDO,POSICION,NRO CAMISETA,GOLES,ASISTENCIAS,T. ROJAS,T. AMARILLAS"<<endl;
	while(fread(&ju, sizeof (Jugador), 1 , p)){
        archivo<<ju.getNro_equipo()<<","<<ju.getNombre()<<","<<ju.getApellido()<<","<<ju.getPosicion()<<","<<ju.getNro_camiseta()<<","<<ju.getCant_goles()<<","<<ju.getAsistencias()<<","<<ju.getTarjeta_roja()<<","<<ju.getTarjeta_amarilla()<<endl;
    }
	fclose(p);
    archivo.close();

    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void exportar_partidos(){
    ofstream archivo;
    archivo.open("datos texto/partidos.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_PARTIDOS,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO PARTIDOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Partido par;

    archivo<<"CODIGO TORNEO,EQUIPO LOCAL,EQUIPO VISITANTE,GOLES LOCAL,GOLES VISITANTE,EQUIPO GANADOR,INSTANCIA,NRO PARTIDO"<<endl;
	while(fread(&par, sizeof (Partido), 1 , p)){
        archivo<<par.getCodigo_toneo()<<","<<par.getEquipo_local()<<","<<par.getEquipo_visitante()<<","<<par.getGoles_local()<<","<<par.getGoles_visitante()<<","<<par.getEquipo_ganador()<<","<<par.getInstancia_torneo()<<endl;
    }
	fclose(p);
    archivo.close();
    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}

void exportar_torneos(){
    ofstream archivo;
    archivo.open("datos texto/torneos.txt", ios::out);
    if(archivo.fail()){
        cout<<"   ERROR DE ARCHIVO";
        return;
    }

    FILE*p;
    p=fopen(FILE_TORNEOS,"rb");
    if (p == NULL) {
        msj("ERROR DE ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Torneo tor;

    archivo<<"TIPO TORNEO,CODIGO TORNEO,INSTANCIA,PARTIDOS JUGADOS,TORNEO ACTIVO"<<endl;
	while(fread(&tor, sizeof (Torneo), 1 , p)){
        archivo<<tor.getTipo_torneo()<<","<<tor.getCodigo_torneo()<<","<<tor.getInstancia_torneo()<<","<<tor.getPartidos_jugados()<<","<<tor.getTorneo_activo()<<endl;
	}
	fclose(p);
    archivo.close();
    msj("ARCHIVO EXPORTADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
}
