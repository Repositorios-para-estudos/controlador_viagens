#include "Cidade.h"

// Implementação do Construtor
// O "Cidade::" indica que esta função pertence à classe Cidade
Cidade::Cidade(std::string nome) {
    this->nome = nome;
}

// Implementação do método getNome
std::string Cidade::getNome() {
    return this->nome;
}