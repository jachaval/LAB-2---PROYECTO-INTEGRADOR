#ifndef PARTIDO_H_INCLUDED
#define PARTIDO_H_INCLUDED
#define FILE_PARTIDOS "partidos.dat"

class Partido {
private:
    int codigo_toneo;
    int equipo_local;
    int equipo_visitante;
    int goles_local;
    int goles_visitante;
    int equipo_ganador;
    int instancia_torneo;
    int nro_partido;
public:
    void setCodigo_toneo(int);
    void setEquipo_local(int);
    void setEquipo_visitante(int);
    void setGoles_local(int);
    void setGoles_visitante(int);
    void setEquipo_ganador(int);
    void setInstancia_torneo(int);
    void setNro_partido(int);
    int getCodigo_toneo();
    int getEquipo_local();
    int getEquipo_visitante();
    int getGoles_local();
    int getGoles_visitante();
    int getEquipo_ganador();
    int getInstancia_torneo();
    int getNro_partido();
    bool escribrirEnDisco();
    bool guardarEnDisco();
};

#endif // PARTIDO_H_INCLUDED
