#include <iostream>
#include <locale.h>

#include <ctime>
#include <iomanip>


using namespace std;
#include "menu.h"
#include "rlutil.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"


int main(){
    setlocale(LC_ALL, "spanish");


    /*
    FILE* pArchivo;
    pArchivo=fopen(FILE_TORNEOS,"rb");
    if(pArchivo==NULL){
        cout<<"error archivo"<<endl;
        exit(1);
    }
    Torneo tor;
    fread(&tor, sizeof(Torneo), 1, pArchivo);
    fclose(pArchivo);

    cout<<"torneo"<<endl;
    cout<< "tipo de torneo: "<<tor.getTipo_torneo()<<endl;
    cout<< "codigo de torneo: "<<tor.getCodigo_torneo()<<endl;
    cout<< "instancia de torneo: "<<tor.getInstancia_torneo()<<endl;
    cout<< "Partido jugados: "<<tor.getPartidos_jugados()<<endl;
    cout<< "torneo activo? "<<tor.getTorneo_activo()<<endl;
    */
    menu_principal();

    return 0;
}
