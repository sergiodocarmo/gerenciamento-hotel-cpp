#include <string>
#include "Pessoa.hpp"

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

class Cliente : public Pessoa {
public:
    Cliente(const std::string& nome, const std::string& telefone);

    std::string getTelefone() const;

private:
    std::string telefone;
};

#endif // CLIENTE_HPP
