#include "../header/Sistema.hpp"

Sistema::~Sistema()
{
    // Limpar a memória alocada dinamicamente
    for (auto quarto : quartos)
    {
        delete quarto;
    }
    for (auto cliente : clientes)
    {
        delete cliente;
    }
    for (auto reserva : reservas)
    {
        delete reserva;
    }
}

const std::vector<Quarto *>& Sistema::getQuartos() const { return quartos; }

const std::vector<Cliente *>& Sistema::getClientes() const { return clientes; }

const std::vector<Reserva *>& Sistema::getReservas() const { return reservas; }

void Sistema::adicionarQuarto(int numero, int capacidade)
{
    quartos.push_back(new Quarto(numero, capacidade));
}

Cliente* Sistema::adicionarCliente(const std::string &nome, const std::string &telefone)
{
    Cliente *cliente = new Cliente(nome, telefone);
    clientes.push_back(cliente);
    return cliente;
}

void Sistema::realizarReserva(Cliente *cliente, Quarto *quarto, const std::string &dataInicio, const std::string &dataFim)
{
    if (quarto->estaReservado())
    {
        std::cout << "Quarto ja reservado.\n";
    }
    else
    {
        quarto->reservar();
        reservas.push_back(new Reserva(cliente, quarto, dataInicio, dataFim));
    }
}

void Sistema::mostrarReservas() const
{
    for (const auto &reserva : reservas)
    {
        std::cout << "Cliente: " << reserva->getCliente()->getNome()
                  << ", Quarto: " << reserva->getQuarto()->getNumero()
                  << ", Data de Inicio: " << reserva->getDataInicio()
                  << ", Data de Fim: " << reserva->getDataFim() << "\n";
    }
}

void Sistema::mostrarQuartos() const
{
    std::cout << "\nLista de Quartos:\n";
    for (const auto &quarto : quartos)
    {
        std::cout << "Numero: " << quarto->getNumero() << ", Capacidade: " << quarto->getCapacidade();
        if (quarto->estaReservado())
        {
            std::cout << " (Reservado)";
        }
        std::cout << "\n";
    }
}

void Sistema::mostrarClientes() const
{
    std::cout << "\nLista de Clientes:\n";
    for (const auto &cliente : clientes)
    {
        std::cout << "Nome: " << cliente->getNome() << ", Telefone: " << cliente->getTelefone() << "\n";
    }
}

// Método para salvar os dados em um arquivo
void Sistema::salvarDados(const std::string &nomeArquivo)
{

    std::cout << "Salvando arquivo... \n";

    std::ofstream arquivo(nomeArquivo);

    // Salvar dados dos quartos
    for (const auto &quarto : quartos)
    {
        arquivo << "Quarto " << quarto->getNumero() << " " << quarto->getCapacidade() << "\n";
    }

    // Salvar dados dos clientes
    for (const auto &cliente : clientes)
    {
        arquivo << "Cliente " << cliente->getNome() << " " << cliente->getTelefone() << "\n";
    }

    // Salvar dados das reservas
    for (const auto &reserva : reservas)
    {
        arquivo << "Reserva " << reserva->getCliente()->getNome() << " " << reserva->getQuarto()->getNumero()
                << " " << reserva->getDataInicio() << " " << reserva->getDataFim() << "\n";
    }
}

void Sistema::carregarDados(const std::string &nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    std::cout << "\nLendo arquivo...\n";

    while (std::getline(arquivo, linha))
    {

        std::istringstream stream(linha);
        std::string tipo;

        // Lê o tipo (Quarto, Cliente, Reserva)
        stream >> tipo;

        if (tipo == "Quarto")
        {

            int numero, capacidade;
            stream >> numero >> capacidade;
            adicionarQuarto(numero, capacidade);
        }
        else if (tipo == "Cliente")
        {

            std::string nome, telefone;
            stream >> nome >> telefone;
            adicionarCliente(nome, telefone);
        }
        else if (tipo == "Reserva")
        {

            std::string nomeCliente, dataInicio, dataFim;
            int numeroQuarto;
            stream >> nomeCliente >> numeroQuarto >> dataInicio >> dataFim;

            Cliente *cliente = encontrarCliente(nomeCliente);
            Quarto *quarto = encontrarQuarto(numeroQuarto);

            if (cliente && quarto)
            {
                this->realizarReserva(cliente, quarto, dataInicio, dataFim);
            }
        }
    }
}

void Sistema::apagarQuarto(int numero)
{
    auto it = std::remove_if(quartos.begin(), quartos.end(), [numero](Quarto *q)
                             { return q->getNumero() == numero; });

    quartos.erase(it, quartos.end());
}

void Sistema::apagarCliente(const std::string &nome)
{
    auto it = std::remove_if(clientes.begin(), clientes.end(), [nome](Cliente *c)
                             { return c->getNome() == nome; });

    clientes.erase(it, clientes.end());
}

void Sistema::apagarReserva(int numeroQuarto)
{
    auto it = std::find_if(reservas.begin(), reservas.end(), [numeroQuarto](Reserva *reserva)
                           { return reserva->getQuarto()->getNumero() == numeroQuarto; });

    if (it != reservas.end())
    {
        (*it)->getQuarto()->liberar(); // Liberar o quarto associado à reserva
        delete *it;                    // Liberar a memória da reserva
        reservas.erase(it);
        std::cout << "Reserva do quarto " << numeroQuarto << " removida com sucesso.\n";
    }
    else
    {
        std::cout << "Reserva para o quarto " << numeroQuarto << " não encontrada.\n";
    }
}

Cliente* Sistema::encontrarCliente(const std::string &nome)
{
    for (const auto &cliente : clientes)
    {
        if (cliente->getNome() == nome)
        {
            return cliente;
        }
    }
    return nullptr;
}

Quarto* Sistema::encontrarQuarto(int numero)
{
    for (const auto &quarto : quartos)
    {
        if (quarto->getNumero() == numero)
        {
            return quarto;
        }
    }
    return nullptr;
}