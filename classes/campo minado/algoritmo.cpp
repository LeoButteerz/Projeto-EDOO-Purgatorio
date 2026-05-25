#include "algoritmo.h"
//bibliotecas para embaralhar o campo minado
#include <algorithm>
#include <random>

//definição do construtor
CampoMinado::CampoMinado(int tamanho, double densidade) {
    this->tamanho = tamanho;
    this->linhas = tamanho;
    this->colunas = tamanho;
    this->densidade = densidade;
    this->quadros = this->linhas * this->colunas;
    this->bombas = int(this->quadros * densidade);
    this->quadrosLivres = this->quadros - this->bombas;
    this->quadrosDescobertos = 0;
    this->vitoria = false;
    this->primeiroClique = true;
    this->campoMinado.assign(this->linhas, std::vector<int>());
    this->campoRevelado.assign(this->linhas, std::vector<int>());
}

CampoMinado::~CampoMinado() {
    //destrutor vazio, pois não há alocação dinâmica de memória
}

//permite acessar o tamanho do campo
int CampoMinado::getTamanho() {
    return this->tamanho;
}

void CampoMinado::gerarCampoMinado() {
    //cria um vetor unidimensional que lista os quadros livres e as bombas
    // 0 -> quadro livre || 1 -> bomba
    std::vector<int> shallowCampo;
    for (int i = 0; i<this->quadrosLivres; i++) {
        shallowCampo.push_back(0);
    }
    for (int i = 0; i<this->bombas; i++) {
        shallowCampo.push_back(1);
    }

    //a função de shuffle foi tirada dessa resposta do stackoverflow: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(shallowCampo), std::end(shallowCampo), rng);

    //campoMinado é um vetor bidimensional, que tem j elementos em cada vetor i
    this->campoMinado.assign(this->linhas, std::vector<int>());
    for (int i = 0; i<this->linhas; i++) {
        for (int j = 0; j<this->colunas; j++) {
            this->campoMinado[i].push_back(shallowCampo[i*this->colunas + j]);
        }
    }
}

void CampoMinado::contarBombasVizinhas(int linha, int coluna) {
    int contador = 0;
    //vetor bidimensional com as coordenadas dos quadros vizinhos
    std::vector<std::vector<int>> vizinhos = {
        {linha-1, coluna-1}, {linha-1, coluna}, {linha-1, coluna+1},
        {linha, coluna-1}, {linha, coluna+1},
        {linha+1, coluna-1}, {linha+1, coluna}, {linha+1, coluna+1}
    };

    //loop que checa se cada quadro vizinho é uma bomba
    for (int k=0; k<8; k++) {
        int vizinhoLinha = vizinhos[k][0];
        int vizinhoColuna = vizinhos[k][1];

        //esse if checa se o quadro existe dentro da matriz/campo minado
        if (this->linhas > vizinhoLinha && vizinhoLinha >= 0 && this->colunas > vizinhoColuna && vizinhoColuna >= 0) {
            if (this->campoMinado[vizinhoLinha][vizinhoColuna] == 1) {
                contador++;
            }
        }
    }
    
    this->campoRevelado[linha][coluna] = contador;
}

//chama contarbombasvizinhas para cada quadro do campo
void CampoMinado::contarBombas() {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            this->contarBombasVizinhas(i, j);
        }
    }
}