# 🌍 Sistema Controlador de Viagens

Projeto desenvolvido para a disciplina de **Linguagem de Programação 1** da UFRN, sob orientação do Prof. Isaac Franco Fernandes.

Este sistema é uma solução em **C++** voltada para a gestão inteligente de tráfego, permitindo o cadastro de entidades e a simulação de deslocamentos complexos entre cidades, incluindo suporte a trajetos com múltiplas conexões.


## 🚀 Funcionalidades

* **Gestão Completa:** Cadastro de Cidades, Transportes (Aquáticos/Terrestres), Passageiros e Trajetos.
* **Simulação de Tráfego:** Cálculo automático de rotas (utilizando Busca em Largura - BFS) para encontrar o melhor caminho entre pontos.
* **Encadeamento de Viagens:** Suporte a viagens com conexões automáticas entre cidades.
* **Simulador de Tempo:** Avanço temporal que respeita a velocidade dos veículos e os períodos obrigatórios de descanso.
* **Relatórios Inteligentes:** Visão geral do estado do sistema, localização de passageiros/transportes e estatísticas de visitas às cidades.
* **Persistência de Dados:** Armazenamento local das informações em arquivos de texto, garantindo a continuidade do estado entre sessões.


## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (Padrão 11 ou superior).
* **Paradigma:** Orientação a Objetos (OO).
* **Persistência:** Manipulação de arquivos via `<fstream>`.
* **Algoritmos:** Busca em Largura (BFS) para cálculo de rotas.



## 📋 Como Executar

1. **Pré-requisitos:** Certifique-se de ter um compilador C++ (como `g++`) instalado.

2. **Clone o repositório:**
   ```bash
   git clone https://github.com/Repositorios-para-estudos/controlador_viagens.git
   cd sistema-controlador-viagens
3. **Compile o projeto:**
   ```bash
   make
4. **Execute:**
   ```bash
   ./controlador_viagens
## 🎓 Autor

Projeto acadêmico desenvolvido por Iohana Maria e Gemini Ai 3.1 Pro 👍.