#pragma once
#include <vector>
#include <string>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;

    // Métodos auxiliares privados são essenciais para manter o código limpo
    Cidade* buscarCidade(std::string nome);
    Transporte* buscarTransporte(std::string nome);
    Passageiro* buscarPassageiro(std::string nome);

public:
    ~ControladorDeTransito();
    
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, TipoTerreno tipo, int distancia);
    void cadastrarTransporte(std::string nome, TipoTerreno tipo, int capacidade, int velocidade, int distDescanso, int tempoDescanso, std::string nomeCidade);
    void cadastrarPassageiro(std::string nome, std::string nomeCidade);
    
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    
    void relatarEstado();
};