#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>

class Coletaveis; //necessario para a classe coletaveis

class Player
{
    private:
        int x;
        int y;

        int vidas;
        int max_vidas;
        int bandeiras;
        int max_bandeiras;
        int pontos;
        int multiplicador;
        int acoes_restantes;

    public:
        Player();
        Player(int vidas_iniciais, int bandeiras_iniciais, int acoes_restantes_iniciais);
        ~Player();

        // posicao do player na tela ou no tabuleiro
        void setPosicao(int novo_x, int novo_y);
        int getX() const;
        int getY() const;

        // controle de vida
        void receberDano(int valor);
        void curar(int valor);
        bool estaVivo() const;
        int getVidas() const;
        int getMaxVidas() const;

        // controle das bandeiras disponiveis
        void ganharBandeira(int valor);
        void usarBandeira(int valor);
        int getBandeiras() const;
        int getMaxBandeiras() const;

        // controle das ações restantes
        void setAcoesRestantes(int valor);
        int getAcoesRestantes() const;
        void usarAcao();

        // pontuacao do jogador
        void somarPontos(int valor);
        void aumentarMultiplicador();
        void resetarMultiplicador();
        int getPontos() const;
        int getMultiplicador() const;

        friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif
