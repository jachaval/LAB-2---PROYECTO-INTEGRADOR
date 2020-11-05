#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
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

bool Partido::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Torneo),1,pArchivo);
    fclose(pArchivo);
    return guardo;
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
