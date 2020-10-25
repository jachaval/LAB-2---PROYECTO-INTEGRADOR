#include <iostream>
#include <locale.h>
using namespace std;
#include "menu.h"
#include "rlutil.h"
using namespace rlutil;
#include "torneo.h"
#include "equipo.h"
int main(){
    setlocale(LC_ALL, "spanish");

    /*FILE * pArchivo;
    int cant;
    pArchivo=fopen(FILE_EQUIPOS,"rb");
    cant=contar_equiposCargados();

    Equipo reg;

    while(fread(&reg,sizeof (Equipo),1,pArchivo)){
        cout << "nro equipo:" << reg.getNro_equipo()<<endl;
        cout << "NOMBRE:" << reg.getNombre_equipo() <<endl<<endl;


    }
    fclose(pArchivo);*/

    menu_principal();

    return 0;
}
