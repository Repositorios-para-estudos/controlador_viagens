#pragma once
#include <vector>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Trajeto* trajeto;
    Cidade* cidadeOrigem;
    Cidade* cidadeDestino;
    
    Viagem* proximaViagem; // Ponteiro pra conexão da viagem com outra viagem
    int distanciaPercorrida;
    int horasEmTransito;
    bool emAndamento;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Trajeto* trajeto, Cidade* cidadeOrigem, Cidade* cidadeDestino);

    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();
    

    void setProximaViagem(Viagem* proximaViagem);
    Viagem* getProximaViagem();
    void finalizarViagem(); 
};