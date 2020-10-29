#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <cstring>
#include <iomanip>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "equipo.h"
#include "jugador.h"

void Equipo::cargar(){
    cout<< "    ";
}


Equipo::Equipo(){
    activo=true;
    partidos_ganados=0;
    partidos_perdidos=0;
    goles_afavor=0;
    goles_encontra=0;
}

void  Equipo::mostrar(){};
bool  Equipo::escribrirEnDisco(){};
void  Equipo::setActivo(){activo=false;}
void  Equipo::setNro_equipo(int n){nro_equipo=n+1;}
void  Equipo::setNombre_equipo(char *nombre){strcpy(nombre_equipo,nombre);}
void  Equipo::setGoles_afavor(int goles){goles_afavor+=goles;}
void  Equipo::setGoles_encontra(int goles){goles_encontra+=goles;}
void  Equipo::setPartidos_ganados(){partidos_ganados++;}
void  Equipo::setPartidos_perdidos(){partidos_perdidos++;}///modificar y agregar una funcion para agregar partidos a favor,gol,etc
int   Equipo::getNro_equipo(){return nro_equipo;}
char *Equipo::getNombre_equipo(){return nombre_equipo;}
int   Equipo::getGoles_afavor(){return goles_afavor;}
int   Equipo::getGoles_encontra(){return goles_encontra;}
int   Equipo::getPartidos_ganados(){return partidos_ganados;}
int   Equipo::getPartidos_perdidos(){return partidos_perdidos;}
bool  Equipo::getActivo(){return activo;}





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
    if(grabo){
        msj("EQUIPO GUARDADO CORRECTAMENTE", APP_TITLEFORECOLOR, APP_OKCOLOR);
    }
    else{
        msj("EL EQUIPO NO SE HA GUARDADO", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
    }
}

bool cargar_equipo(int cant_equipos){
    char nombre[30];
    int cant_jugadores,n;
    bool grabo;
    cout<<"    CARGAR EQUIPO Y JUGADORES"<<endl<<endl;
    Equipo eq;
    n=contar_equiposCargados();
    eq.setNro_equipo(n);
    cin.ignore();
    cout<<"    Ingrese nombre: ";
    cin.getline(nombre,25);

    eq.setNombre_equipo(nombre);
    if(!eq.guardarEnDisco()){
        cout<<"    NO SE HA PODIDO GUARDAR"<<endl;
        return false;
    }

    cout<<"    Ingrese cantidad de jugadores: ";
    cin>>cant_jugadores;
    cout<<endl;
<<<<<<< Updated upstream
    grabo=cargar_jugadores(cant_jugadores,(n+1));
=======


    grabo=cargar_jugadores(cant_jugadores,n);
>>>>>>> Stashed changes
    return (grabo);
}


bool cargar_jugadores(int cant_jugadores, int nroEquipo){
    int i,camiseta;
    char posicion[25], apellido[25], nombre[25];
    for(i=0;i<cant_jugadores;i++){
        Jugador ju;
        cin.ignore();
        cout<< "    Ingresar nombre jugador "<<i+1<<": ";
        cin.getline(nombre,25);
        cout<< "    Ingresar apellido jugador "<<i+1<<": ";
        cin.getline(apellido,25);
        cout<< "    Ingresar posicion jugador "<<i+1<<": ";
        cin.getline(posicion,25);
        cout<<"    Ingresar número de camiseta jugador "<<i+1<<": ";
        cin>>camiseta;
        cout<<endl;

        ju.setNombre(nombre);

        ju.setApellido(apellido);

        ju.setPosicion(posicion);

        ju.setNro_equipo(nroEquipo);

        ju.setNro_camiseta(camiseta);


        ju.guardarEnDisco();
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

void listar_equipos(){
    FILE *pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"rb");
    Equipo eq;
    cout << left;
    cout << setw(11) << "Nro Equipo" << setw(20) << "|Nombre Equipo" << setw(4) << "|PG" << setw(4) << "|PP" << setw(4) << "|GF" << setw(4) << "|GC";
    cout << endl << "-----------------------------------------------" << endl;
    while(fread(&eq, sizeof (Equipo), 1, pArchivo)==1){
        cout << setw(12);
        cout << eq.getNro_equipo();
        cout << setw(20) ;
        cout << eq.getNombre_equipo();
        cout << setw(4) ;
        cout << eq.getPartidos_ganados();
        cout << setw(4) ;
        cout << eq.getPartidos_perdidos();
        cout << setw(4) ;
        cout << eq.getGoles_afavor();
        cout << setw(4) ;
        cout << eq.getGoles_encontra();
        cout << endl;
    }
    fclose(pArchivo);
}
