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
#include "equipo.h"


int main(){
    setlocale(LC_ALL, "spanish");

    menu_principal();

    return 0;
}
