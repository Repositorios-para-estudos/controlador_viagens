#include <vector>
#include <string>

#include "ControladorTransporte.h"
#include "Tipos.h"

// Implementação do Construtor e Destrutor com a persistência de dados
ControladorTransporte::ControladorTransporte() : persistencia("data/") {
    this->cidades = persistencia.carregarCidades();
    this->transportes = persistencia.carregarTransportes(this->cidades);
    this->trajetos = persistencia.carregarTrajetos(this->cidades);
    this->passageiros = persistencia.carregarPassageiros(this->cidades);
}

ControladorTransporte::~ControladorTransporte() {
    persistencia.salvarCidades(this->cidades);
    persistencia.salvarTransportes(this->transportes);
    persistencia.salvarTrajetos(this->trajetos);
    persistencia.salvarPassageiros(this->passageiros);

    for (Cidade* cidade : cidades) {
        delete cidade;
    }
    for (Trajeto* trajeto : trajetos) {
        delete trajeto;
    }
    for (Transporte* transporte : transportes) {
        delete transporte;
    }
    for (Passageiro* passageiro : passageiros) {
        delete passageiro;
    }
    for (Viagem* viagem : viagens) {
        delete viagem;
    }
}

// Implementação dos métodos de busca
Cidade* ControladorTransporte::buscarCidade(const std::string& nome) {
    for (Cidade* cidade : cidades) {
        if (cidade->getNome() == nome) {
            return cidade;
        }
    }
    return nullptr;
}

Transporte* ControladorTransporte::buscarTransporte(const std::string& nome) {
    for (Transporte* transporte : transportes) {
        if (transporte->getNome() == nome) {
            return transporte;
        }
    }
    return nullptr;
}

Passageiro* ControladorTransporte::buscarPassageiro(const std::string& nome) {
    for (Passageiro* passageiro : passageiros) {
        if (passageiro->getNome() == nome) {
            return passageiro;
        }
    }
    return nullptr;
}

// Implementação dos métodos de cadastro
void ControladorTransporte::cadastrarCidade(std::string nome) {
    Cidade* novaCidade = new Cidade(nome);
    cidades.push_back(novaCidade);
}

void ControladorTransporte::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, TipoTerreno tipo, int distancia) {
    Cidade* cidadeOrigem = buscarCidade(nomeOrigem);
    Cidade* cidadeDestino = buscarCidade(nomeDestino);

    if (cidadeOrigem && cidadeDestino) {
        Trajeto* novoTrajeto = new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
        trajetos.push_back(novoTrajeto);
    }
}

void ControladorTransporte::cadastrarTransporte(std::string nome, TipoTerreno tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual) {
    Cidade* cidadeAtual = buscarCidade(localAtual);
    if (cidadeAtual) {
        Transporte* novoTransporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, cidadeAtual);
        transportes.push_back(novoTransporte);
    }
}

void ControladorTransporte::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade* cidadeAtual = buscarCidade(localAtual);
    if (cidadeAtual) {
        Passageiro* novoPassageiro = new Passageiro(nome, cidadeAtual);
        passageiros.push_back(novoPassageiro);
    }
}

