#include <string>

class DJ {
public:
    int identificador;
    std::string nombre_comercial;
    std::string genero_musical;
    std::string fecha_nacimiento;
    std::string numero_contacto;
};

class RRPP {
public:
    int codigo_rrpp;
    std::string nombre;
    std::string zona_recogida;
    std::string hora_recogida;
    std::string numero_contacto;
};

class DiaDeFiesta {
public:
    int codigo_fecha;
    std::string fecha;
    std::string nombre_discoteca;
    int entradas_disponibles;
    std::string evento_especial;
};

class Usuario {
public:
    std::string nombre;
    std::string usuario;
    std::string sexo;
    int edad;
    std::string correo_electronico;
    std::string contrasenya;
    bool admin;
};

class ListaEventos {
public:
    std::string dia;
    std::string descripcion;
    std::string nombre_discoteca;
    int aforo;
};