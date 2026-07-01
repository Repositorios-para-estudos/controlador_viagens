#pragma once
#include <string>
#include "Cidade.h"
#include "Tipos.h"

class Trajeto{
private:
    Cidade* cidadeOrigem;
    Cidade* cidadeDestino;
    TipoTerreno tipo;
    int distanciaKm;

public:

    Trajeto(Cidade* origem, Cidade* destino, TipoTerreno tipo, int distancia);

    Cidade* getCidadeOrigem();
    Cidade* getCidadeDestino();
    TipoTerreno getTipo();
    int getDistanciaKm();
};

