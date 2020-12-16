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

bool Jugador::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Jugador),1,pArchivo);
    fclose(pArchivo);
    return guardo;
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
    cout << "    INGRESE N�MERO DEL EQUIPO A BUSCAR: ";
    cin >> equipo;

    existe=nombre_equipo(nomb_equipo,equipo);/// carga el nombre para poder poner el nombre del equipo Y ADEMAS VERIFICA QUE EXISTA EL EQUIPO
    if(existe){
        cout << endl << "    LISTA DE JUGADORES DEL EQUIPO: ";
        setColor(RED);
        cout << nomb_equipo<<endl<<endl;
        setColor(WHITE);
        cout << left;
        cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posici�n " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
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

int cantidad_jugadores(){
    FILE *p = fopen(FILE_JUGADORES, "rb");
    if (p == NULL){
        return 1;
    }
    int bytes, cant;
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    fclose(p);
    cant = bytes / sizeof(Jugador);
    return cant;
}

void mostrar_goleadores(Jugador *v){


    int i;
    cout<<endl;
    cout<<"-----------TABLA DE GOLEADORES-----------";
    cout<<endl;

    cout<<left;
    cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) <<"|Goles ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;
       for(i=0;i<10;i++){

                cout << left;
                cout << setw(16);
                cout << v[i].getNombre();
                cout << setw(15) ;
                cout << v[i].getApellido();
                cout << setw(10) ;
                cout << v[i].getCant_goles();
                cout<<endl;
                }


                return;

}


void tabla_goleadores(){


    int cant,i,j,posmax;
    Jugador *v,aux;

    cant=cantidad_jugadores();

    v=new Jugador[cant];

        FILE *p;
        p = fopen(FILE_JUGADORES, "rb");
        fread(v, sizeof(Jugador), cant, p);
        fclose(p);

        for(i=0; i<cant-1; i++){
        posmax = i;
        for(j=i+1; j<cant; j++){
            if (v[j].getCant_goles() > v[posmax].getCant_goles()){
                posmax = j;
            }
        }
        aux = v[i];
        v[i] = v[posmax];
        v[posmax] = aux;
    }
    mostrar_goleadores(v);

delete []v;

return;

}





