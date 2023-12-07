#include <string>

#ifndef PESSOA_HPP
#define PESSOA_HPP

class Pessoa {
public:
    Pessoa(const std::string& nome);

    std::string getNome() const;

private:
    std::string nome;
};

#endif // PESSOA_HPP
