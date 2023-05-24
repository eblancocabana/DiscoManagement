#ifndef ENTRADA_H
#define ENTRADA_H

#include <string>

class Entrada {
private:
    int codigoFecha;
    std::string fechaEntrada;
    std::string nombreDiscoteca;
    int numeroEntradas;
    std::string cuentaGmail;
    std::string numeroTarjetaCredito;
    std::string cvvTarjeta;
    std::string caducidadTarjeta;
    std::string tipoEntrada;
    double precio;

public:
    Entrada();
    Entrada(int codigoFecha, std::string fechaEntrada, std::string nombreDiscoteca, int numeroEntradas,
            std::string cuentaGmail, std::string numeroTarjetaCredito, std::string cvvTarjeta,
            std::string caducidadTarjeta, std::string tipoEntrada, double precio);
    Entrada(const Entrada &entrada);
    ~Entrada();

    int getCodigoFecha();
    void setCodigoFecha(int codigoFecha);
    std::string getFechaEntrada();
    void setFechaEntrada(std::string fechaEntrada);
    std::string getNombreDiscoteca();
    void setNombreDiscoteca(std::string nombreDiscoteca);
    int getNumeroEntradas();
    void setNumeroEntradas(int numeroEntradas);
    std::string getCuentaGmail();
    void setCuentaGmail(std::string cuentaGmail);
    std::string getNumeroTarjetaCredito();
    void setNumeroTarjetaCredito(std::string numeroTarjetaCredito);
    std::string getCvvTarjeta();
    void setCvvTarjeta(std::string cvvTarjeta);
    std::string getCaducidadTarjeta();
    void setCaducidadTarjeta(std::string caducidadTarjeta);
    std::string getTipoEntrada();
    void setTipoEntrada(std::string tipoEntrada);
    double getPrecio();
    void setPrecio(double precio);

    void printEntrada();
};

#endif
