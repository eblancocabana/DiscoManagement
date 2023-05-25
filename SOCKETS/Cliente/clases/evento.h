#ifndef EVENTO_H
#define EVENTO_H

class Evento {
    private:
        char* dia;
        char* descripcion;
        char* nombre_discoteca;
        int aforo;

    public:
        Evento();
        Evento(char* dia, char* descripcion, char* nombre_discoteca, int aforo);
        Evento(const Evento &evento);
        ~Evento();

        char* getDia();
        void setDia(char* dia);
        char* getDescripcion();
        void setDescripcion(char* descripcion);
        char* getNombreDiscoteca();
        void setNombreDiscoteca(char* nombre_discoteca);
        int getAforo();
        void setAforo(int aforo);

        void printEvento();
};

#endif