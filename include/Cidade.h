#pragma once
#include <string>

class Cidade {
private:
    std::string nome;
    int visitas;

public:
    Cidade(std::string nome);

    std::string getNome();
    void registrarVisita();
    int getVisitas();
};