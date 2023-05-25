#ifndef DIASFIESTA_H
#define DIASFIESTA_H

class DiasFiesta {
    private:
        int codigo_fecha;
        char* fecha;
        char* nombre_discoteca;
        int entradas_disponibles;
        char* evento_especial;

    public:
        DiasFiesta();
        DiasFiesta(int codigo_fecha, char* fecha, char* nombre_discoteca, int entradas_disponibles, char* evento_especial);
        DiasFiesta(const DiasFiesta &diasfiesta);
        ~DiasFiesta();

        int getCodigoFecha();
        void setCodigoFecha(int codigo_fecha);
        char* getFecha();
        void setFecha(char* fecha);
        char* getNombreDiscoteca();
        void setNombreDiscoteca(char* nombre_discoteca);
        int getEntradasDisponibles();
        void setEntradasDisponibles(int entradas_disponibles);
        char* getEventoEspecial();
        void setEventoEspecial(char* evento_especial);

        void printDiasFiesta();
};

#endif