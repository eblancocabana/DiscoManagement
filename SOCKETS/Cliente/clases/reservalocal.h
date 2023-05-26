#ifndef RESERVALOCAL_H
#define RESERVALOCAL_H

class ReservaLocal {
private:
    char* codigo;
    char* fecha;
    char* nombreDiscoteca;
    int aforo;
    char* numeroTarjeta;
    char* cvvTarjeta;
    char* caducidadTarjeta;

public:
    ReservaLocal();
    ReservaLocal(char* codigo, char* fecha, char* nombreDiscoteca, int aforo, char* numeroTarjeta, char* cvvTarjeta, char* caducidadTarjeta);
    ReservaLocal(const ReservaLocal &reservaLocal);
    ~ReservaLocal();

    char* getCodigo();
    void setCodigo(char* codigo);

    char* getFecha();
    void setFecha(char* fecha);

    char* getNombreDiscoteca();
    void setNombreDiscoteca(char* nombreDiscoteca);

    int getAforo();
    void setAforo(int aforo);

    char* getNumeroTarjeta();
    void setNumeroTarjeta(char* numeroTarjeta);

    char* getCvvTarjeta();
    void setCvvTarjeta(char* cvvTarjeta);

    char* getCaducidadTarjeta();
    void setCaducidadTarjeta(char* caducidadTarjeta);

    void printReservaLocal();
};

#endif
