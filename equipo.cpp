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

void Equipo::cargar(){
    cout<< "    ";
}
Equipo::Equipo(){}
void  Equipo::mostrar(){}
bool  Equipo::escribrirEnDisco(){}
void  Equipo::setNro_equipo(int n){nro_equipo=n;}
void  Equipo::setNombre_equipo(char *nombre){strcpy(nombre_equipo,nombre);}
void  Equipo::setGoles_afavor(int goles){goles_afavor=goles;}
void  Equipo::setGoles_encontra(int goles){goles_encontra=goles;}
void  Equipo::setPartidos_ganados(int partidos){partidos_ganados=partidos;}
void  Equipo::setPartidos_perdidos(int partidos){partidos_perdidos=partidos;}
int   Equipo::getNro_equipo(){return nro_equipo;}
char *Equipo::getNombre_equipo(){return nombre_equipo;}
int   Equipo::getGoles_afavor(){return goles_afavor;}
int   Equipo::getGoles_encontra(){return goles_encontra;}
int   Equipo::getPartidos_ganados(){return partidos_ganados;}
int   Equipo::getPartidos_perdidos(){return partidos_perdidos;}

bool Equipo::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Equipo),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

void ingresar_equipo(int cant_equipos){
    cls();
    title("TORNEO DE FUTBOL", APP_TITLEFORECOLOR, APP_TITLEBACKCOLOR);
    gotoxy(1,3);
    char nombre[30];
    int cant_jugadores;
    cout<<"    CARGAR EQUIPO Y JUGADORES"<<endl<<endl;
    Equipo eq;
    cout<<"    Ingrese nombre: ";
    cin>>nombre;
    eq.setNombre_equipo(nombre);
    anykey();
    if(eq.guardarEnDisco()){
        cout<<"    SE HA GUARDADO CORRECTAMENTE"<<endl;
    }
    else{
        cout<<"    NO SE HA PODIDO GUARDAR"<<endl;
    }

    cout<<"    Ingrese cantidad de jugadores: ";
    cin>>cant_jugadores;

    //cargar_jugadores();
    int i;
    for(i=0;i<cant_jugadores;i++){
        Jugador ju;
        char nombrej[25];
        cout<< "    Ingresar nombre jugador "<<i+1<<": ";
        cin>>nombrej;
        ju.setNombre(nombrej);
        if(ju.guardarEnDisco()){
            cout<<"    SE HA GUARDADO CORRECTAMENTE"<<endl;
        }
    }

}

