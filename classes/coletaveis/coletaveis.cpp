#include "coletaveis.hpp"
#include "player.hpp"
#include <iostream>
using namespace std;

// construtor da classe pai coletaveis
coletaveis::coletaveis(player* ponteiro_interno, float self_lifetime) {
    ponteiro = ponteiro_interno;
    lifetime = self_lifetime;

    timer = self_lifetime;
    // pensei em multiplicar em 60 por causa do fps
    ativo = true;
}

//destrutor da classe
coletaveis::~coletaveis() {
}

// logica do metodo do update se ainda esta ativo
void coletaveis::update() {
    if (!ativo) return; //termina o codigo

    if (timer > 0) {
        timer--; //diminui o tempo em 1 cada vez acessado
    } else {
        ativo = false; //o item expirou/desapareceu
    }

// falta como fazer a questão da posição do player pra ver se o player ta tocando ou n 
}

bool coletaveis::ta_ativo() const {
    return ativo;
}

//metodos das classes filhas

// construtor da classe vida
vida::vida(player* ponteiro_interno, float self_lifetime) : coletaveis(ponteiro_interno, self_lifetime) {}// chama o construtor da classe pai antes

void vida::ocorrencia_efeito() {
//logica pra adicionar vida em algum lugar
}

//construtor classe tempo
tempo::tempo(player* ponteiro_interno, float self_lifetime) : coletaveis(ponteiro_interno, self_lifetime) {}

void tempo::ocorrencia_efeito() {
    //logica de adicionar mais tempo
}

//construtor classe flag
flag::flag(player* ponteiro_interno, float self_lifetime) : coletaveis(ponteiro_interno, self_lifetime) {}

void flag::ocorrencia_efeito() {
    //logica adicionar numero das flags
}