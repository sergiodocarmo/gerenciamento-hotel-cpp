#include "Cliente.hpp"

Cliente::Cliente(const std::string &nome, const std::string &telefone) : Pessoa(nome), telefone(telefone) {}

std::string Cliente::getTelefone() const { return telefone; }
