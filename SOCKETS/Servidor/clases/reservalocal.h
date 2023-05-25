#ifndef RESERVALOCAL_H
#define RESERVALOCAL_H

class ReservaLocal {
private:
    int codigo;
    char* fecha;
    char* nombreDiscoteca;
    int aforo;
    char* numeroTarjeta;
    char* cvvTarjeta;
    char* caducidadTarjeta;

public:
    ReservaLocal();
    ReservaLocal(int codigo, char* fecha, char* nombreDiscoteca, int aforo, char* numeroTarjeta, char* cvvTarjeta, char* caducidadTarjeta);
    ReservaLocal(const ReservaLocal &reservaLocal);
    ~ReservaLocal();

    int getCodigo();
    void setCodigo(int codigo);

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
