#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED
#define FILE_EQUIPOS "datos/equipos.dat"

class Equipo{
	private:
		int nro_equipo;
		char nombre_equipo[30];
		int goles_afavor;
		int goles_encontra;
		int partidos_ganados;
		int partidos_perdidos;
		bool activo;
	public:
	    Equipo();
		void cargar();
		void mostrar();
		bool escribrirEnDisco();
		bool guardarEnDisco();
		void setNro_equipo(int);
		void setNombre_equipo(char *);
		void setGoles_afavor(int);
		void setGoles_encontra(int);
		void setPartidos_ganados(int);
		void setPartidos_perdidos(int);
		void setActivo();
		int getNro_equipo();
		char *getNombre_equipo();
		int getGoles_afavor();
		int getGoles_encontra();
		int getPartidos_ganados();
		int getPartidos_perdidos();
		bool getActivo();
		void aumentar_gol_afavor(int);
        void aumentar_gol_encontra(int);
        void aumentar_partidos_ganados();
        void aumentar_partidos_perdidos();
};

void ingresar_equipos(int);

bool cargar_equipo(int cant_equipos);
bool cargar_jugadores(int cant_jugadores, int nroEquipo);
int contar_equiposCargados();

Equipo buscarEquipo(Equipo nro_equipo);

void listar_equipos();

bool nombre_equipo(char *,int);

bool checkrep(int n, int num[]);
void poner_equipos_aleatorios(int * vecAleatorio, int cant_equipos); //carga un vector aleatorio para poner en orden al alzar lo equipos
void sortear_equipos(int cantidad_equipos);
#endif // EQUIPO_H_INCLUDED
