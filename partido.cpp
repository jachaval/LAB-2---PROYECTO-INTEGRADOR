#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "equipo.h"
#include "jugador.h"
#include "torneo.h"
#include "partido.h"

void Partido::setCodigo_toneo(int cod){codigo_toneo=cod;}
void Partido::setEquipo_local(int equipo){equipo_local=equipo;}
void Partido::setEquipo_visitante(int equipo){equipo_visitante=equipo;}
void Partido::setGoles_local(int goles){goles_local=goles;}
void Partido::setGoles_visitante(int goles){goles_visitante=goles;}
void Partido::setEquipo_ganador(int equipo){equipo_ganador=equipo;}
void Partido::setInstancia_torneo(int instancia){instancia_torneo=instancia;}
void Partido::setNro_partido(int partido){nro_partido=partido;}
int Partido::getCodigo_toneo(){return codigo_toneo;}
int Partido::getEquipo_local(){return equipo_local;}
int Partido::getEquipo_visitante(){return equipo_visitante;}
int Partido::getGoles_local(){return goles_local;}
int Partido::getGoles_visitante(){return goles_visitante;}
int Partido::getEquipo_ganador(){return equipo_ganador;}
int Partido::getInstancia_torneo(){return instancia_torneo;}
int Partido::getNro_partido(){return nro_partido;}
bool Partido::escribrirEnDisco(){}

Partido::Partido(){
    codigo_toneo;
    equipo_local=0;
    equipo_visitante=0;
    goles_local=0;
    goles_visitante=0;
    equipo_ganador=0;
    instancia_torneo=0;
    nro_partido=0;
}

bool Partido::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Partido),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

void Partido::aumentar_partidos_jugados(){
    nro_partido++;
}

void cargar_partido(int numeroEquipo1,int numeroEquipo2, int golesEquipo1, int golesEquipo2, int equipo_ganador, int instancia_torneo){
    Partido par;
    FILE* pArchivo;
    pArchivo=fopen(FILE_PARTIDOS, "ab");
    if(pArchivo=NULL){
        msj("ERROR ARCHIVO PARTIDO",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }

    par.setEquipo_local(numeroEquipo1);
    par.setEquipo_visitante(numeroEquipo2);
    par.setGoles_local(golesEquipo1);
    par.setGoles_visitante(golesEquipo2);
    par.setEquipo_ganador(equipo_ganador);
    par.setInstancia_torneo((instancia_torneo/2));

    par.guardarEnDisco();

    fclose(pArchivo);
}

void listar_partidos(){
    FILE *pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO PARTIDOS", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    Partido par;
    cout << left;
    cout << setw(11) << "Cod Torneo" << setw(20) << "|Equipo Local" << setw(4) << "|Equipo Visitante" << setw(4) << "|Goles Local" << setw(4) << "|Goles Visitante" << setw(4) << "|Equipo Ganador"<< setw(4) << "|Instancia Torneo" << setw(4) << "|Número Partido";
    cout << endl << "---------------------------------------------------------------------------------------------" << endl;
    while(fread(&par, sizeof (Partido), 1, pArchivo)==1){
        cout << setw(12);
        cout << par.getCodigo_toneo();
        cout << setw(20) ;
        cout << par.getEquipo_local();
        cout << setw(4) ;
        cout << par.getEquipo_visitante();
        cout << setw(4) ;
        cout << par.getGoles_local();
        cout << setw(4) ;
        cout << par.getGoles_visitante();
        cout << setw(4) ;
        cout << par.getEquipo_ganador();
        cout << setw(4) ;
        cout << par.getInstancia_torneo();
        cout << setw(4) ;
        cout << par.getNro_partido();
        cout << endl;


    }
    anykey();
    fclose(pArchivo);
}
