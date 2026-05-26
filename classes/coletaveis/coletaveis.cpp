#include "coletaveis.hpp"
#include "../player/player.hpp"
#include <iostream>

// construtor da classe pai coletaveis
Coletaveis::Coletaveis(Player* ponteiro_interno, int self_lifetime, int self_posicaoX, int self_posicaoY) {
    ponteiro = ponteiro_interno;
    lifetime = self_lifetime;
    posicaoX = self_posicaoX;
    posicaoY = self_posicaoY;

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

void Coletaveis::set_ativo(const bool valor) {
    ativo = valor;
}

//metodos das classes filhas

// construtor da classe vida
Vida::Vida(Player* ponteiro_interno, int self_lifetime, int self_posicaoX, int self_posicaoY) : Coletaveis(ponteiro_interno, self_lifetime, self_posicaoX, self_posicaoY) {}// chama o construtor da classe pai antes

void Vida::ocorrencia_efeito(const int qnt) {
    this->ponteiro->curar(qnt);
}

//construtor classe tempo
Tempo::Tempo(Player* ponteiro_interno, int self_lifetime, int self_posicaoX, int self_posicaoY) : Coletaveis(ponteiro_interno, self_lifetime, self_posicaoX, self_posicaoY) {}

void Tempo::ocorrencia_efeito(const int qnt) {
    this->ponteiro->setAcoesRestantes(qnt);
}

//construtor classe flag
Flag::Flag(Player* ponteiro_interno, int self_lifetime, int self_posicaoX, int self_posicaoY) : Coletaveis(ponteiro_interno, self_lifetime, self_posicaoX, self_posicaoY) {}

void Flag::ocorrencia_efeito(const int qnt) {
    this->ponteiro->ganharBandeira(qnt);
}