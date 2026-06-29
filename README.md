# AEstrela

O **AEstrela** é um motor de busca e navegação espacial implementado em C++ projetado para simular, validar e analisar o comportamento de algoritmos de busca em grafos de grade (*Grid Graphs*). O projeto foi estruturado seguindo rigorosamente os padrões de abstração e modelagem de agentes descritos no livro *Inteligência Artificial: Uma Abordagem Moderna* (Russell & Norvig).

O objetivo principal do sistema é isolar a lógica do ambiente (um mapa matricial de cruzamentos e custos) dos motores de busca, permitindo uma análise comparativa de performance, otimalidade e eficiência sob diferentes configurações de caminhos e densidades de obstáculos.

## 🚀 Funcionalidades Planejadas

- **Abstração de Ambiente:** Encapsulamento completo de matrizes de custo $15\times15$ com suporte a bloqueios estáticos (obstáculos).
- **Motores de Busca:**
  - *Busca de Melhor Escolha (Best-First Search):* Implementação genérica baseada em Fila de Prioridades (Min-Heap) configurável para **A*** e **Busca Gulosa**.
  - *Busca Local (Hill Climbing):* Variações de Subida de Encosta (Gulosa Determinística, Maior Aclive e Estocástica).
- **Métricas Geométricas:** Implementação exata das funções heurísticas de Distância Manhattan e Distância Euclidiana (piso inteiro).
- **Módulo de Experimentos:** Gerador automático de instâncias aleatórias com validação prévia de conectividade por via de Busca em Largura (BFS) e exportação de relatórios em `.csv`.
- **Visualização:** Impressão do mapa no console utilizando caracteres de bloco e cores ANSI para destacar a fronteira explorada e o caminho ótimo encontrado.

## 📁 Estrutura do Projeto

```text
├── CMakeLists.txt        # Script de build do CMake
├── data/                 # Gerenciamento de arquivos do sistema
│   ├── entradas/         # Matrizes geradas e validadas (.txt)
│   └── resultados/       # Dados coletados dos experimentos (.csv)
├── include/              # Arquivos de cabeçalho (.hpp)
│   ├── core/             # Modelagem do Problema, Nós e Estados
│   ├── heuristicas/      # Interfaces e implementações das distâncias
│   └── buscas/           # Algoritmos de busca local e de fronteira
└── src/                  # Arquivos de implementação (.cpp)
    └── main.cpp          # Orquestrador / Executor dos experimentos

## 🛠️ Pré-requisitos & Compilação

Para compilar e executar este projeto, você precisará de um compilador C++ com suporte ao padrão C++17 (ou superior) e o sistema de build CMake.

### Compilação via terminal (Linux)

1. Clone o repositório
```
git clone [https://github.com/seu-usuario/heurigrid.git](https://github.com/seu-usuario/heurigrid.git)
cd heurigrid
```
2. Crie o diretório de build e compile:
```
mkdir build && cd build
cmake ..
make
```
3. Execute o programa
```
./aestrela
```

## 📝 Licença
Este projeto foi desenvolvido para fins estritamente acadêmicos e de pesquisa institucional
