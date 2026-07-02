#include <queue>
#include <iostream>
#include <vector>
#include <string>

#include "ControladorTransporte.h"
#include "Tipos.h"

// Implementação do Construtor e Destrutor com a persistência de dados
ControladorTransporte::ControladorTransporte() : persistencia("data/") {
    this->cidades = persistencia.carregarCidades();
    this->transportes = persistencia.carregarTransportes(this->cidades);
    this->trajetos = persistencia.carregarTrajetos(this->cidades);
    this->passageiros = persistencia.carregarPassageiros(this->cidades);
}

ControladorTransporte::~ControladorTransporte() {
    persistencia.salvarCidades(this->cidades);
    persistencia.salvarTransportes(this->transportes);
    persistencia.salvarTrajetos(this->trajetos);
    persistencia.salvarPassageiros(this->passageiros);

    for (Cidade* cidade : cidades) {
        delete cidade;
    }
    for (Trajeto* trajeto : trajetos) {
        delete trajeto;
    }
    for (Transporte* transporte : transportes) {
        delete transporte;
    }
    for (Passageiro* passageiro : passageiros) {
        delete passageiro;
    }
    for (Viagem* viagem : viagens) {
        delete viagem;
    }
}

// Implementação dos métodos de busca
Cidade* ControladorTransporte::buscarCidade(const std::string& nome) {
    for (Cidade* cidade : cidades) {
        if (cidade->getNome() == nome) {
            return cidade;
        }
    }
    return nullptr;
}

Transporte* ControladorTransporte::buscarTransporte(const std::string& nome) {
    for (Transporte* transporte : transportes) {
        if (transporte->getNome() == nome) {
            return transporte;
        }
    }
    return nullptr;
}

Passageiro* ControladorTransporte::buscarPassageiro(const std::string& nome) {
    for (Passageiro* passageiro : passageiros) {
        if (passageiro->getNome() == nome) {
            return passageiro;
        }
    }
    return nullptr;
}

// Implementação do método de cálculo da melhor rota
std::vector<Trajeto*> ControladorTransporte::calcularMelhorRota(Cidade* origem, Cidade* destino, TipoTerreno tipoTransporte) {
    // Fila que guarda o par: {Cidade Atual, Caminho de Trajetos Até Aqui}
    std::queue<std::pair<Cidade*, std::vector<Trajeto*>>> fila;
    std::vector<Cidade*> visitados; // Evita loop infinito se A for para B e B voltar para A

    // Começamos na origem com um caminho vazio
    fila.push({origem, {}});

    while (!fila.empty()) {
        Cidade* atual = fila.front().first;
        std::vector<Trajeto*> caminhoAtual = fila.front().second;
        fila.pop();

        // Se chegamos no destino, retornamos a rota completa!
        if (atual == destino) {
            return caminhoAtual;
        }

        // Verifica se a cidade já foi visitada
        bool jaVisitado = false;
        for (Cidade* c : visitados) {
            if (c == atual) { jaVisitado = true; break; }
        }
        if (jaVisitado) continue;
        
        visitados.push_back(atual);

        // Procura todos os trajetos que saem da cidade atual
        for (Trajeto* t : trajetos) {
            // O trajeto deve sair da cidade atual E ser do mesmo tipo do transporte
            if (t->getCidadeOrigem() == atual && t->getTipo() == tipoTransporte) {
                // Cria um novo caminho adicionando este trajeto
                std::vector<Trajeto*> novoCaminho = caminhoAtual;
                novoCaminho.push_back(t);
                
                // Coloca a próxima cidade na fila de busca
                fila.push({t->getCidadeDestino(), novoCaminho});
            }
        }
    }

    // Se a fila esvaziar e não achar o destino, retorna um vetor vazio
    return {}; 
}

// Implementação dos métodos de cadastro
void ControladorTransporte::cadastrarCidade(std::string nome) {
    Cidade* novaCidade = new Cidade(nome);
    cidades.push_back(novaCidade);
}

void ControladorTransporte::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, TipoTerreno tipo, int distancia) {
    Cidade* cidadeOrigem = buscarCidade(nomeOrigem);
    Cidade* cidadeDestino = buscarCidade(nomeDestino);

    if (cidadeOrigem && cidadeDestino) {
        Trajeto* novoTrajeto = new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
        trajetos.push_back(novoTrajeto);
    }
}

void ControladorTransporte::cadastrarTransporte(std::string nome, TipoTerreno tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual) {
    Cidade* cidadeAtual = buscarCidade(localAtual);
    if (cidadeAtual) {
        Transporte* novoTransporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, cidadeAtual);
        transportes.push_back(novoTransporte);
    }
}

void ControladorTransporte::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade* cidadeAtual = buscarCidade(localAtual);
    if (cidadeAtual) {
        Passageiro* novoPassageiro = new Passageiro(nome, cidadeAtual);
        passageiros.push_back(novoPassageiro);
    }
}

// Implementação dos métodos de gestão de viagens e simulação
void ControladorTransporte::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, std::string nomeOrigem, std::string nomeDestino) {
    
    Transporte* transporte = buscarTransporte(nomeTransporte);
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);

    if (!transporte || !origem || !destino || transporte->getLocalAtual() != origem) {
        std::cout << "Dados inválidos ou transporte fora da origem" << std::endl;
        return;
    }

    std::vector<Passageiro*> passageirosDaViagem;
    for (const std::string& nomePass : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nomePass);
        if (p && p->getLocalAtual() == origem) {
            passageirosDaViagem.push_back(p);
        }
    }

    if ((int)passageirosDaViagem.size() > transporte->getCapacidadePassageiros()) {
        std::cout << "Capacidade excedida" << std::endl;
        return;
    }

    std::vector<Trajeto*> rota = calcularMelhorRota(origem, destino, transporte->getTipo());

    if (rota.empty()) {
        // Erro: Não existe caminho (nem direto, nem com conexões) para este tipo de transporte
        std::cout << "Não existe caminho disponível para este tipo de transporte" << std::endl;
        return;
    }

    // Desvincula o transporte e os passageiros das cidades físicas (agora estão em trânsito)
    transporte->setLocalAtual(nullptr); 
    for (Passageiro* p : passageirosDaViagem) {
        p->setLocalAtual(nullptr);
    }

    Viagem* viagemAnterior = nullptr;
    Viagem* primeiraViagem = nullptr;

    // Criar as "N" viagens com base nos trajetos encontrados
    for (size_t i = 0; i < rota.size(); ++i) {
        Trajeto* t = rota[i];
        
        // A origem e destino parciais são as cidades do trajeto específico
        Viagem* novaViagem = new Viagem(transporte, passageirosDaViagem, t, t->getCidadeOrigem(), t->getCidadeDestino());

        // Fazendo o encadeamento das conexões
        if (viagemAnterior != nullptr) {
            viagemAnterior->setProximaViagem(novaViagem);
        } else {
            primeiraViagem = novaViagem;
        }
        
        viagemAnterior = novaViagem;

        // Guardamos todas no controlador
        viagens.push_back(novaViagem);
    }

    // Somente a primeira viagem da cadeia é iniciada agora.
    // As outras só iniciarão quando o avancarHoras finalizar a anterior.
    if (primeiraViagem != nullptr) {
        primeiraViagem->iniciarViagem();
    }
}

void ControladorTransporte::avancarHoras(int horas) {
    for (Viagem* v : viagens) {
        if (v->isEmAndamento()) {
            v->avancarHoras(horas);
        }
    }
}