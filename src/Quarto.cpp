#include "Quarto.hpp"

Quarto::Quarto(int numero, int capacidade) : numero(numero), capacidade(capacidade), reservado(false) {}

int Quarto::getNumero() const { return numero; }

int Quarto::getCapacidade() const { return capacidade; }

bool Quarto::estaReservado() const { return reservado; }

void Quarto::reservar() { reservado = true; }

void Quarto::liberar() { reservado = false; }
