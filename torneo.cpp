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
void Torneo::setCodigo_torneo(int codigo){codigo_torneo=codigo;}
void Torneo::setInstancia_torneo(int inst){instancia_torneo=inst;}
void Torneo::setPartidos_jugados(int par){partidos_jugados=par;}
void Torneo::setTorneo_activo(bool activo){torneo_activo=activo;}
int  Torneo::getTipo_torneo(){return tipo_torneo;}
int  Torneo::getCodigo_torneo(){return codigo_torneo;}
int  Torneo::getInstancia_torneo(){return instancia_torneo;}
int  Torneo::getPartidos_jugados(){return partidos_jugados;}
bool Torneo::getTorneo_activo(){return torneo_activo;}

Torneo::Torneo(){
    partidos_jugados=0;
    torneo_activo=true;
}

void Torneo::aumentar_partidos_jugados(){
    partidos_jugados++;
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

void Torneo::cambiar_instacia_torneo(){
    instancia_torneo=instancia_torneo/2;
}

void Torneo::autonumerar_torneo(){
    cls();
    cout<<"ENTROOOOO"<<endl<<endl;
    anykey();
    int cant;
    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS, "rb");
    if(pArchivo==NULL){
        codigo_torneo=1;
        return;
    }
    cant=contar_torneosCargados();
    codigo_torneo=cant+1;
    cls();
    cout<<"codigo torneo "<<codigo_torneo<<endl<<endl;
    anykey();
    fclose(pArchivo);
}

int contar_torneosCargados(){
    FILE*pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
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

int seleccionar_torneo(){
    int torneo, cant_equipos;
    char seguro;
    cout<<"    Seleccionar torneo:"<<endl<<endl;
    cout<<"    1 - 32vos = 64 EQUIPOS "<<endl;
    cout<<"    2 - 16vos = 32 EQUIPOS"<<endl;
    cout<<"    3 - 8vos  = 16 EQUIPOS"<<endl;
    cout<<"    4 - 4tos  = 8 EQUIPOS"<<endl<<endl;

    cout<<"    Opci�n-> ";
    cin>> torneo;

    if(torneo==1) cant_equipos=64;
    if(torneo==2) cant_equipos=32;
    if(torneo==3) cant_equipos=16;
    if(torneo==4) cant_equipos=8;

    cout<< endl<< "    HA SELECCIONADO EL TORNEO PARA "<< cant_equipos << " EQUIPOS"<<endl;
    cout<< endl<< "    �EST� SEGURO DE LA ELECCI�N? (S/N)"; ///FALTARIA AGREGAR VALIDACION POR INGRESOS INCORRECTOS
    cin>>seguro;
    if(seguro=='N' || seguro=='n') {
        cout<<endl << "    VUELVA A SELECCIONAR TORNEO"<<endl;
        return 0;
    }
    cout<<endl << "    TORNEO SELECCIONADO CORRECTAMENTE"<<endl;
    anykey();

    Torneo tor;
    tor.autonumerar_torneo();
    tor.setInstancia_torneo(cant_equipos/2);
    tor.setTipo_torneo(cant_equipos);
    tor.guardarEnDisco();

    return cant_equipos;
}

void cargar_resultado_partido(){
    int numeroEquipo1,numeroEquipo2, numeroCamiseta, numeroCamiseta_asistencia, golesEquipo1,golesEquipo2;
    int resultado, res_penales1=0, res_penales2=0;
    bool grabo;
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
    if(tor.getInstancia_torneo()==32){
        cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"VOS" <<endl<<endl;
    }
    if(tor.getInstancia_torneo()==16){
        cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"VOS" <<endl<<endl;
    }
    if(tor.getInstancia_torneo()==8){
        cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"VOS" <<endl<<endl;
    }
    if(tor.getInstancia_torneo()==4){
        cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE "<< tor.getInstancia_torneo()<<"TOS" <<endl<<endl;
    }
    if(tor.getInstancia_torneo()==2){
        cout<<"    CARGAR DATOS DEL PARTIDO "<<tor.getPartidos_jugados()+1<< " DE LA LLAVE DE SEMIFINAL" <<endl<<endl;
    }
    if(tor.getInstancia_torneo()==1){
        cout<<"    CARGAR DATOS DEL PARTIDO FINAL" <<endl<<endl;
    }

    cout<<"    N�mero del primer equipo: ";
    cin>>numeroEquipo1;
    nombre_equipo(nomb_equipo1,numeroEquipo1);
    cout<<"    EQUIPO "<<nomb_equipo1;
    cout<<endl;
    cout<<"    Goles: ";
    cin>>golesEquipo1;
    cout<<endl;

    cout<<"    N�mero del segundo equipo: ";
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

    grabo=registrarResultado(golesEquipo1,golesEquipo2,res_penales1,numeroEquipo1);
    if(!grabo){
        msj("NO SE HA PODIDO GUARDAR EL RESULTADO",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    grabo=registrarResultado(golesEquipo2,golesEquipo1,res_penales2,numeroEquipo2);
    if(!grabo){
        msj("NO SE HA PODIDO GUARDAR EL RESULTADO",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
//////////////////////
    int i;
    char asis;

    if(golesEquipo1>0){
        cout<<"    ASIGNE GOLES DEL EQUIPO ";
        setColor(RED);
        cout<< nomb_equipo1<<endl<<endl;
        setColor(WHITE);

        for(i=0;i<golesEquipo1;i++){
            cout << "    Del gol "<<i+1<<"."<<endl<<endl;
            cout<<"    Ingrese nro de camiseta del jugador que marc�: ";
            cin>>numeroCamiseta;
            cout<<"    �HUBO ASISTENCIA?(S/N):";
            cin>>asis;
            cout<<endl;
            if(asis=='s' || asis=='S'){
                cout<<"    Ingrese nro de camiseta del jugador que asisti�: ";
                cin>>numeroCamiseta_asistencia;
                cout<<endl;
            }
            else{
                numeroCamiseta_asistencia=0;
            }

            grabo=registrarGol(numeroEquipo1,numeroCamiseta);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR EL GOL",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
            grabo=registrarAsistencia(numeroEquipo1,numeroCamiseta_asistencia);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA ASISTENCIA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
        }
    }
    if(golesEquipo2>0){
        cout<<"    ASIGNE GOLES DEL EQUIPO ";
        setColor(RED);
        cout<< nomb_equipo2<<endl<<endl;
        setColor(WHITE);
        for(i=0;i<golesEquipo2;i++){
            cout << "    Del gol "<<i+1<<"."<<endl<<endl;
            cout<<"    Ingrese nro de camiseta del jugador que marc�: ";
            cin>>numeroCamiseta;
            cout<<"    �HUBO ASISTENCIA?(S/N):";
            cin>>asis;
            cout<<endl;
            if(asis=='s' || asis=='S'){
                cout<<"    Ingrese nro de camiseta del jugador que asisti�: ";
                cin>>numeroCamiseta_asistencia;
                cout<<endl;
            }
            else{
                numeroCamiseta_asistencia=0;
            }

            grabo=registrarGol(numeroEquipo2,numeroCamiseta);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR EL GOL",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
            grabo=registrarAsistencia(numeroEquipo2,numeroCamiseta_asistencia);
            if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA ASISTENCIA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
            }
        }
    }
//////////////////
    int numeroCamiseta_amarilla,numeroCamiseta_roja;
    char amarillas,rojas;

    cout<<"    �EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo1;
    setColor(WHITE);
    cout<<" HUBO TARJETAS AMARILLAS?(S/N): ";
    cin>>amarillas;

    while(amarillas=='s' || amarillas=='S'){
        cout<< endl<<"    Ingrese n�mero de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_amarilla;

        grabo=registrarAmarilla(numeroEquipo1, numeroCamiseta_amarilla);
        if(!grabo){
            msj("NO SE HA PODIDO GUARDAR LA TARJETA AMARILLA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
            return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA AMARILLA?(S/N): ";
        cin>>amarillas;
    }

    cout<<endl<<"    �EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo2;
    setColor(WHITE);
    cout<<" HUBO TARJETAS AMARILLAS?(S/N): ";
    cin>>amarillas;
    while(amarillas=='s' || amarillas=='S'){
        cout<< endl<<"    Ingrese n�mero de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_amarilla;

        grabo=registrarAmarilla(numeroEquipo2, numeroCamiseta_amarilla);
        if(!grabo){
            msj("NO SE HA PODIDO GUARDAR LA TARJETA AMARILLA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
            return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA AMARILLA?(S/N): ";
        cin>>amarillas;
    }

////////////////////

    cout<<endl<<"    �EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo1;
    setColor(WHITE);
    cout<<" HUBO TARJETAS ROJAS?(S/N): ";
    cin>>rojas;
    while(rojas=='s' || rojas=='S'){
        cout<< endl<<"    Ingrese n�mero de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_roja;

        grabo=registrarRoja(numeroEquipo1, numeroCamiseta_roja);
        if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA TARJETA ROJA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA ROJA?(S/N): ";
        cin>>rojas;
    }

    cout<<endl<<"    �EN EL EQUIPO ";
    setColor(RED);
    cout<<nomb_equipo2;
    setColor(WHITE);
    cout<<" HUBO TARJETAS ROJAS?(S/N): ";
    cin>>rojas;
    while(rojas=='s' || rojas=='S'){
        cout<< endl<<"    Ingrese n�mero de camiseta del jugador amonestado: ";
        cin>>numeroCamiseta_roja;

        registrarRoja(numeroEquipo2, numeroCamiseta_roja);
        if(!grabo){
                msj("NO SE HA PODIDO GUARDAR LA TARJETA ROJA",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
                return;
        }
        cout<<endl<<"    REGISTRAR OTRA TARJETA ROJA?(S/N): ";
        cin>>rojas;
    }

    if(grabo){
        contar_partido_cargado();
        cout<<"partidos jugados: "<<tor.getPartidos_jugados()<<endl;
        cout<<"INSTANCIA: "<<tor.getInstancia_torneo()<<endl;
        anykey();
        msj("PARTIDO GUARDADO CORRECTAMENTE",APP_TITLEFORECOLOR, APP_OKCOLOR);
        if((tor.getPartidos_jugados()+1)==tor.getInstancia_torneo()){
            cambiar_instancia_torneo();
            /// FUNCION QUE PONGA LOS EQUIPOS EN LA SIGUIENTE FASE
            /// HAY QUE HACER CLASS PARTIDO
        }
    }
}

bool registrarResultado(int goles_a_favor,int goles_en_contra, int diferencia_penales, int equipo){
    Equipo eq;
    int diferencia;
    FILE*p;
    p=fopen(FILE_EQUIPOS,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
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
            return true;
        }
    }
    fclose(p);
    return false;
}

bool registrarGol(int nro_equipo, int numeroCamiseta){

    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta==ju.getNro_camiseta()){

            ju.aumentar_gol();

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

bool registrarAsistencia(int nro_equipo, int numeroCamiseta_asistencia){
    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta_asistencia==ju.getNro_camiseta()){


            if(numeroCamiseta_asistencia>0){
                ju.aumentar_asistencia();
            }

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return true;
}

bool registrarAmarilla(int nro_equipo, int numeroCamiseta_amarilla){
    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta_amarilla==ju.getNro_camiseta()){


            if(numeroCamiseta_amarilla>0){
                ju.aumentar_amarilla();
            }

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return true;
}

bool registrarRoja(int nro_equipo, int numeroCamiseta_roja){
    Jugador ju;
    FILE*p;
    p=fopen(FILE_JUGADORES,"rb+");
    if (p == NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return false;
    }

    while(fread(&ju,sizeof(Jugador),1,p)==1){
        if(nro_equipo==ju.getNro_equipo() && numeroCamiseta_roja==ju.getNro_camiseta()){


            if(numeroCamiseta_roja>0){
                ju.aumentar_roja();
            }

            fseek(p,ftell(p)-sizeof (Jugador),0);
            fwrite(&ju, sizeof(Jugador), 1 , p);
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}

void cambiar_instancia_torneo(){
    Torneo tor;
    FILE *p;
    p=fopen(FILE_TORNEOS,"rb+");
    if(p==NULL){
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    fread(&tor,sizeof(Torneo), 1,p);

    tor.cambiar_instacia_torneo();
    tor.setPartidos_jugados(0);

    fseek(p, ftell(p)-sizeof(Torneo),0);
    fwrite(&tor , sizeof(Torneo),1 ,p);
    fclose(p);
}

void contar_partido_cargado(){
    Torneo tor;
    FILE *p;
    p=fopen(FILE_TORNEOS,"rb+");
    if(p==NULL){
        msj("ERROR ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
        return;
    }
    fread(&tor,sizeof(Torneo), 1,p);
    tor.aumentar_partidos_jugados();

    fseek(p, ftell(p)-sizeof(Torneo),0);
    fwrite(&tor , sizeof(Torneo),1 ,p);
    fclose(p);
}


















































