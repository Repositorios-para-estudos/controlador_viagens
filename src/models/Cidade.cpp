#include "Cidade.h"

// Implementação do Construtor
// O "Cidade::" indica que esta função pertence à classe Cidade
Cidade::Cidade(std::string nome) {
    this->nome = nome;
    this->visitas = 0;
}

// Implementação dos métodos
std::string Cidade::getNome() {
    return this->nome;
}

void Cidade::registrarVisita() {
    this->visitas++;
}

int Cidade::getVisitas() {
    return this->visitas;
}