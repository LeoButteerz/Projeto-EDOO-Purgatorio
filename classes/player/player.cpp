#include "player.hpp"
#include <cmath>

// construtor padrao, deixa o player em um estado inicial jogavel
Player::Player()
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
Player::Player(int vidas_iniciais, int bandeiras_iniciais,
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

Player::~Player()
{
}

// impede que a velocidade passe do limite definido para o player
double Player::limitarVelocidade(double velocidade) const
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
double Player::reduzirVelocidade(double velocidade) const
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

void Player::mover(bool esquerda, bool direita, bool cima, bool baixo)
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
        velocidade_x = reduzirVelocidade(velocidade_x);
    }

    // depois calcula o movimento vertical
    if (cima) {
        velocidade_y -= acc_atual;
    }

    if (baixo) {
        velocidade_y += acc_atual;
    }

    if (!cima && !baixo) {
        velocidade_y = reduzirVelocidade(velocidade_y);
    }

    velocidade_x = limitarVelocidade(velocidade_x);
    velocidade_y = limitarVelocidade(velocidade_y);

    // soma a velocidade na posicao atual do player
    x += int(velocidade_x);
    y += int(velocidade_y);
}

void Player::setPosicao(int novo_x, int novo_y)
{
    x = novo_x;
    y = novo_y;
}

int Player::getX() const
{
    return x;
}

int Player::getY() const
{
    return y;
}

void Player::setVelocidade(double nova_velocidade_x, double nova_velocidade_y)
{
    velocidade_x = nova_velocidade_x;
    velocidade_y = nova_velocidade_y;
}

double Player::getVelocidade_x() const
{
    return velocidade_x;
}

double Player::getVelocidade_y() const
{
    return velocidade_y;
}

void Player::setDirecao(int nova_direcao)
{
    direcao = nova_direcao;
}

int Player::getDirecao() const
{
    return direcao;
}

void Player::receberDano(int valor)
{
    // ao receber dano, ele entra no estado de machucado
    machucado = true;
    vidas -= valor;

    if (vidas < 0) {
        vidas = 0;
    }
}

void Player::curar(int valor)
{
    vidas += valor;

    // nao deixa a cura passar do maximo de vidas
    if (vidas > max_vidas) {
        vidas = max_vidas;
    }
}

bool Player::estaVivo() const
{
    return vidas > 0;
}

int Player::getVidas() const
{
    return vidas;
}

int Player::getMaxVidas() const
{
    return max_vidas;
}

void Player::ganharBandeira(int valor)
{
    bandeiras += valor;

    // o coletavel nao pode passar do limite de bandeiras
    if (bandeiras > max_bandeiras) {
        bandeiras = max_bandeiras;
    }
}

void Player::usarBandeira(int valor)
{
    bandeiras -= valor;

    // evita quantidade negativa de bandeiras
    if (bandeiras < 0) {
        bandeiras = 0;
    }
}

int Player::getBandeiras() const
{
    return bandeiras;
}

int Player::getMaxBandeiras() const
{
    return max_bandeiras;
}

void Player::somarPontos(int valor)
{
    // no jogo original a pontuacao usa o multiplicador atual
    pontos += valor * multiplicador;
}

void Player::aumentarMultiplicador()
{
    multiplicador++;
}

void Player::resetarMultiplicador()
{
    multiplicador = 1;
}

int Player::getPontos() const
{
    return pontos;
}

int Player::getMultiplicador() const
{
    return multiplicador;
}

void Player::setCavando(bool valor)
{
    cavando = valor;
}

bool Player::estaCavando() const
{
    return cavando;
}

void Player::acordar()
{
    // remove o estado de dano depois que o tempo de atordoamento passa
    machucado = false;
}

bool Player::estaMachucado() const
{
    return machucado;
}
