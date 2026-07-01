#include "Trajeto.h"

Trajeto::Trajeto(Cidade* origem, Cidade* destino, TipoTerreno tipo, int distancia) {
    this->cidadeOrigem = origem;
    this->cidadeDestino = destino;
    this->tipo = tipo;
    this->distanciaKm = distancia;
}

Cidade* Trajeto::getCidadeOrigem() { return this->cidadeOrigem; }
Cidade* Trajeto::getCidadeDestino() { return this->cidadeDestino; }
TipoTerreno Trajeto::getTipo() { return this->tipo; }
int Trajeto::getDistanciaKm() { return this->distanciaKm; }