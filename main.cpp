#include <iostream>
#include <locale.h>
using namespace std;
#include "menu.h"
#include "rlutil.h"
using namespace rlutil;

int main(){
    setlocale(LC_ALL, "spanish");

    menu_principal();

    return 0;
}
