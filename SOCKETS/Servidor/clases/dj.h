#ifndef DJ_H
#define DJ_H

class Dj {
    private:
        int id_dj;
        char* nombre_dj;
        char* genero_musical;
        char* fecha_nacimiento;
        char* numero_contacto;
    
    public:
        Dj();
        Dj(int id_dj, char* nombre_dj, char* genero_musical, char* fecha_nacimiento, char* numero_contacto);
        Dj(const Dj &dj);
        ~Dj();

        int getID();
        void setID(int id);
        char* getNombre();
        void setNombre(char* nombre);
        char* getGenero();
        void setGenero(char* genero);
        char* getFecha();
        void setFecha(char* fecha);
        char* getNumero();
        void setNumero(char* numero);

        void printDJ();
};

#endif