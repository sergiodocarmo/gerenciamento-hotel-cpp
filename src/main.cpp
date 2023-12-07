
#include "../header/includes.hpp"

int main() {
    Sistema sistema;

    sistema.carregarDados("./data/dados.txt");

    int escolha;
    do {
        std::cout << "\nEscolha uma opcao:\n"
                  << "1. Adicionar Quarto\n"
                  << "2. Adicionar Cliente\n"
                  << "3. Realizar Reserva\n"
                  << "4. Mostrar Quartos\n"
                  << "5. Mostrar Clientes\n"
                  << "6. Mostrar Reservas\n"
                  << "7. Apagar Quarto\n"
                  << "8. Apagar Cliente\n"
                  << "9. Apagar Reservas\n"
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
                    std::cout << "Nao ha reservas cadastradas.\n";
                } else {
                    sistema.mostrarReservas();
                }
                break;
            case 7: {
                int numeroQuarto;
                std::cout << "Numero do Quarto a ser apagado: ";
                std::cin >> numeroQuarto;
                sistema.apagarQuarto(numeroQuarto);
                break;
            }
            case 8: {
                std::string nomeCliente;
                std::cout << "Nome do Cliente a ser apagado: ";
                std::cin.ignore();  // Limpar o buffer de entrada antes de getline
                std::getline(std::cin, nomeCliente);
                sistema.apagarCliente(nomeCliente);
                break;
            }
            case 9: {
                int numeroQuarto;
                std::cout << "Número do Quarto para remover a reserva: ";
                std::cin >> numeroQuarto;

                sistema.apagarReserva(numeroQuarto);
                break;
            }
            case 0:
                std::cout << "Saindo do programa.\n";
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
        }

    } while (escolha != 0);

    sistema.salvarDados("./dados/dados.txt");

    return 0;
}
