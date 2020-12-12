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
#include "partido.h"


int main(){
    setlocale(LC_ALL, "spanish");
    /*
    FILE* pArchivo;
    pArchivo=fopen(FILE_PARTIDOS,"rb");
    if(pArchivo==NULL){
        cout<<"error archivo"<<endl;
        exit(1);
    }
    Partido tor;
    fread(&tor, sizeof(Partido), 1, pArchivo);
    fclose(pArchivo);

    cout<<"Partido"<<endl;
    cout<< "codigo de Partido: "<<tor.getCodigo_toneo()<<endl;
    cout<< "Equipo local: "<<tor.getEquipo_local()<<endl;
    cout<< "Equipo visitante: "<<tor.getEquipo_visitante()<<endl;
    cout<< "Goles local: "<<tor.getGoles_local()<<endl;
    cout<< "Goles visitante "<<tor.getGoles_visitante()<<endl;
    cout<< "Equipo ganador "<<tor.getEquipo_ganador()<<endl;
    cout<< "Instancia del torneo "<<tor.getInstancia_torneo()<<endl;
    cout<< "Nro de partido "<<tor.getNro_partido()<<endl;
    */

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

    /*
    FILE * pArchivo;
    pArchivo=fopen(FILE_JUGADORES,"rb");
    if(pArchivo==NULL){
        cout<<"error archivo"<<endl;
        exit(1);
    }
    Jugador ju;

        cout << setw(15) << "Nombre " << setw(15) << "|Apellido " << setw(15) << "|Posición " << setw(15) << "|Nro. Camiseta "<< setw(6) << "|Goles " << setw(12) << "|Asistencias " << setw(9) << "|T. Rojas " << setw(13) << "|T. Amarillas ";
        cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;
        while(fread(&ju, sizeof (Jugador),1, pArchivo)==1){

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
    */


    menu_principal();

    return 0;
}
