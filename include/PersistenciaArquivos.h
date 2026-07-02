#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"

class PersistenciaArquivo {
private:
    std::string diretorioBase;

public:
    PersistenciaArquivo(std::string diretorioBase);

    void salvarCidades(const std::vector<Cidade*>& cidades);
    std::vector<Cidade*> carregarCidades();

    void salvarTransportes(const std::vector<Transporte*>& transportes);
    std::vector<Transporte*> carregarTransportes(const std::vector<Cidade*>& cidadesCadastradas);

    void salvarTrajetos(const std::vector<Trajeto*>& trajetos);
    std::vector<Trajeto*> carregarTrajetos(const std::vector<Cidade*>& cidadesCadastradas);

    void salvarPassageiros(const std::vector<Passageiro*>& passageiros);
    std::vector<Passageiro*> carregarPassageiros(const std::vector<Cidade*>& cidadesCadastradas);
};