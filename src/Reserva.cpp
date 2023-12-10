#include "../header/Reserva.hpp"

Reserva::Reserva(Cliente* cliente, Quarto* quarto, const std::string& dataInicio, const std::string& dataFim)
    : cliente(cliente), quarto(quarto), dataInicio(dataInicio), dataFim(dataFim) {}

Cliente* Reserva::getCliente() const { return cliente; }

Quarto* Reserva::getQuarto() const { return quarto; }

std::string Reserva::getDataInicio() const { return dataInicio; }

std::string Reserva::getDataFim() const { return dataFim; }
