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

Jugador::Jugador(){
    tarjeta_roja=0;
    tarjeta_amarilla=0;
    asistencias=0;
    cant_goles=0;
    leido=false;
}

void Jugador::setNro_equipo(int nro){nro_equipo=nro;}
void Jugador::setNombre(char *nom){strcpy(nombre,nom);}
void Jugador::setApellido(char *ap){strcpy(apellido,ap);}
void Jugador::setPosicion(char *pos){strcpy(posicion,pos);}
void Jugador::setTarjeta_roja(int roja){tarjeta_roja=roja;}
void Jugador::setTarjeta_amarilla(int amarilla){tarjeta_amarilla=amarilla;}
void Jugador::setAsistencias(int asis){asistencias=asis;}
void Jugador::setCant_goles(int goles){cant_goles=goles;}
void Jugador::setNro_camiseta(int nro){nro_camiseta=nro;}
int  Jugador::getNro_equipo(){return nro_equipo;}
char *Jugador::getNombre(){return nombre;}
char *Jugador::getApellido(){return apellido;}
char *Jugador::getPosicion(){return posicion;}
int  Jugador::getTarjeta_roja(){return tarjeta_roja;}
int  Jugador::getTarjeta_amarilla(){return tarjeta_amarilla;}
int  Jugador::getAsistencias(){return asistencias;}
int  Jugador::getCant_goles(){return cant_goles;}
int  Jugador::getNro_camiseta(){return nro_camiseta;}
bool  Jugador::getLeido(){return leido;}


void Jugador::aumentar_gol(){
    cant_goles++;
}

void Jugador::aumentar_asistencia(){
    asistencias++;
}
void Jugador::aumentar_amarilla(){
    tarjeta_amarilla++;
}

void Jugador::aumentar_roja(){
    tarjeta_roja++;
}

void Jugador::cambiarLeido(){
      leido=true;
}

bool Jugador::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Jugador),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

void Jugador::mostrar_goles(){

    Jugador ju;
        cout << setw(12);
        cout << ju.getNombre();
        cout << setw(20) ;
        cout << ju.getApellido();
        cout << setw(4) ;
        cout << ju.getCant_goles();

        return;
        }

void listar_jugadores_x_equipo(){


    bool existe;
    int equipo;
    char nomb_equipo[30];
    FILE * pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO JUGADORES", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    Jugador ju;
    cout << "    INGRESE NÚMERO DEL EQUIPO A BUSCAR: ";
    cin >> equipo;

    existe=nombre_equipo(nomb_equipo,equipo);/// carga el nombre para poder poner el nombre del equipo Y ADEMAS VERIFICA QUE EXISTA EL EQUIPO
    if(existe){
        cout << endl << "    LISTA DE JUGADORES DEL EQUIPO: ";
        setColor(RED);
        cout << nomb_equipo<<endl<<endl;
        setColor(WHITE);
        cout << left;
        cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posición " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
        cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;
        while(fread(&ju, sizeof (Jugador),1, pArchivo)==1){
            if(equipo==ju.getNro_equipo()){
                cout << left;
                cout << setw(16);
                cout << ju.getNombre();
                cout << setw(15) ;
                cout << ju.getApellido();
                cout << setw(15) ;
                cout << ju.getPosicion();
                cout << setw(15) ;
                cout << ju.getNro_camiseta();
                cout << setw(7) ;
                cout << ju.getCant_goles();
                cout << setw(13) ;
                cout << ju.getAsistencias();
                cout << setw(10) ;
                cout << ju.getTarjeta_roja();
                cout << setw(14) ;
                cout << ju.getTarjeta_amarilla();
                cout << endl;


            }
        }
         anykey();

    }
    else{
        msj("EQUIPO NO ENCONTRADO",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
    }
}

void tabla_goleadores(){

    Jugador reg;
    int c=0,goles=0,posicion,i;


    FILE *pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"rb+");
    if(pArchivo==NULL)return;

      cout << endl << "    LISTA DE GOLEADORES: ";

      cout << setw(11) << "Jugador" << setw(20) << "|Nombre" << setw(4) << "|Apellido" << setw(4) << "|Cantidad de goles";
      cout << endl << "-----------------------------------------------" << endl;

    for(i=0;i<10;i++){

    while(fread(&reg, sizeof(Equipo),1 ,pArchivo)){
    c++;

    if(reg.getLeido()>=goles && reg.getLeido()==false){

        goles=reg.getLeido();
        posicion=c;
    }
    }

    fseek(pArchivo,posicion,SEEK_SET);
    reg.cambiarLeido();
    reg.mostrar_goles();
    fwrite(&reg,sizeof(Jugador),1,pArchivo);

    goles=0;
    }

     while(fread(&reg, sizeof(Jugador),1 ,pArchivo)){
     fwrite(&reg,sizeof(Jugador),1,pArchivo);
     }


    fclose(pArchivo);
    return;
}

