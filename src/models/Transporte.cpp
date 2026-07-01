#include "Transporte.h"

Transporte::Transporte(std::string nome, TipoTerreno tipo, int capacidadePassageiros, int velocidadeMedia, int distanciaDescansos, int tempoDescanso, Cidade* localAtual) {
    this->nome = nome;
    this->tipo = tipo;
    this->capacidadePassageiros = capacidadePassageiros;
    this->velocidadeMedia = velocidadeMedia;
    this->distanciaDescansos = distanciaDescansos;
    this->tempoDescanso = tempoDescanso;
    this->tempoDescansoAtual = 0;
    this->localAtual = localAtual;
}

std::string Transporte::getNome() { return this->nome; }
TipoTerreno Transporte::getTipo() { return this->tipo; }
int Transporte::getCapacidadePassageiros() { return this->capacidadePassageiros; }
int Transporte::getVelocidadeMedia() { return this->velocidadeMedia; }
int Transporte::getDistanciaDescansos() { return this->distanciaDescansos; }
int Transporte::getTempoDescanso() { return this->tempoDescanso; }
int Transporte::getTempoDescansoAtual() { return this->tempoDescansoAtual; }
Cidade* Transporte::getLocalAtual() { return this->localAtual; }

void Transporte::setLocalAtual(Cidade* local) { this->localAtual = local; }
void Transporte::setTempoDescansoAtual(int tempo) { this->tempoDescansoAtual = tempo; }