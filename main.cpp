#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
using namespace std;
#include "menu.h"
#include "rlutil.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"
#include "partido.h"
#include "equipo.h"


int main(){
    setlocale(LC_ALL, "spanish");

    FILE* p;
    p=fopen(FILE_TORNEOS, "rb");
    if(p==NULL){
        cout<<" ERROR DE ARCHIVO TORNEO";
        anykey();
    }
    Torneo reg;
    cout << left;
    cout << setw(11) << "Tipo Torneo" << setw(17) << "|Cod. Torneo" << setw(18) << "|Instancia" << setw(13) << "|Partidos Jugados" << setw(17) << "|Torneo Activo";
    cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;

    while(fread(&reg, sizeof (Torneo),1,p)){
        reg.mostrar();


    }

    fclose(p);

    anykey();

    FILE* par;
    par=fopen(FILE_PARTIDOS, "rb");
    if(p==NULL){
        cout<<" ERROR DE ARCHIVO PARTIDOS";
        anykey();
    }
    Partido pa;
    cout << left;
    cout << setw(11) << "Cod. Torneo" << setw(17) << "|Equipo Local" << setw(18) << "|Equipo Visitante" << setw(13) << "|Goles Local" << setw(17) << "|Goles Visitante"<< setw(13) << "|Equipo Ganador"<< setw(13) << "|Instancia"<< setw(13) << "|Nro Partido"<<endl;
    cout << endl << "---------------------------------------------------------------------------------------------------------------------------" << endl;

    while(fread(&pa, sizeof (Partido),1,par)){
    cout << left;
    cout << setw(18);
    cout << pa.getCodigo_toneo();
    cout << setw(15) ;
    cout << pa.getEquipo_local();
    cout << setw(15) ;
    cout << pa.getEquipo_visitante();
    cout << setw(15) ;
    cout << pa.getGoles_local();
    cout << setw(7) ;
    cout << pa.getGoles_visitante();
    cout << setw(7) ;
    cout << pa.getEquipo_ganador();
    cout << setw(7) ;
    cout << pa.getInstancia_torneo();
    cout << setw(7) ;
    cout << pa.getNro_partido();
    cout << setw(13) ;
    cout << endl;


    }

    fclose(par);

    anykey();

    menu_principal();

    return 0;
}
