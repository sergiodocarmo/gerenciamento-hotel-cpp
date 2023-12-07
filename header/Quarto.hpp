#ifndef QUARTO_HPP
#define QUARTO_HPP

class Quarto {
public:
    Quarto(int numero, int capacidade);

    int getNumero() const;
    int getCapacidade() const;
    bool estaReservado() const;

    void reservar();
    void liberar();

private:
    int numero;
    int capacidade;
    bool reservado;
};

#endif // QUARTO_HPP
