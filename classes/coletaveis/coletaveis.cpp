#include "coletaveis.hpp"
#include "player.hpp"
#include <iostream>
using namespace std;

// construtor da classe pai coletaveis
Coletaveis::Coletaveis(player* ponteiro_interno, double self_lifetime) {
    ponteiro = ponteiro_interno;
    lifetime = self_lifetime;

    timer = self_lifetime;
    // pensei em multiplicar em 60 por causa do fps
    ativo = true;
}

//destrutor da classe
Coletaveis::~Coletaveis() {
}

// logica do metodo do update se ainda esta ativo
void Coletaveis::update() {
    if (!ativo) return; //termina o codigo

    if (timer > 0) {
        timer--; //diminui o tempo em 1 cada vez acessado
    } else {
        ativo = false; //o item expirou/desapareceu
    }

// falta como fazer a questão da posição do player pra ver se o player ta tocando ou n 
}

bool Coletaveis::ta_ativo() const {
    return ativo;
}

//metodos das classes filhas

// construtor da classe vida
Vida::Vida(player* ponteiro_interno, double self_lifetime) : Coletaveis(ponteiro_interno, self_lifetime) {}// chama o construtor da classe pai antes

void Vida::ocorrencia_efeito() {
    //logica pra adicionar vida em algum lugar
}

//construtor classe tempo
Tempo::Tempo(player* ponteiro_interno, double self_lifetime) : Coletaveis(ponteiro_interno, self_lifetime) {}

void Tempo::ocorrencia_efeito() {
    //logica de adicionar mais tempo
}

//construtor classe flag
Flag::Flag(player* ponteiro_interno, double self_lifetime) : Coletaveis(ponteiro_interno, self_lifetime) {}

void Flag::ocorrencia_efeito() {
    //logica adicionar numero das flags
}