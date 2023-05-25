#ifndef ENTRADA_H
#define ENTRADA_H

class Entrada {
private:
    int codigoFecha;
    char* fechaEntrada;
    char* nombreDiscoteca;
    int numeroEntradas;
    char* cuentaGmail;
    char* numeroTarjetaCredito;
    char* cvvTarjeta;
    char* caducidadTarjeta;
    char* tipoEntrada;
    double precio;
    char* usuario;

public:
    Entrada();
    Entrada(int codigoFecha, char* fechaEntrada, char* nombreDiscoteca, int numeroEntradas, char* cuentaGmail, 
            char* numeroTarjetaCredito, char* cvvTarjeta, char* caducidadTarjeta, char* tipoEntrada, double precio, char* usuario);
    Entrada(const Entrada &entrada);
    ~Entrada();

    int getCodigoFecha();
    void setCodigoFecha(int codigoFecha);

    char* getFechaEntrada();
    void setFechaEntrada(char* fechaEntrada);

    char* getNombreDiscoteca();
    void setNombreDiscoteca(char* nombreDiscoteca);

    int getNumeroEntradas();
    void setNumeroEntradas(int numeroEntradas);

    char* getCuentaGmail();
    void setCuentaGmail(char* cuentaGmail);

    char* getNumeroTarjetaCredito();
    void setNumeroTarjetaCredito(char* numeroTarjetaCredito);

    char* getCvvTarjeta();
    void setCvvTarjeta(char* cvvTarjeta);

    char* getCaducidadTarjeta();
    void setCaducidadTarjeta(char* caducidadTarjeta);
    
    char* getTipoEntrada();
    void setTipoEntrada(char* tipoEntrada);

    double getPrecio();
    void setPrecio(double precio);

    char* getUsuario();
    void setUsuario(char* usuario);

    void printEntrada();
};

#endif
