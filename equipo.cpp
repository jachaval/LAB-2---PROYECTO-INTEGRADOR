#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <locale.h>
#include <iomanip>
#include <ctime>
using namespace std;
#include "rlutil.h"
#include "interfaz.h"
using namespace rlutil;
#include "torneo.h"
#include "jugador.h"
#include "partido.h"
#include "equipo.h"


Equipo::Equipo(){
    activo=true;
    partidos_ganados=0;
    partidos_perdidos=0;
    goles_afavor=0;
    goles_encontra=0;
}

void  Equipo::mostrar(){};
bool  Equipo::escribrirEnDisco(){};
void  Equipo::setActivo(){activo=false;}
void  Equipo::setNro_equipo(int n){nro_equipo=n+1;}
void  Equipo::setNombre_equipo(char *nombre){strcpy(nombre_equipo,nombre);}
void  Equipo::setGoles_afavor(int goles){goles_afavor=goles;}
void  Equipo::setGoles_encontra(int goles){goles_encontra=goles;}
void  Equipo::setPartidos_ganados(int partidos){partidos_ganados=partidos;}
void  Equipo::setPartidos_perdidos(int partidos){partidos_perdidos=partidos;}///modificar y agregar una funcion para agregar partidos a favor,gol,etc
int   Equipo::getNro_equipo(){return nro_equipo;}
char *Equipo::getNombre_equipo(){return nombre_equipo;}
int   Equipo::getGoles_afavor(){return goles_afavor;}
int   Equipo::getGoles_encontra(){return goles_encontra;}
int   Equipo::getPartidos_ganados(){return partidos_ganados;}
int   Equipo::getPartidos_perdidos(){return partidos_perdidos;}
bool  Equipo::getActivo(){return activo;}

void Equipo::aumentar_gol_afavor(int goles){
    goles_afavor+= goles;
}
void Equipo::aumentar_gol_encontra(int goles){
    goles_encontra+= goles;
}

void Equipo::aumentar_partidos_ganados(){
    partidos_ganados++;
}
void Equipo::aumentar_partidos_perdidos(){
    partidos_perdidos++;
}


bool Equipo::guardarEnDisco(){
    bool guardo;
    FILE *pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"ab");
    if(pArchivo==NULL)return false;
    guardo=fwrite(this,sizeof(Equipo),1,pArchivo);
    fclose(pArchivo);
    return guardo;
}

void ingresar_equipos(int cant_equipos){

    bool grabo;
    grabo=cargar_equipo(cant_equipos);
    if(grabo){
        msj("EQUIPO GUARDADO CORRECTAMENTE", APP_TITLEFORECOLOR, APP_OKCOLOR);
    }
    else{
        msj("EL EQUIPO NO SE HA GUARDADO", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
    }
}

bool checkrep(int n, int vecAleatorio[], int cant){
    for(int i=0; i<cant; i++){
        if(n == vecAleatorio[i]){
            return true;
        }
    }
    return false;
}

void poner_equipos_aleatorios(int * vecAleatorio, int cant_equipos){
    srand(time(NULL));
    const int cant=8;//cant es el rango de 1 a 8 en este caso
    int n;
    for(int i=0; i<cant; i++){
        do{
            n = 1 + rand() % cant;
        }while(checkrep(n, vecAleatorio, cant));
        vecAleatorio[i] = n;
    }
}

void sortear(){
    int cantidad_equipos;
    int cant_equiposCargados;
    FILE *p;
    p=fopen(FILE_TORNEOS,"rb");
    if(p==NULL){
        cout << "    SELECCIONAR TORNEO PRIMERO"<<endl<<endl;
        anykey();
        return;
    }
    fclose(p);

    cantidad_equipos=informar_tipoTorneo(); ///devuelve la cantidad de equipos total del torneo seleccionado.
    cant_equiposCargados=contar_equiposCargados(); //devuelve la cantidad de los equipos cargados, si ya estan todo no permite cargar mas

    if(cant_equiposCargados==cantidad_equipos){
        if(cantidad_equipos>0){
            cout<<"    SORTEAR EQUIPOS" <<endl<<endl;
            sortear_equipos(cantidad_equipos);
            /// mostrar equipos sorteados. HACER FUNCIONES CON RLUTIL HACER TIPO FIXTURE
            listar_equipos();
            anykey();
        }
        else{
            cout<<"    PRIMERO SELECCIONE EL TORNEO PARA PODER CARGAR LOS EQUIPOS"<<endl;
            anykey();
        }
    }
    else{
        cout<< "    EQUIPOS CARGADOS HASTA EL MOMENTO: "<< cant_equiposCargados<<" de " << cantidad_equipos<<endl<<endl;

        cout<< "    TERMINE DE CARGAR EQUIPOS PARA PODER SORTEAR " <<endl<<endl;
    }
}

void sortear_equipos(int cant){/// abre el archivo equipos y el vector de nro de equipo lo pone de manera aleatoria.
    int vecAleatorio[cant];
    poner_equipos_aleatorios(vecAleatorio,cant);

    Equipo eq;
    FILE* p;
    p=fopen(FILE_EQUIPOS,"rb+");
    if(p==NULL){
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }

    for(int i=0;i<cant;i++){
        fseek(p,0,SEEK_SET); ///seteo el cursor al inicio del archivo
        fseek(p, i * sizeof (Equipo),SEEK_SET); /// lo seteo a la posicion de registro a leer
        fread(&eq, sizeof(Equipo),1 ,p);

        cambiar_nroequipo_jugadores(vecAleatorio);

        eq.setNro_equipo(vecAleatorio[i]-1);
        fseek(p,ftell(p)-sizeof (Equipo),SEEK_SET); /// seteo a la posicion de registro leido para modificarlo
        fwrite(&eq, sizeof(Equipo), 1 , p);
    }
    fclose(p);
}

void cambiar_nroequipo_jugadores(int *vecAleatorio){
    Jugador jug;
    FILE* p;
    int numero, i=0;
    p=fopen(FILE_JUGADORES,"rb+");
    if(p==NULL){
        msj("ERROR DE ARCHIVO JUGADORES",APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    while(fread(&jug, sizeof(Jugador), 1 , p)){

        numero=jug.getNro_equipo();
        jug.setNro_equipo(vecAleatorio[numero-1]);
        //jug.setNro_equipo(vecAleatorio[jug.getNro_equipo()-1]);

        fseek(p,ftell(p)-sizeof (Jugador),SEEK_SET);
        fwrite(&jug, sizeof(Jugador), 1 , p);

        i++; //para saber en que registro leyo.
        fseek(p, i * sizeof (Jugador),SEEK_SET); //pone el cursor al final de registro que acaba de leer.. porque el fwrite te vuelve el puntero al inicio del archivo
    }
    fclose(p);
}

bool cargar_equipo(int cant_equipos){
    char nombre[30];
    int cant_jugadores,n;
    bool grabo;
    cout<<"    CARGAR EQUIPO Y JUGADORES"<<endl<<endl;
    Equipo eq;
    n=contar_equiposCargados();
    eq.setNro_equipo(n);
    cin.ignore();
    cout<<"    Ingrese el nombre de el equipo en mayúsculas: ";
    cin.getline(nombre,25);

    eq.setNombre_equipo(nombre);
    if(!eq.guardarEnDisco()){
        cout<<"    NO SE HA PODIDO GUARDAR"<<endl;
        return false;
    }

    cout<<endl<<"    Ingrese cantidad de jugadores: ";
    cin>>cant_jugadores;
    cout<<endl;

    while(cant_jugadores > 22 || cant_jugadores < 1){
        cout<< "     Cantidad invalida. Solo se permiten un maximo de 22 jugadores. Por favor, ingrese de nuevo la cantidad de jugadores: "<<endl;
        cin>>cant_jugadores;
        cout<<endl;
    }

    grabo=cargar_jugadores(cant_jugadores,(n+1));

    return (grabo);
}


bool cargar_jugadores(int cant_jugadores, int nroEquipo){
    int i,camiseta;
    bool guardo;
    char posicion[25], apellido[25], nombre[25];
    for(i=0;i<cant_jugadores;i++){
        Jugador ju;
        cin.ignore();
        cout<< "    Ingresar nombre jugador "<<i+1<<": ";
        cin.getline(nombre,25);
        cout<< "    Ingresar apellido jugador "<<i+1<<": ";
        cin.getline(apellido,25);
        cout<< "    Ingresar posicion jugador "<<i+1<<": ";
        cin.getline(posicion,25);
        cout<<"    Ingresar número de camiseta jugador "<<i+1<<": ";
        cin>>camiseta;
        cout<<endl;

        ju.setNombre(nombre);

        ju.setApellido(apellido);

        ju.setPosicion(posicion);

        ju.setNro_equipo(nroEquipo);

        ju.setNro_camiseta(camiseta);


        guardo=ju.guardarEnDisco();
        if(!guardo){/// si no grabo entonces corta el for. si graba continua la carga del proximo jugador
            return false;
        }
    }
    return true;
}


int contar_equiposCargados(){
    FILE*pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"rb");
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

void listar_equipos(){
    FILE *pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"rb");
    if(pArchivo==NULL){
        msj("ERROR ARCHIVO EQUIPOS", APP_TITLEFORECOLOR, APP_ERRORCOLOR);
        return;
    }
    Equipo eq;
    cout << left;
    cout << setw(11) << "Nro Equipo" << setw(20) << "|Nombre Equipo" << setw(4) << "|PG" << setw(4) << "|PP" << setw(4) << "|GF" << setw(4) << "|GC";
    cout << endl << "-----------------------------------------------" << endl;
    while(fread(&eq, sizeof (Equipo), 1, pArchivo)==1){
        cout << setw(12);
        cout << eq.getNro_equipo();
        cout << setw(20) ;
        cout << eq.getNombre_equipo();
        cout << setw(4) ;
        cout << eq.getPartidos_ganados();
        cout << setw(4) ;
        cout << eq.getPartidos_perdidos();
        cout << setw(4) ;
        cout << eq.getGoles_afavor();
        cout << setw(4) ;
        cout << eq.getGoles_encontra();
        cout << endl;


    }
     anykey();
    fclose(pArchivo);
}

bool nombre_equipo(char * nom_equipo,int equipo){
    Equipo eq;
    FILE * pArchivo;
    pArchivo=fopen(FILE_EQUIPOS,"rb");
    if(pArchivo==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }
    else{
        while(fread(&eq, sizeof(Equipo), 1 , pArchivo)){
            if(equipo==eq.getNro_equipo()){
                strcpy(nom_equipo,eq.getNombre_equipo());
                fclose(pArchivo);
                return true;
            }
        }
    }
    fclose(pArchivo);
    return false;
}

void mostrar_equipo(Equipo aux){

cout<<left;
    cout << setw(20) << "Nombre del equipo " << setw(20) << "|Partidos ganados " << setw(20) <<"|Partidos perdidos "<< setw(20) <<"|Goles a favor "<< setw(20) <<"|Goles en contra ";
    cout << endl << "--------------------------------------------------------------------------------------------------------" << endl;

    cout << left;
    cout << setw(20);
    cout << aux.getNombre_equipo();
    cout << setw(20) ;
    cout << aux.getPartidos_ganados();
    cout << setw(20) ;
    cout << aux.getPartidos_perdidos();
    cout << setw(20);
    cout << aux.getGoles_afavor();
    cout << setw(20);
    cout << aux.getGoles_encontra();

    cout<<endl;


}

void buscarEquipo(){

	Equipo reg;
	bool encontrado=false;
	char nombre_equipo[30];
	cout<<"Ingrese en mayusculas el nombre del equipo a buscar: ";
	cin.ignore();
	cin.getline(nombre_equipo,30);
	cout<<endl;


	FILE* f;
	f = fopen(FILE_EQUIPOS, "rb");
	if (f == NULL) {
		return;
	}
	while (fread(&reg, sizeof(Equipo), 1, f)) {
		if (strcmp(nombre_equipo,reg.getNombre_equipo())==0) {

            cls();
            mostrar_equipo(reg);
            encontrado=true;

			fclose(f);
			return;
		}
	}

	if(encontrado==false){
        cout<<"El equipo no existe"<<endl;

	}

	fclose(f);
	return;
}

void listar_equipos_en_competencia(){
    FILE* f;
	f = fopen(FILE_EQUIPOS, "rb");
	if (f == NULL) {
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}

	Equipo eq;
    cout << left;
    cout << setw(11) << "Nro Equipo" << setw(20) << "|Nombre Equipo" << setw(4) << "|PG" << setw(4) << "|PP" << setw(4) << "|GF" << setw(4) << "|GC";
    cout << endl << "-----------------------------------------------" << endl;
    while(fread(&eq, sizeof (Equipo), 1, f)==1){
        if(eq.getActivo()==true){
            cout << setw(12);
            cout << eq.getNro_equipo();
            cout << setw(20) ;
            cout << eq.getNombre_equipo();
            cout << setw(4) ;
            cout << eq.getPartidos_ganados();
            cout << setw(4) ;
            cout << eq.getPartidos_perdidos();
            cout << setw(4) ;
            cout << eq.getGoles_afavor();
            cout << setw(4) ;
            cout << eq.getGoles_encontra();
            cout << endl;
        }
    }
    fclose(f);
}

void ver_ganador(){
    FILE* f;
	f = fopen(FILE_EQUIPOS, "rb");
	if (f == NULL) {
        msj("ERROR DE ARCHIVO EQUIPOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
    int contador=0;
	Equipo eq;
    while(fread(&eq, sizeof (Equipo), 1, f)==1){
        if(eq.getActivo()==true){
            contador++;
        }
    }
    fclose(f);

    if(contador==1){

    setColor(RED);
        for (int i = 0; i < 40; i++) {
            gotoxy(i + 4, 3); printf("*");
            gotoxy(7, 4); printf("EQUIPO GANADOR ES: ");
            gotoxy(i + 4, 5); printf("*");
            gotoxy(4, 4); printf("*");
            gotoxy(43, 4); printf("*");
        }
        setColor(WHITE);
    gotoxy(26,4);
        cout << eq.getNombre_equipo();

    }
    else{
        cout<< "AUN NO TERMINO EL TORNEO"<<endl;
    }

}

void ver_proximos_encuentros(){ ///para febrero agregar fecha de encuentro
    FILE* f;
	f = fopen(FILE_TORNEOS, "rb");
	if (f == NULL) {
        msj("ERROR DE ARCHIVO TORNEOS",APP_TITLEFORECOLOR,APP_ERRORCOLOR);
		return;
	}
	Torneo tor;

	fread(&tor, sizeof (Torneo), 1 , f);

	switch(tor.getInstancia_torneo()){
        case 1:
            fase_final(tor.getPartidos_jugados());
            break;
        case 2:
            fase_semi(tor.getPartidos_jugados());
            break;
        case 4:
            fase_cuartos(tor.getPartidos_jugados());
            break;
        case 8:
            fase_octavos(tor.getPartidos_jugados());
            break;
        case 16:
            fase_16(tor.getPartidos_jugados());
            break;
        case 32:
            fase_32(tor.getPartidos_jugados());
            break;
	}

    fclose(f);
}

void fase_final(int partidos_jugados){    /// fase 1

    int cant,i , equipo1, equipo2;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==1){
            equipo1=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==2){
            equipo2=vec[i].getEquipo_ganador();
        }
    }

    cout<< "    FINAL"<<endl<<endl;

    cout<< equipo1 << " VS "<< equipo2;


    delete []vec;

}

void fase_semi(int partidos_jugados){
    int cant,i , equipo1, equipo2, equipo3, equipo4;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==1){
            equipo1=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==2){
            equipo2=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==3){
            equipo3=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==4){
            equipo4=vec[i].getEquipo_ganador();
        }
    }

    cout<< "    SEMIFINALES"<<endl<<endl;

    cout<< equipo1 << " VS "<< equipo2;
    cout<< equipo3 << " VS "<< equipo4;

    delete []vec;

}
void fase_cuartos(int partidos_jugados){
    int cant,i , equipo1, equipo2, equipo3, equipo4, equipo5, equipo6, equipo7, equipo8;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==1){
            equipo1=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==2){
            equipo2=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==3){
            equipo3=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==4){
            equipo4=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==5){
            equipo5=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==6){
            equipo6=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==7){
            equipo7=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==8){
            equipo8=vec[i].getEquipo_ganador();
        }
    }

    cout<< "    SEMIFINALES"<<endl<<endl;

    cout<< equipo1 << " VS "<< equipo2;
    cout<< equipo3 << " VS "<< equipo4;
    cout<< equipo5 << " VS "<< equipo6;
    cout<< equipo7 << " VS "<< equipo8;

    delete []vec;
}
void fase_octavos(int partidos_jugados){
int cant,i , equipo1, equipo2, equipo3, equipo4, equipo5, equipo6, equipo7, equipo8, equipo9, equipo10, equipo11, equipo12, equipo13, equipo14, equipo15, equipo16;
    Partido *vec;

    cant=cantidad_partidos();

    vec=new Partido[cant];

    FILE *p;
    p = fopen(FILE_PARTIDOS, "rb");
    fread(vec, sizeof(Partido), cant, p);
    fclose(p);

    for(i=0; i<cant-1; i++){
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==1){
            equipo1=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==2){
            equipo2=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==3){
            equipo3=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==4){
            equipo4=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==5){
            equipo5=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==6){
            equipo6=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==7){
            equipo7=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==8){
            equipo8=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==9){
            equipo9=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==10){
            equipo10=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==11){
            equipo11=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==12){
            equipo12=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==13){
            equipo13=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==14){
            equipo14=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==15){
            equipo15=vec[i].getEquipo_ganador();
        }
        if(vec[i].getInstancia_torneo()== 2 && vec[i].getNro_partido()==16){
            equipo16=vec[i].getEquipo_ganador();
        }
    }

    cout<< "    CUARTOS DE FINAL"<<endl<<endl;

    cout<< equipo1 << " VS "<< equipo2;
    cout<< equipo3 << " VS "<< equipo4;
    cout<< equipo5 << " VS "<< equipo6;
    cout<< equipo7 << " VS "<< equipo8;
    cout<< equipo9 << " VS "<< equipo10;
    cout<< equipo11 << " VS "<< equipo12;
    cout<< equipo13 << " VS "<< equipo14;
    cout<< equipo15 << " VS "<< equipo16;

    delete []vec;
}
void fase_16(int partidos_jugados){

}
void fase_32(int partidos_jugados){

}
