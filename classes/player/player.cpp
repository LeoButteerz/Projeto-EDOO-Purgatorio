#include "player.hpp"

#include <cmath>

// construtor padrao, deixa o player em um estado inicial jogavel
player::player()
{
    x = 0;
    y = 0;

    velocidade_x = 0;
    velocidade_y = 0;
    velocidade_maxima = 5;
    aceleracao = 1;
    desaceleracao = 1;
    desaceleracao_critica = 0.5;

    max_vidas = 7;
    vidas = max_vidas;
    max_bandeiras = 10;
    bandeiras = max_bandeiras;
    pontos = 0;
    multiplicador = 1;

    direcao = 0;
    cavando = false;
    machucado = false;
}

// construtor com parametros, usado caso o jogo queira definir valores diferentes
player::player(int vidas_iniciais, int bandeiras_iniciais,
               double velocidade_max, double acc,
               double dampen, double cdamp)
{
    x = 0;
    y = 0;

    velocidade_x = 0;
    velocidade_y = 0;
    velocidade_maxima = velocidade_max;
    aceleracao = acc;
    desaceleracao = dampen;
    desaceleracao_critica = cdamp;

    max_vidas = vidas_iniciais;
    vidas = vidas_iniciais;
    max_bandeiras = bandeiras_iniciais;
    bandeiras = bandeiras_iniciais;
    pontos = 0;
    multiplicador = 1;

    direcao = 0;
    cavando = false;
    machucado = false;
}

player::~player()
{
}

// impede que a velocidade passe do limite definido para o player
double player::limitar_velocidade(double velocidade) const
{
    if (velocidade > velocidade_maxima) {
        return velocidade_maxima;
    }

    if (velocidade < -velocidade_maxima) {
        return -velocidade_maxima;
    }

    return velocidade;
}

// diminui a velocidade aos poucos quando nao existe input de movimento
double player::reduzir_velocidade(double velocidade) const
{
    if (std::abs(velocidade) <= desaceleracao_critica) {
        return 0;
    }

    if (velocidade > 0) {
        velocidade -= desaceleracao;
    } else {
        velocidade += desaceleracao;
    }

    return velocidade;
}

void player::mover(bool esquerda, bool direita, bool cima, bool baixo)
{
    double acc_atual = aceleracao;

    // quando toma dano, o player fica parado por um tempo
    if (machucado) {
        acc_atual = 0;
    }

    // primeiro calcula o movimento horizontal
    if (esquerda) {
        velocidade_x -= acc_atual;
    }

    if (direita) {
        velocidade_x += acc_atual;
    }

    if (!esquerda && !direita) {
        velocidade_x = reduzir_velocidade(velocidade_x);
    }

    // depois calcula o movimento vertical
    if (cima) {
        velocidade_y -= acc_atual;
    }

    if (baixo) {
        velocidade_y += acc_atual;
    }

    if (!cima && !baixo) {
        velocidade_y = reduzir_velocidade(velocidade_y);
    }

    velocidade_x = limitar_velocidade(velocidade_x);
    velocidade_y = limitar_velocidade(velocidade_y);

    // soma a velocidade na posicao atual do player
    x += int(velocidade_x);
    y += int(velocidade_y);
}

void player::set_posicao(int novo_x, int novo_y)
{
    x = novo_x;
    y = novo_y;
}

int player::get_x() const
{
    return x;
}

int player::get_y() const
{
    return y;
}

void player::set_velocidade(double nova_velocidade_x, double nova_velocidade_y)
{
    velocidade_x = nova_velocidade_x;
    velocidade_y = nova_velocidade_y;
}

double player::get_velocidade_x() const
{
    return velocidade_x;
}

double player::get_velocidade_y() const
{
    return velocidade_y;
}

void player::set_direcao(int nova_direcao)
{
    direcao = nova_direcao;
}

int player::get_direcao() const
{
    return direcao;
}

void player::receber_dano(int valor)
{
    // ao receber dano, ele entra no estado de machucado
    machucado = true;
    vidas -= valor;

    if (vidas < 0) {
        vidas = 0;
    }
}

void player::curar(int valor)
{
    vidas += valor;

    // nao deixa a cura passar do maximo de vidas
    if (vidas > max_vidas) {
        vidas = max_vidas;
    }
}

bool player::esta_vivo() const
{
    return vidas > 0;
}

int player::get_vidas() const
{
    return vidas;
}

int player::get_max_vidas() const
{
    return max_vidas;
}

void player::ganhar_bandeira(int valor)
{
    bandeiras += valor;

    // o coletavel nao pode passar do limite de bandeiras
    if (bandeiras > max_bandeiras) {
        bandeiras = max_bandeiras;
    }
}

void player::usar_bandeira(int valor)
{
    bandeiras -= valor;

    // evita quantidade negativa de bandeiras
    if (bandeiras < 0) {
        bandeiras = 0;
    }
}

int player::get_bandeiras() const
{
    return bandeiras;
}

int player::get_max_bandeiras() const
{
    return max_bandeiras;
}

void player::somar_pontos(int valor)
{
    // no jogo original a pontuacao usa o multiplicador atual
    pontos += valor * multiplicador;
}

void player::aumentar_multiplicador()
{
    multiplicador++;
}

void player::resetar_multiplicador()
{
    multiplicador = 1;
}

int player::get_pontos() const
{
    return pontos;
}

int player::get_multiplicador() const
{
    return multiplicador;
}

void player::set_cavando(bool valor)
{
    cavando = valor;
}

bool player::esta_cavando() const
{
    return cavando;
}

void player::acordar()
{
    // remove o estado de dano depois que o tempo de atordoamento passa
    machucado = false;
}

bool player::esta_machucado() const
{
    return machucado;
}
