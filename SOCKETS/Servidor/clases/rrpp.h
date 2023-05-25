#ifndef RRPP_H
#define RRPP_H

class RRPP {
    private:
        int codigo_rrpp;
        char* nombre;
        char* zona_recogida;
        char* hora_recogida;
        char* numero_contacto;

    public:
        RRPP();
        RRPP(int codigo_rrpp, char* nombre, char* zona_recogida, char* hora_recogida, char* numero_contacto);
        RRPP(const RRPP &rrpp);
        ~RRPP();

        int getCodigoRRPP();
        void setCodigoRRPP(int codigo_rrpp);
        char* getNombre();
        void setNombre(char* nombre);
        char* getZonaRecogida();
        void setZonaRecogida(char* zona_recogida);
        char* getHoraRecogida();
        void setHoraRecogida(char* hora_recogida);
        char* getNumeroContacto();
        void setNumeroContacto(char* numero_contacto);

        void printRRPP();
};

#endif