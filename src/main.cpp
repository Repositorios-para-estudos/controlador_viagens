#include <iostream>
#include <string>
#include "ControladorTransporte.h"

using namespace std;

// Função auxiliar para manter o main() limpo
void exibirMenu() {
    cout << "\n========================================\n";
    cout << "      SISTEMA CONTROLADOR DE VIAGENS      \n";
    cout << "========================================\n";
    cout << "1. Cadastrar Cidade\n";
    cout << "2. Cadastrar Transporte\n";
    cout << "3. Cadastrar Trajeto\n";
    cout << "4. Cadastrar Passageiro\n";
    cout << "5. Relatar Estado Geral\n";
    cout << "0. Sair do Sistema\n";
    cout << "----------------------------------------\n";
    cout << "Escolha uma opcao: ";
}

int main() {
    ControladorTransporte controlador;
    int opcao = -1;

    while (opcao != 0) {
        exibirMenu();
        cin >> opcao;

        cin.ignore(); 

        switch (opcao) {
            case 1: {
                string nomeCidade;
                cout << "Digite o nome da cidade: ";
                getline(cin, nomeCidade);
                
                controlador.cadastrarCidade(nomeCidade);
                cout << "Cidade '" << nomeCidade << "' enviada para cadastro!\n";
                break;
            }
            case 2: {
                string nomeTransporte, localAtual;
                TipoTerreno tipo;
                int capacidade, velocidade, distanciaEntreDescansos, tempoDeDescanso;

                cout << "Digite o nome do transporte: ";
                getline(cin, nomeTransporte);
                cout << "Digite o tipo de terreno (0 - Aquático, 1 - Terrestre): ";
                int tipoInput;
                cin >> tipoInput;
                tipo = static_cast<TipoTerreno>(tipoInput);
                cout << "Digite a capacidade do transporte: ";
                cin >> capacidade;
                cout << "Digite a velocidade do transporte: ";
                cin >> velocidade;
                cout << "Digite a distancia entre descansos: ";
                cin >> distanciaEntreDescansos;
                cout << "Digite o tempo de descanso: ";
                cin >> tempoDeDescanso;
                cin.ignore(); 
                cout << "Digite o local atual do transporte: ";
                getline(cin, localAtual);

                controlador.cadastrarTransporte(nomeTransporte, tipo, capacidade, velocidade, distanciaEntreDescansos, tempoDeDescanso, localAtual);
                cout << "Transporte '" << nomeTransporte << "' enviado para cadastro!\n";
                break;
            }
            case 3: {
                string nomeOrigem, nomeDestino;
                TipoTerreno tipo;
                int distancia;

                cout << "Digite o nome da cidade de origem: ";
                getline(cin, nomeOrigem);
                cout << "Digite o nome da cidade de destino: ";
                getline(cin, nomeDestino);
                cout << "Digite o tipo de terreno (0 - Aquático, 1 - Terrestre): ";
                int tipoInput;
                cin >> tipoInput;
                tipo = static_cast<TipoTerreno>(tipoInput);
                cout << "Digite a distancia do trajeto: ";
                cin >> distancia;
                cin.ignore(); 

                controlador.cadastrarTrajeto(nomeOrigem, nomeDestino, tipo, distancia);
                cout << "Trajeto de '" << nomeOrigem << "' para '" << nomeDestino << "' enviado para cadastro!\n";
                break;
            }
            case 4: {
                string nomePassageiro, nomeCidadeAtual;
                cout << "Digite o nome do passageiro: ";
                getline(cin, nomePassageiro);
                cout << "Digite o nome da cidade atual do passageiro: ";
                getline(cin, nomeCidadeAtual);
                
                controlador.cadastrarPassageiro(nomePassageiro, nomeCidadeAtual);
                cout << "Passageiro enviado para cadastro!\n";
                break;
            }
            // case 5:
            //     cout << "\n--- Relatorio de Estado ---\n";
            //     controlador.relatarEstado();
            //     break;
            case 0:
                cout << "Encerrando o sistema. Ate logo!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    }

    return 0;
}