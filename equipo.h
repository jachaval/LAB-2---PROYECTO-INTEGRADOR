#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED
#define FILE_EQUIPOS "equipos.dat"

class Equipo{
	private:
		int nro_equipo;
		char nombre_equipo[30];
		int goles_afavor;
		int goles_encontra;
		int partidos_ganados;
		int partidos_perdidos;
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
		int getNro_equipo();
		char *getNombre_equipo();
		int getGoles_afavor();
		int getGoles_encontra();
		int getPartidos_ganados();
		int getPartidos_perdidos();

};

void ingresar_equipos(int);

bool cargar_equipo(int cant_equipos);
bool cargar_jugadores(int cant_jugadores);
int contar_equiposCargados();

#endif // EQUIPO_H_INCLUDED
