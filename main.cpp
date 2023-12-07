#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

class Pessoa {
public:
    Pessoa(const std::string& nome) : nome(nome) {}

    std::string getNome() const { return nome; }

private:
    std::string nome;
};

class Quarto {
public:
    Quarto(int numero, int capacidade) : numero(numero), capacidade(capacidade), reservado(false) {}

    int getNumero() const { return numero; }
    int getCapacidade() const { return capacidade; }
    bool estaReservado() const { return reservado; }

    void reservar() { reservado = true; }
    void liberar() { reservado = false; }

private:
    int numero;
    int capacidade;
    bool reservado;
};

class Cliente : public Pessoa {
public:
    Cliente(const std::string& nome, const std::string& telefone) : Pessoa(nome), telefone(telefone) {}

    std::string getTelefone() const { return telefone; }

private:
    std::string telefone;
};

class Reserva {
public:
    Reserva(Cliente* cliente, Quarto* quarto, const std::string& dataInicio, const std::string& dataFim)
        : cliente(cliente), quarto(quarto), dataInicio(dataInicio), dataFim(dataFim) {}

    Cliente* getCliente() const { return cliente; }
    Quarto* getQuarto() const { return quarto; }
    std::string getDataInicio() const { return dataInicio; }
    std::string getDataFim() const { return dataFim; }

private:
    Cliente* cliente;
    Quarto* quarto;
    std::string dataInicio;
    std::string dataFim;
};

class SistemaReservasHotel {
public:

    ~SistemaReservasHotel() {
        // Limpar a memória alocada dinamicamente
        for (auto quarto : quartos) {
            delete quarto;
        }
        for (auto cliente : clientes) {
            delete cliente;
        }
        for (auto reserva : reservas) {
            delete reserva;
        }
    }

    void adicionarQuarto(int numero, int capacidade) {
        quartos.push_back(new Quarto(numero, capacidade));
    }

    Cliente* adicionarCliente(const std::string& nome, const std::string& telefone) {
        Cliente* cliente = new Cliente(nome, telefone);
        clientes.push_back(cliente);
        return cliente;
    }

    void realizarReserva(Cliente* cliente, Quarto* quarto, const std::string& dataInicio, const std::string& dataFim) {
        if (quarto->estaReservado()) {
            std::cout << "Quarto ja reservado.\n";
        } else {
            quarto->reservar();
            reservas.push_back(new Reserva(cliente, quarto, dataInicio, dataFim));
        }
    }

    void mostrarReservas() const {
        for (const auto& reserva : reservas) {
            std::cout << "Cliente: " << reserva->getCliente()->getNome()
                      << ", Quarto: " << reserva->getQuarto()->getNumero()
                      << ", Data de Inicio: " << reserva->getDataInicio()
                      << ", Data de Fim: " << reserva->getDataFim() << "\n";
        }
    }

    void mostrarQuartos() const {
    std::cout << "\nLista de Quartos:\n";
    for (const auto& quarto : quartos) {
        std::cout << "Numero: " << quarto->getNumero() << ", Capacidade: " << quarto->getCapacidade();
        if (quarto->estaReservado()) {
            std::cout << " (Reservado)";
        }
        std::cout << "\n";
    }
}

void mostrarClientes() const {
    std::cout << "\nLista de Clientes:\n";
    for (const auto& cliente : clientes) {
        std::cout << "Nome: " << cliente->getNome() << ", Telefone: " << cliente->getTelefone() << "\n";
    }
}

    const std::vector<Quarto*>& getQuartos() const { return quartos; }

    const std::vector<Cliente*>& getClientes() const { return clientes; }

    const std::vector<Reserva*>& getReservas() const { return reservas; }

    // Método para salvar os dados em um arquivo
    void salvarDados(const std::string& nomeArquivo) {

            std::cout << "Salvando arquivo... \n";

        std::ofstream arquivo(nomeArquivo);

        // Salvar dados dos quartos
        for (const auto& quarto : quartos) {
            arquivo << "Quarto " << " " << quarto->getNumero() << " " << quarto->getCapacidade() << "\n";
        }

        // Salvar dados dos clientes
        for (const auto& cliente : clientes) {
            arquivo << "Cliente " << " " << cliente->getNome() << " " << cliente->getTelefone() << "\n";
        }

        // Salvar dados das reservas
        for (const auto& reserva : reservas) {
            arquivo << "Reserva " << reserva->getCliente()->getNome() << " " << reserva->getQuarto()->getNumero()
                    << " " << reserva->getDataInicio() << " " << reserva->getDataFim() << "\n";
        }
    }

    void carregarDados(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        std::string linha;

        std::cout << "\nLendo arquivo...\n";

        while (std::getline(arquivo, linha)) {

            std::istringstream stream(linha);
            std::string tipo;

            // Lê o tipo (Quarto, Cliente, Reserva)
            stream >> tipo;

            if (tipo == "Quarto") {

                int numero, capacidade;
                stream >> numero >> capacidade;
                adicionarQuarto(numero, capacidade);

            } else if (tipo == "Cliente") {

                std::string nome, telefone;
                stream >> nome >> telefone;
                adicionarCliente(nome, telefone);

            } else if (tipo == "Reserva") {

                std::string nomeCliente, dataInicio, dataFim;
                int numeroQuarto;
                stream >> nomeCliente >> numeroQuarto >> dataInicio >> dataFim;

                Cliente* cliente = encontrarCliente(nomeCliente);
                Quarto* quarto = encontrarQuarto(numeroQuarto);
                
                if (cliente && quarto) {
                    this->realizarReserva(cliente, quarto, dataInicio, dataFim);
                }
            }
        }
    }

private:
    std::vector<Quarto*> quartos;
    std::vector<Cliente*> clientes;
    std::vector<Reserva*> reservas;

    Cliente* encontrarCliente(const std::string& nome) {
        for (const auto& cliente : clientes) {
            if (cliente->getNome() == nome) {
                return cliente;
            }
        }
        return nullptr;
    }

    Quarto* encontrarQuarto(int numero) {
        for (const auto& quarto : quartos) {
            if (quarto->getNumero() == numero) {
                return quarto;
            }
        }
        return nullptr;
    }
};

int main() {
    SistemaReservasHotel sistema;

    sistema.carregarDados("dados.txt");

    int escolha;
    do {
        std::cout << "\nEscolha uma opcao:\n"
                  << "1. Adicionar Quarto\n"
                  << "2. Adicionar Cliente\n"
                  << "3. Realizar Reserva\n"
                  << "4. Mostrar Quartos\n"
                  << "5. Mostrar Clientes\n"
                  << "6. Mostrar Reservas\n"
                  << "0. Sair\n"
                  << "Opcao: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1: {
                int numero, capacidade;
                std::cout << "Numero do Quarto: ";
                std::cin >> numero;
                std::cout << "Capacidade do Quarto: ";
                std::cin >> capacidade;
                sistema.adicionarQuarto(numero, capacidade);
                break;
            }
            case 2: {
                std::string nome, telefone;
                std::cout << "Nome do Cliente: ";
                std::cin.ignore();  // Limpar o buffer de entrada antes de getline
                std::getline(std::cin, nome);
                std::cout << "Telefone do Cliente: ";
                std::cin >> telefone;
                sistema.adicionarCliente(nome, telefone);
                break;
            }
            case 3: {
                std::string nomeCliente;
                int numeroQuarto;
                std::string dataInicio, dataFim;

                std::cout << "Nome do Cliente: ";
                std::cin.ignore();  // Limpar o buffer de entrada antes de getline
                std::getline(std::cin, nomeCliente);

                Cliente* cliente = nullptr;
                for (const auto& c : sistema.getClientes()) {
                    if (c->getNome() == nomeCliente) {
                        cliente = c;
                        break;
                    }
                }

                if (!cliente) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }

                std::cout << "Numero do Quarto: ";
                std::cin >> numeroQuarto;
                std::cout << "Data de Inicio (YYYY-MM-DD): ";
                std::cin >> dataInicio;
                std::cout << "Data de Fim (YYYY-MM-DD): ";
                std::cin >> dataFim;

                Quarto* quarto = nullptr;
                for (const auto& q : sistema.getQuartos()) {
                    if (q->getNumero() == numeroQuarto) {
                        quarto = q;
                        break;
                    }
                }

                if (!quarto) {
                    std::cout << "Quarto nao encontrado.\n";
                    break;
                }

                sistema.realizarReserva(cliente, quarto, dataInicio, dataFim);
                std::cout << "Reserva realizada com sucesso.\n";
                break;
            }
            case 4:
                sistema.mostrarQuartos();
                break;
            case 5:
                sistema.mostrarClientes();
                break;
            case 6:
                if (sistema.getReservas().empty()) {
                    std::cout << "Não há reservas cadastradas.\n";
                } else {
                    sistema.mostrarReservas();
                }
                break;
            case 0:
                std::cout << "Saindo do programa.\n";
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
        }

    } while (escolha != 0);

    sistema.salvarDados("dados.txt");

    return 0;
}
