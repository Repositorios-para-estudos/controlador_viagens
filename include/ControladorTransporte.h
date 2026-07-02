#pragma once
#include <vector>
#include <string>

// Incluindo todas as entidades que o controlador vai gerenciar
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"
#include "Tipos.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;

    Cidade* buscarCidade(const std::string& nome);
    Transporte* buscarTransporte(const std::string& nome);
    Passageiro* buscarPassageiro(const std::string& nome);

public:
    ControladorDeTransito();
    ~ControladorDeTransito();

    // Métodos de Cadastro
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, TipoTerreno tipo, int distancia);
    void cadastrarTransporte(std::string nome, TipoTerreno tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    
    // Gestão de Viagens e Simulação
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    
    // Relatórios solicitados no escopo do projeto
    void relatarEstado();
    void relatarOndeEstaoPessoas();
    void relatarOndeEstaoTransportes();
    void relatarViagensEmAndamento();
    void relatarCidadesMaisVisitadas();
};