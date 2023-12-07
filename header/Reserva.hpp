#include "Cliente.hpp"
#include "Quarto.hpp"
#include <string>

#ifndef RESERVA_HPP
#define RESERVA_HPP

class Reserva {
public:
    Reserva(Cliente* cliente, Quarto* quarto, const std::string& dataInicio, const std::string& dataFim);

    Cliente* getCliente() const;
    Quarto* getQuarto() const;
    std::string getDataInicio() const;
    std::string getDataFim() const;

private:
    Cliente* cliente;
    Quarto* quarto;
    std::string dataInicio;
    std::string dataFim;
};

#endif // RESERVA_HPP
