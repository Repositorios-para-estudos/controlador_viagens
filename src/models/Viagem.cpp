#include "Viagem.h"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* cidadeOrigem, Cidade* cidadeDestino) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->cidadeOrigem = cidadeOrigem;
    this->cidadeDestino = cidadeDestino;
    this->proximaViagem = nullptr;
    this->horasEmTransito = 0;
    this->emAndamento = false;
}