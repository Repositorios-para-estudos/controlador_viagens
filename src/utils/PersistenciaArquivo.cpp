#include "PersistenciaArquivos.h"
#include <iostream>

PersistenciaArquivo::PersistenciaArquivo(std::string diretorioBase) {
    this->diretorioBase = diretorioBase;
}

void PersistenciaArquivo::salvarCidades(const std::vector<Cidade*>& cidades) {
    std::ofstream arquivo(diretorioBase + "cidades.txt");

    if (arquivo.is_open()) {
        for (Cidade* cidade : cidades) {
            arquivo << cidade->getNome() << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar cidades.\n";
    }
}

std::vector<Cidade*> PersistenciaArquivo::carregarCidades() {
    std::vector<Cidade*> cidadesCarregadas;    
    std::ifstream arquivo(diretorioBase + "cidades.txt");
    std::string linha;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            Cidade* novaCidade = new Cidade(linha);
            cidadesCarregadas.push_back(novaCidade);
        }
        arquivo.close();
    }
    
    return cidadesCarregadas;
}

void PersistenciaArquivo::salvarTransportes(const std::vector<Transporte*>& transportes) {
    std::ofstream arquivo(diretorioBase + "transportes.txt");

    if (arquivo.is_open()) {
        for (Transporte* t : transportes) {
            // Convertendo o enum para inteiro para salvar no texto
            int tipoInt = static_cast<int>(t->getTipo());
            
            // Extraindo o nome da cidade atual a partir do ponteiro
            std::string nomeCidade = "";
            if (t->getLocalAtual() != nullptr) {
                nomeCidade = t->getLocalAtual()->getNome();
            }

            // Escreve no formato: 
            // Nome,Tipo,Capacidade,Velocidade,DistDescanso,TempoDescanso,NomeCidadeAtual
            arquivo << t->getNome() << ","
                    << tipoInt << ","
                    << t->getCapacidadePassageiros() << ","
                    << t->getVelocidadeMedia() << ","
                    << t->getDistanciaDescansos() << ","
                    << t->getTempoDescanso() << ","
                    << nomeCidade << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar transportes.\n";
    }
}

std::vector<Transporte*> PersistenciaArquivo::carregarTransportes(const std::vector<Cidade*>& cidadesCadastradas) {
    std::vector<Transporte*> transportesCarregados;
    std::ifstream arquivo(diretorioBase + "transportes.txt");
    std::string linha;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string item;
            std::vector<std::string> dados;

            // Fatiando a linha toda vez que encontrar uma vírgula
            while (std::getline(ss, item, ',')) {
                dados.push_back(item);
            }

            // Garantindo que a linha tinha os 7 atributos esperados
            if (dados.size() == 7) {
                std::string nome = dados[0];
                // Converte string pra int, depois pra enum
                TipoTerreno tipo = static_cast<TipoTerreno>(std::stoi(dados[1]));
                int capacidade = std::stoi(dados[2]);
                int velocidade = std::stoi(dados[3]);
                int distancia_descanso = std::stoi(dados[4]);
                int tempo_descanso = std::stoi(dados[5]);
                std::string nomeCidade = dados[6];

                // Busca o ponteiro da cidade correspondente ao nome lido
                Cidade* localAtual = nullptr;
                for (Cidade* c : cidadesCadastradas) {
                    if (c->getNome() == nomeCidade) {
                        localAtual = c;
                        break;
                    }
                }

                // Se a cidade foi encontrada, cria o transporte e adiciona à lista
                if (localAtual != nullptr) {
                    Transporte* novoTransporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_descanso, tempo_descanso, localAtual);
                    transportesCarregados.push_back(novoTransporte);
                } else {
                    std::cerr << "Aviso: Cidade '" << nomeCidade << "' nao encontrada. Transporte '" << nome << "' ignorado.\n";
                }
            }
        }
        arquivo.close();
    }
    
    return transportesCarregados;
}

void PersistenciaArquivo::salvarTrajetos(const std::vector<Trajeto*>& trajetos) {
    std::ofstream arquivo(diretorioBase + "trajetos.txt");

    if (arquivo.is_open()) {
        for (Trajeto* t : trajetos) {
            int tipoInt = static_cast<int>(t->getTipo());
            
            arquivo << t->getCidadeOrigem()->getNome() << ","
                    << t->getCidadeDestino()->getNome() << ","
                    << tipoInt << ","
                    << t->getDistanciaKm() << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar trajetos.\n";
    }
}

std::vector<Trajeto*> PersistenciaArquivo::carregarTrajetos(const std::vector<Cidade*>& cidadesCadastradas) {
    std::vector<Trajeto*> trajetosCarregados;
    std::ifstream arquivo(diretorioBase + "trajetos.txt");
    std::string linha;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string item;
            std::vector<std::string> dados;

            while (std::getline(ss, item, ',')) {
                dados.push_back(item);
            }

            if (dados.size() == 4) {
                std::string nomeOrigem = dados[0];
                std::string nomeDestino = dados[1];
                TipoTerreno tipo = static_cast<TipoTerreno>(std::stoi(dados[2]));
                int distancia = std::stoi(dados[3]);

                Cidade* cidadeOrigem = nullptr;
                Cidade* cidadeDestino = nullptr;

                for (Cidade* c : cidadesCadastradas) {
                    if (c->getNome() == nomeOrigem) {
                        cidadeOrigem = c;
                    }
                    if (c->getNome() == nomeDestino) {
                        cidadeDestino = c;
                    }
                }

                if (cidadeOrigem != nullptr && cidadeDestino != nullptr) {
                    Trajeto* novoTrajeto = new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
                    trajetosCarregados.push_back(novoTrajeto);
                } else {
                    std::cerr << "Aviso: Cidades '" << nomeOrigem << "' ou '" << nomeDestino << "' nao encontradas. Trajeto ignorado.\n";
                }
            }
        }
        arquivo.close();
    }
    
    return trajetosCarregados;
}

void PersistenciaArquivo::salvarPassageiros(const std::vector<Passageiro*>& passageiros) {
    std::ofstream arquivo(diretorioBase + "passageiros.txt");

    if (arquivo.is_open()) {
        for (Passageiro* p : passageiros) {
            std::string nomeCidade = "";
            if (p->getLocalAtual() != nullptr) {
                nomeCidade = p->getLocalAtual()->getNome();
            }

            arquivo << p->getNome() << ","
                    << nomeCidade << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar passageiros.\n";
    }
}

std::vector<Passageiro*> PersistenciaArquivo::carregarPassageiros(const std::vector<Cidade*>& cidadesCadastradas) {
    std::vector<Passageiro*> passageirosCarregados;
    std::ifstream arquivo(diretorioBase + "passageiros.txt");
    std::string linha;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string item;
            std::vector<std::string> dados;

            while (std::getline(ss, item, ',')) {
                dados.push_back(item);
            }

            if (dados.size() == 2) {
                std::string nomePassageiro = dados[0];
                std::string nomeCidadeAtual = dados[1];

                Cidade* cidadeAtual = nullptr;
                for (Cidade* c : cidadesCadastradas) {
                    if (c->getNome() == nomeCidadeAtual) {
                        cidadeAtual = c;
                        break;
                    }
                }

                if (cidadeAtual != nullptr) {
                    Passageiro* novoPassageiro = new Passageiro(nomePassageiro, cidadeAtual);
                    passageirosCarregados.push_back(novoPassageiro);
                } else {
                    std::cerr << "Aviso: Cidade '" << nomeCidadeAtual << "' nao encontrada. Passageiro '" << nomePassageiro << "' ignorado.\n";
                }
            }
        }
        arquivo.close();
    }
    
    return passageirosCarregados;
}