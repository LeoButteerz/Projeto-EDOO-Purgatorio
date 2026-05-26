#include "player.hpp"

// construtor padrao, deixa o player em um estado inicial jogavel
Player::Player(){
    x = 0;
    y = 0;

    max_vidas = 7;
    vidas = max_vidas;
    max_bandeiras = 10;
    bandeiras = max_bandeiras;
    pontos = 0;
    multiplicador = 1;
}

// construtor com parametros para definir vida e bandeiras iniciais
Player::Player(int vidas_iniciais, int bandeiras_iniciais){
    x = 0;
    y = 0;

    max_vidas = vidas_iniciais;
    vidas = vidas_iniciais;
    max_bandeiras = bandeiras_iniciais;
    bandeiras = bandeiras_iniciais;
    pontos = 0;
    multiplicador = 1;
}

// destrutor vazio, pois a classe nao usa memoria dinamica
Player::~Player(){

}

// muda a posicao atual do player
void Player::setPosicao(int novo_x, int novo_y){
    x = novo_x;
    y = novo_y;
}

// retorna a posicao horizontal do player
int Player::getX() const{
    return x;
}

// retorna a posicao vertical do player
int Player::getY() const{
    return y;
}

// diminui a vida do player quando ele sofre dano
void Player::receberDano(int valor){
    vidas -= valor;

    // evita que a vida fique negativa
    if (vidas < 0) {
        vidas = 0;
    }
}

// aumenta a vida do player sem passar do limite
void Player::curar(int valor){
    vidas += valor;

    // nao deixa a cura passar do maximo de vidas
    if (vidas > max_vidas) {
        vidas = max_vidas;
    }
}

// verifica se o player ainda tem vida
bool Player::estaVivo() const{
    return vidas > 0;
}

// retorna a quantidade atual de vidas
int Player::getVidas() const{
    return vidas;
}

// retorna o maximo de vidas possivel
int Player::getMaxVidas() const{
    return max_vidas;
}

// aumenta a quantidade de bandeiras disponiveis
void Player::ganharBandeira(int valor){
    bandeiras += valor;

    // o coletavel nao pode passar do limite de bandeiras
    if (bandeiras > max_bandeiras) {
        bandeiras = max_bandeiras;
    }
}

// diminui a quantidade de bandeiras usadas
void Player::usarBandeira(int valor){
    bandeiras -= valor;

    // evita quantidade negativa de bandeiras
    if (bandeiras < 0) {
        bandeiras = 0;
    }
}

// retorna a quantidade atual de bandeiras
int Player::getBandeiras() const{
    return bandeiras;
}

// retorna o maximo de bandeiras possivel
int Player::getMaxBandeiras() const{
    return max_bandeiras;
}

// soma pontos considerando o multiplicador atual
void Player::somarPontos(int valor){
    // no jogo original a pontuacao usa o multiplicador atual
    pontos += valor * multiplicador;
}

// aumenta o multiplicador de pontos
void Player::aumentarMultiplicador(){
    multiplicador++;
}

// volta o multiplicador para o valor inicial
void Player::resetarMultiplicador(){
    multiplicador = 1;
}

// retorna a pontuacao atual
int Player::getPontos() const{
    return pontos;
}

// retorna o multiplicador atual
int Player::getMultiplicador() const{
    return multiplicador;
}
