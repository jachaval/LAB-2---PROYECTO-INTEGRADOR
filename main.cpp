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

    menu_principal();

    return 0;
}
