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

    for (int i = 0; i<this->linhas; i++) {
        for (int j = 0; j<this->colunas; j++) {
            this->campoMinado.push_back(std::vector<int>{shallowCampo[i*this->colunas + j]});
        }
    }
}