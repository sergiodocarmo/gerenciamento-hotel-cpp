#include "Cliente.hpp"
#include "Quarto.hpp"
#include "Reserva.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#ifndef SISTEMA_HPP
#define SISTEMA_HPP

class Sistema {
public:
    ~Sistema();

    void adicionarQuarto(int numero, int capacidade);
    Cliente* adicionarCliente(const std::string& nome, const std::string& telefone);
    void realizarReserva(Cliente* cliente, Quarto* quarto, const std::string& dataInicio, const std::string& dataFim);
    void mostrarReservas() const;
    void mostrarQuartos() const;
    void mostrarClientes() const;

    const std::vector<Quarto*>& getQuartos() const;
    const std::vector<Cliente*>& getClientes() const;
    const std::vector<Reserva*>& getReservas() const;

    void salvarDados(const std::string& nomeArquivo);
    void carregarDados(const std::string& nomeArquivo);

    void apagarQuarto(int numero);
    void apagarCliente(const std::string& nome);
    void apagarReserva(int numeroQuarto);

private:
    std::vector<Quarto*> quartos;
    std::vector<Cliente*> clientes;
    std::vector<Reserva*> reservas;

    Cliente* encontrarCliente(const std::string& nome);
    Quarto* encontrarQuarto(int numero);
};

#endif // SISTEMA_HPP