# Nome do executável final
TARGET = controlador_viagens

# Compilador e opções de compilação (Flags)
# -Wall: Mostra todos os avisos (warnings) para te ajudar a achar erros
# -std=c++11: Usa a versão moderna do C++
# -Iinclude: Diz ao compilador onde procurar os arquivos .h
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Diretórios
SRC_DIR = src
MODELS_DIR = $(SRC_DIR)/models
CONTROLLERS_DIR = $(SRC_DIR)/controllers
UTILS_DIR = $(SRC_DIR)/utils

# Encontra todos os arquivos .cpp nas pastas
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(MODELS_DIR)/*.cpp) \
          $(wildcard $(CONTROLLERS_DIR)/*.cpp) \
          $(wildcard $(UTILS_DIR)/*.cpp)

# Transforma a lista de .cpp em uma lista de .o (arquivos objeto)
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão (o que acontece quando você digita apenas 'make')
all: $(TARGET)

# Como construir o executável final juntando todos os .o
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Compilação concluída! Execute com ./$(TARGET)"

# Como compilar cada arquivo .cpp individualmente
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados (útil para recomeçar do zero)
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Arquivos compilados foram limpos."