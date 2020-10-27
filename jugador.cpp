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

void Jugador::setNro_equipo(int nro){nro_equipo=nro;}
void Jugador::setNombre(char *nom){strcpy(nombre,nom);}
void Jugador::setApellido(char *ap){strcpy(apellido,ap);}
void Jugador::setPosicion(char *pos){strcpy(posicion,pos);}
void Jugador::setTarjeta_roja(int roja){tarjeta_roja+=roja;}
void Jugador::setTarjeta_amarilla(int amarilla){tarjeta_amarilla+=amarilla;}
void Jugador::setAsistencias(int asis){asistencias+=asis;}
void Jugador::setCant_goles(int goles){cant_goles+=goles;}
void Jugador::setNro_camiseta(int nro){nro_camiseta=nro;}
int  Jugador::getNro_equipo(){return nro_equipo;}
char *Jugador::getNombre(){return nombre;}
char *Jugador::getApellido(){return apellido;}
char *Jugador::getPosicion(){return posicion;}
int  Jugador::getTarjeta_roja(){return tarjeta_roja;}
int  Jugador::getTarjeta_amarilla(){return tarjeta_amarilla;}
int  Jugador::getAsistencias(){return asistencias;}
int  Jugador::getCant_goles(){return cant_goles;}
int Jugador::getNro_camiseta(){return nro_camiseta;}

bool Jugador::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Jugador),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

