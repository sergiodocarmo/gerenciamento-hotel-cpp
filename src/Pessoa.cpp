#include "Pessoa.hpp"

Pessoa::Pessoa(const std::string& nome) : nome(nome) {}

std::string Pessoa::getNome() const {
    return nome;
}
