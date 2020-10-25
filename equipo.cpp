#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <cstring>
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

void ingresar_equipos(int cant_equipos){

    bool grabo;
    grabo=cargar_equipo(cant_equipos);


}

bool cargar_equipo(int cant_equipos){
    char nombre[30];
    int cant_jugadores;
    cout<<"    CARGAR EQUIPO Y JUGADORES"<<endl<<endl;
    Equipo eq;
    cout<<"    Ingrese nombre: ";
    cin>>nombre;
    eq.setNombre_equipo(nombre);
    if(eq.guardarEnDisco()){
        cout<<"    SE HA GUARDADO CORRECTAMENTE"<<endl;
    }
    else{
        cout<<"    NO SE HA PODIDO GUARDAR"<<endl;
    }

    cout<<"    Ingrese cantidad de jugadores: ";
    cin>>cant_jugadores;
    return (cargar_jugadores(cant_jugadores));
}


bool cargar_jugadores(int cant_jugadores){
    int i;
    char posicion[25], apellido[25], nombre[25];
    for(i=0;i<cant_jugadores;i++){
        Jugador ju;
        cin.ignore();
        cout<< "    Ingresar nombre jugador "<<i+1<<": ";
        cin.getline(nombre,25);
        cout<< "    Ingresar apellido del jugador "<<i+1<<": "<<endl;
        cin.getline(apellido,25);
        cout<< "    Ingresar posicion del jugador "<<i+1<<": "<<endl;
        cin.getline(posicion,25);

        ju.setNombre(nombre);
        ju.setApellido(apellido);
        ju.setPosicion(posicion);
        if(!ju.guardarEnDisco()){/// si no grabo entonces corta el for. si graba continua la carga del proximo jugador
            return false;
        }
    }
    return true;
}


int contar_equiposCargados(){
    FILE*pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"rb");
    if (pArchivo == NULL){
        return 0;
    }
    int bytes, cant;
    fseek(pArchivo, 0, SEEK_END);
    bytes = ftell(pArchivo);
    fclose(pArchivo);
    cant = bytes / sizeof(Equipo);
    return cant;
}
