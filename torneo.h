#ifndef TORNEO_H_INCLUDED
#define TORNEO_H_INCLUDED
#define FILE_TORNEOS "datos/torneos.dat"

class Torneo {
    private:
        int tipo_torneo;///64 equipos, 32 equipos, 16 equipos o 8 equipos.
        int instancia_torneo;/// al iniciar torneo se carga con la llave inicial correspondiente. cuando pasa de llave se va cambiando el valor.
        int partidos_jugados;
        bool torneo_activo;
   public:
        Torneo();
        void setTipo_torneo(int);
        void setInstancia_torneo(int);
        void setPartidos_jugados(int);
        void setTorneo_activo(bool);
        int getTipo_torneo();
        int getInstancia_torneo();
        int getPartidos_jugados();
        bool getTorneo_activo();
        void cargar();
		void mostrar();
		bool escribrirEnDisco();
		bool guardarEnDisco();
};

int informar_tipoTorneo();
int seleccionar_torneo();
void cargar_resultado_partido();


void registrarResultado(int, int, int, int);

void registrarGol(int nro_equipo, int numeroCamiseta);

void registrarAsistencia(int nro_equipo, int numeroCamiseta);

void registrarAmarilla(int nro_equipo, int numeroCamiseta);

void registrarRoja(int nro_equipo, int numeroCamiseta);

void mostrar_llaveTorneo();

#endif // TORNEO_H_INCLUDED
