# Projeto-EDOO-Purgatorio
Refazendo o jogo Purgatório (original em: https://github.com/Elanosinho/projeto-ip/tree/main) em C++ para o projeto da cadeira de EDOO na UFPE 

# Instruções de compilação e execução

**Pré-requisitos:**
- Compilador g++ com suporte a C++17

**Compilação:**
```g++ main.cpp -o main```
```./main```

# Como jogar
Primeiro de tudo, monte o tamanho do lado do seu campo minado (inteiro positivo) e a desidade de bombas no campo (número entre 0 e 1). Depois disso, responda com um caractére a ação que deseja realizar e coloque as cordenadas da sua ação (linha coluna). Se atente a suas ações e a quantidade de bandeiras que tem :)

# Divisão de tarefas
```txt
Integrantes:
  Arthur Araujo : Implementação da Classe Coletaveis
  João Pedro : Implementação da Classe Player
  Leon Gonçalves : Implementação do Campo Minado e a Simulação
  Marx Andrey : Implementação da Classe Interação
```

# Organização do projeto
```txt
Projeto-EDOO-Purgatorio/
├── main.cpp
├── README.md
├── CONTRIBUTING.MD
├── .gitignore
└── classes/
    ├── player/
    │   ├── player.hpp
    │   └── player.cpp
    ├── coletaveis/
    │   ├── coletaveis.hpp
    │   └── coletaveis.cpp
    ├── interaction/
    │   ├── interaction.hpp
    │   └── interaction.cpp
    └── campo minado/
        ├── campo_minado.hpp
        └── campo_minado.cpp

Classes Implementadas
1. Player - Gerencia o personagem jogador

Posição
Vidas e bandeiras
Sistema de pontuação com multiplicador

2. Coletáveis ​​- Sistema de itens colecionáveis ​​(herança)

Vida - Restaura vidas do jogador
N° de ações - Aumenta a quantidade de ações na partida
Flag - Adiciona bandeiras ao jogador
Cada item tem tempo de vida e timer

3. Interações - Gerencia interações do mouse

Controle cliques e pressionamentos do botão esquerdo e direito
Rastreia posição do mouse

4. CampoMinado - Implementa a lógica do campo minado

Geração estimada com densidade configurável
Contagem de bombas atráss
Sistema de revelação e marcação de bandeiras
Verificação de vitória
