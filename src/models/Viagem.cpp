#include <iostream>

#include "Viagem.h"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Trajeto* trajeto, Cidade* cidadeOrigem, Cidade* cidadeDestino) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->trajeto = trajeto;
    this->cidadeOrigem = cidadeOrigem;
    this->cidadeDestino = cidadeDestino;
    this->proximaViagem = nullptr;
    this->horasEmTransito = 0;
    this->emAndamento = false;
    this->distanciaPercorrida = 0;
}

void Viagem::iniciarViagem() {
    this->emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;

    // Simulamos hora a hora para contabilizar os descansos corretamente
    for (int i = 0; i < horas; ++i) {
        this->horasEmTransito++;

        // Verifica se o transporte está em período de descanso
        if (transporte->getTempoDescansoAtual() > 0) {
            // Fica parado descansando
            transporte->setTempoDescansoAtual(transporte->getTempoDescansoAtual() - 1);
        } else {
            // O transporte anda de acordo com sua velocidade (Km/h)
            distanciaPercorrida += transporte->getVelocidadeMedia();

            // Verifica se andou o suficiente para precisar de um novo descanso
            // Evitamos divisões por zero checando se a distância entre descansos é maior que zero
            if (transporte->getDistanciaDescansos() > 0 && 
                distanciaPercorrida % transporte->getDistanciaDescansos() == 0) {
                transporte->setTempoDescansoAtual(transporte->getTempoDescanso());
            }
        }

        // Verifica se chegou ao destino
        if (distanciaPercorrida >= trajeto->getDistanciaKm()) {
            finalizarViagem();
            break;
        }
    }
}

void Viagem::relatarEstado() {
    std::cout << "Viagem de " << cidadeOrigem->getNome() << " para " << cidadeDestino->getNome() << std::endl;
    std::cout << "Transporte: " << transporte->getNome() << std::endl;
    std::cout << "Passageiros: ";
    for (auto passageiro : passageiros) {
        std::cout << passageiro->getNome() << " ";
    }
    std::cout << std::endl;
    std::cout << "Horas em trânsito: " << horasEmTransito << std::endl;
    std::cout << "Em andamento: " << (emAndamento ? "Sim" : "Não") << std::endl;
}

bool Viagem::isEmAndamento() {
    return emAndamento;
}

Transporte* Viagem::getTransporte() {
    return transporte;
}

Cidade* Viagem::getCidadeOrigem() {
    return cidadeOrigem;
}

Cidade* Viagem::getCidadeDestino() {
    return cidadeDestino;
}

bool Viagem::temPassageiro(Passageiro* pBusca) {
    for (Passageiro* p : passageiros) {
        if (p == pBusca) return true;
    }
    return false;
}

void Viagem::setProximaViagem(Viagem* proximaViagem) {
    this->proximaViagem = proximaViagem;
}

Viagem* Viagem::getProximaViagem() {
    return proximaViagem;
}

void Viagem::finalizarViagem() {
    this->emAndamento = false;

    // Se existe uma próxima viagem, é uma conexão!
    if (this->proximaViagem != nullptr) {
        // Inicia a próxima etapa da viagem conectada
        this->proximaViagem->iniciarViagem();
        
        // Os passageiros e transportes continuam com localAtual = nullptr (em trânsito)
    } 
    else {
        transporte->setLocalAtual(cidadeDestino);
        for (auto passageiro : passageiros) {
            passageiro->setLocalAtual(cidadeDestino);
        }
        cidadeDestino->registrarVisita();
    }
}