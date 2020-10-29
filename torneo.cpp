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

void Torneo::setTipo_torneo(int tipo){tipo_torneo=tipo;}
void Torneo::setInstancia_torneo(int inst){instancia_torneo=inst;}
void Torneo::setPartidos_jugados(int par){partidos_jugados=par;}
void Torneo::setTorneo_activo(bool activo){torneo_activo=activo;}
int  Torneo::getTipo_torneo(){return tipo_torneo;}
int  Torneo::getInstancia_torneo(){return instancia_torneo;}
int  Torneo::getPartidos_jugados(){return partidos_jugados;}
bool Torneo::getTorneo_activo(){return torneo_activo;}

Torneo::Torneo(){
    partidos_jugados=0;
    torneo_activo=true;
}

bool Torneo::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Torneo),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

int informar_tipoTorneo(){

    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if(pArchivo==NULL){
        return 0;
    }
    int cant;
    Torneo tor;
    fread(&tor, sizeof(Torneo), 1, pArchivo);
    fclose(pArchivo);
    cant=tor.getTipo_torneo();
    return cant;
}

void cargar_resultado_partido(){
    int numeroEquipo1,numeroEquipo2, numeroCamiseta, golesEquipo1,golesEquipo2, golesJugador, asistencias, CantRojas, CantAmari;
    int resultado, res_penales1=0, res_penales2=0;
    int opcion;

    Torneo tor;
    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    fread(&tor, sizeof(Torneo),1 , pArchivo);
    pclose(pArchivo);
    char nomb_equipo1[30];
    char nomb_equipo2[30];
    cout<<"    CARGAR PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"TOS" <<endl<<endl;
    cout<<"    Número del primer equipo: ";
    cin>>numeroEquipo1;
    nombre_equipo(nomb_equipo1,numeroEquipo1);
    cout<<"    EQUIPO "<<nomb_equipo1;
    cout<<endl;
    cout<<"    Goles: ";
    cin>>golesEquipo1;
    cout<<endl;

    cout<<"    Número del segundo equipo: ";
    cin>>numeroEquipo2;
    nombre_equipo(nomb_equipo2,numeroEquipo2);
    cout<<"    EQUIPO "<<nomb_equipo2;
    cout<<endl;
    cout<<"    Goles: ";
    cin>>golesEquipo2;
    cout<<endl;

    resultado=golesEquipo1-golesEquipo2;

    res_penales1=0;
    res_penales2=0;

    if(resultado==0){
        int penales1,penales2;

        cout<< "    INGRESE LOS RESULTADOS DE LA RONDA DE PENALTIES RESPETANDO EL ORDEN ANTERIOR"<<endl<<endl;
        cout<< "    Penales a favor de "<<nomb_equipo1<<": ";
        cin>>penales1;
        cout<<endl;

        cout<< "    Penales a favor de "<<nomb_equipo2<<": ";
        cin>>penales2;
        cout<<endl;


        res_penales1=penales1-penales2;
        res_penales2=penales2-penales1;
    }


    registrarResultado(golesEquipo1,golesEquipo2,res_penales1,numeroEquipo1);
    registrarResultado(golesEquipo2,golesEquipo1,res_penales2,numeroEquipo2);


    cls();
    do{
        cout<<"    INGRESE LOS GOLEADORES. PRIMERO DIGITE EL NÚMERO DE EQUIPO DEL GOLEADOR, LUEGO EL DE LA CAMISETA Y LUEGO LA CANTIDAD DE GOLES QUE EL JUGADOR HIZO.";
        cout<<"    En caso de no haber goles ingrese -1"<<endl;
        cout<<"    Número de equipo: " <<endl;
        cin>>numeroEquipo1;
        cout<<endl;

        if(numeroEquipo1>0){
            cout<<"Número de camiseta: " <<endl;
            cin>>numeroCamiseta;
            cout<<endl;
            cout<<"Cantidad de goles del jugador: "<<endl;
            cin>>golesJugador;
            cout<<endl;


            registrarGoles(numeroEquipo1, numeroCamiseta, golesJugador);
            //hacer mensaje con okcolor//

            cout<<" ¿Hay más jugadores para ingresar? Ingrese 1 en caso de que si o 0 en caso de que no"<<endl;

            cin>>opcion;
            cout<<endl;

            while (opcion!=1 || opcion!=0){
                cout<<"OPCIÓN INCORRECTA"<<endl;
                cin>>opcion;
                cout<<endl;
            }
        }

    }while(opcion==1);

    cls();


    do{
        cout<<"    INGRESE LAS ASISTENTENCIAS. PRIMERO DIGITE EL NÚMERO DE EQUIPO DEL JUGADOR, LUEGO EL DE LA CAMISETA Y LUEGO LA CANTIDAD DE ASISTENCIAS QUE EL JUGADOR HIZO";
        cout<<"    En caso de no haber asistencias ingrese -1 en ambos campos"<<endl;
        cout<<"    Número de equipo: "<<endl;
        cin>>numeroEquipo1;
        cout<<endl;

        if(numeroCamiseta>0){

            cout<<"Número de camiseta: " <<endl;
            cin>>numeroCamiseta;
            cout<<endl;
            cout<<"Cantidad de asistencias de el jugador: "<<endl;
            cin>>asistencias;
            cout<<endl;

            registrarAsistencias(numeroEquipo1,numeroCamiseta, asistencias);
            //hacer mensaje con okcolor//

            cout<<" ¿Hay más jugadores para ingresar? Ingrese 1 en caso de que si o 0 en caso de que no"<<endl;

            cin>>opcion;
            cout<<endl;

            while (opcion=1 || opcion!=0){
            cout<<"OPCIÓN INCORRECTA"<<endl;
            cin>>opcion;
            cout<<endl;
            }
        }

    }while(opcion==1);

    cls();

    do{
        cout<<"    INGRESE LAS TARJETAS AMARILLAS. PRIMERO DIGITE EL NÚMERO DE EQUIPO, LUEGO EL DE LA CAMISETA Y LUEGO LA CANTIDAD DE TARJETAS AMARILLAS"<<endl<<endl;
        cout<<"    En caso de no haber amarillas ingrese -1"<<endl;
        cout<<" Número de equipo: "<<endl;
        cin>>numeroEquipo1;
        cout<<endl;
        if(numeroEquipo1>0){

        cout<<"Número de camiseta: " <<endl;
        cin>>numeroCamiseta;
        cout<<endl;
        cout<<"Cantidad de tarjetas amarillas: "<<endl;
        cin>>CantAmari;
        cout<<endl;

        registrarAmarillas(numeroEquipo1,numeroCamiseta, CantAmari);
        //hacer mensaje con okcolor//

        cout<<" ¿Hay más jugadores para ingresar? Ingrese 1 en caso de que si o 0 en caso de que no"<<endl;

        cin>>opcion;
        cout<<endl;

        while (opcion=1 || opcion!=0){
            cout<<"OPCIÓN INCORRECTA"<<endl;
            cin>>opcion;
            cout<<endl;}
        }

        }while(opcion==1);

        cls();


        do{
        cout<<"    AHORA INGRESE UNO POR UNO LOS NÚMEROS DE EQUIPO Y CAMISETA DE LOS JUGADORES CON TARJETA ROJA. ";
        cout<<"   En caso de no haber tarjetas rojas ingrese -1";
        cout<<" Número de equipo: "<<endl;
        cin>>numeroEquipo1;
        cout<<endl;
        if(numeroEquipo1>0){
            cout<<"Número de camiseta: " <<endl;
            cin>>numeroCamiseta;
            cout<<endl;
            CantRojas=1;

            registrarRojas(numeroEquipo1,numeroCamiseta, CantRojas);
            //hacer mensaje con okcolor//

            cout<<" ¿Hay más jugadores para ingresar? Ingrese 1 en caso de que si o 0 en caso de que no"<<endl;

            cin>>opcion;
            cout<<endl;

            while (opcion=1 || opcion!=0){
                cout<<"OPCIÓN INCORRECTA"<<endl;
                cin>>opcion;
                cout<<endl;
            }
        }

    }while(opcion==1);

    cls();
}


void registrarResultado(int goles_a_favor,int goles_en_contra, int diferencia_penales, int equipo){
    Equipo eq;
    int diferencia;
    FILE*p;
    p=fopen(FILE_EQUIPOS,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    diferencia=goles_a_favor-goles_en_contra;


    while(fread(&eq,sizeof(Equipo),1,p)==1){
        if(equipo==eq.getNro_equipo()){
            eq.aumentar_gol_afavor(goles_a_favor);
            eq.aumentar_gol_encontra(goles_en_contra);
            if(diferencia>0)eq.aumentar_partidos_ganados();

            if(diferencia<0){
                eq.aumentar_partidos_perdidos();
                eq.setActivo();
            }
            if(diferencia==0){
                if(diferencia_penales>0){
                    eq.aumentar_partidos_ganados();
                }
                else{
                    eq.aumentar_partidos_perdidos();
                    eq.setActivo();
                }
            }
            fseek(p,ftell(p)-sizeof (Equipo),0);
            fwrite(&eq, sizeof(Equipo), 1 , p);
            fclose(p);
            msj("RESULTADO GUARDADO CORRECTAMENTE",APP_TITLEFORECOLOR,APP_OKCOLOR);
            return;
        }
    }
    fclose(p);
}

void registrarGoles(int equipo, int camiseta, int goles){

    Jugador ju;

    FILE*p;
    p=fopen(FILE_JUGADORES,"ab");
    if (p == NULL){
        return;
    }

    while(fwrite(&ju,sizeof(Jugador),1,p)){
        if(equipo==ju.getNro_equipo() && camiseta==ju.getNro_equipo())ju.setCant_goles(goles);
    }
}


void registrarAsistencias(int equipo, int camiseta, int asistencias){

    Jugador ju;

    FILE*p;
    p=fopen(FILE_JUGADORES,"ab");
    if (p == NULL){
        return;
    }

    while(fwrite(&ju,sizeof(Jugador),1,p)){
        if(equipo==ju.getNro_equipo() && camiseta==ju.getNro_camiseta())ju.setAsistencias(asistencias);
    }
}


void registrarAmarillas(int equipo, int camiseta, int amarillas){

    Jugador ju;

    FILE*p;
    p=fopen(FILE_JUGADORES,"ab");
    if (p == NULL){
        return;
    }

    while(fwrite(&ju,sizeof(Jugador),1,p)){
        if(equipo==ju.getNro_equipo() && camiseta==ju.getNro_camiseta())ju.setTarjeta_amarilla(amarillas);
    }
}


void registrarRojas(int equipo, int camiseta, int rojas){

    Jugador ju;

    FILE*p;
    p=fopen(FILE_JUGADORES,"ab");
    if (p == NULL){
        return;
    }

    while(fwrite(&ju,sizeof(Jugador),1,p)){
        if(equipo==ju.getNro_equipo() && camiseta==ju.getNro_camiseta())ju.setTarjeta_roja(rojas);

    }
}

int seleccionar_torneo(){
    int torneo, cant_equipos;
    char seguro;
    cout<<"    Seleccionar torneo:"<<endl<<endl;
    cout<<"    1 - 32vos = 64 EQUIPOS "<<endl;
    cout<<"    2 - 16vos = 32 EQUIPOS"<<endl;
    cout<<"    3 - 8vos  = 16 EQUIPOS"<<endl;
    cout<<"    4 - 4tos  = 8 EQUIPOS"<<endl<<endl;

    cout<<"    Opción-> ";
    cin>> torneo;

    if(torneo==1) cant_equipos=64;
    if(torneo==2) cant_equipos=32;
    if(torneo==3) cant_equipos=16;
    if(torneo==4) cant_equipos=8;

    cout<< endl<< "    HA SELECCIONADO EL TORNEO PARA "<< cant_equipos << " EQUIPOS"<<endl;
    cout<< endl<< "    ¿ESTÁ SEGURO DE LA ELECCIÓN? (S/N)"; ///FALTARIA AGREGAR VALIDACION POR INGRESOS INCORRECTOS
    cin>>seguro;
    if(seguro=='N' || seguro=='n') {
        cout<<endl << "    VUELVA A SELECCIONAR TORNEO"<<endl;
        return 0;
    }
    cout<<endl << "    TORNEO SELECCIONADO CORRECTAMENTE"<<endl;
    anykey();

    Torneo tor;
    tor.setInstancia_torneo(cant_equipos/2);
    tor.setTipo_torneo(cant_equipos);
    tor.guardarEnDisco();

    return cant_equipos;
}

