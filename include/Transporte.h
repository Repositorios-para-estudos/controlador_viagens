#pragma once
#include <string>
#include "Cidade.h"
#include "Tipos.h"

class Transporte
{
private:
    std::string nome;
    TipoTerreno tipo;
    int capacidadePassageiros;
    int velocidadeMedia;
    int distanciaDescansos;
    int tempoDescanso;
    int tempoDescansoAtual;
    Cidade* localAtual;

public:
    Transporte(std::string nome, TipoTerreno tipo, int capacidadePassageiros, int velocidadeMedia, int distanciaDescansos, int tempoDescanso, Cidade* localAtual);

    std::string getNome();
    TipoTerreno getTipo();
    int getCapacidadePassageiros();
    int getVelocidadeMedia();
    int getDistanciaDescansos();
    int getTempoDescanso();
    int getTempoDescansoAtual();
    Cidade* getLocalAtual();

    void setLocalAtual(Cidade* local);
    void setTempoDescansoAtual(int tempo);
};

