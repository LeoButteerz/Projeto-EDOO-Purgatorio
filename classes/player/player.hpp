#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
    private:
        int x;
        int y;

        double velocidade_x;
        double velocidade_y;
        double velocidade_maxima;
        double aceleracao;
        double desaceleracao;
        double desaceleracao_critica;

        int vidas;
        int max_vidas;
        int bandeiras;
        int max_bandeiras;
        int pontos;
        int multiplicador;

        int direcao;
        bool cavando;
        bool machucado;

        double limitarVelocidade(double velocidade) const;
        double reduzirVelocidade(double velocidade) const;

    public:
        Player();
        Player(int vidas_iniciais, int bandeiras_iniciais,
               double velocidade_max, double acc,
               double dampen, double cdamp);
        ~Player();

        // movimenta o player usando as quatro direcoes basicas
        void mover(bool esquerda, bool direita, bool cima, bool baixo);

        // posicao do player na tela ou no tabuleiro
        void setPosicao(int novo_x, int novo_y);
        int getX() const;
        int getY() const;

        // velocidade atual do player
        void setVelocidade(double nova_velocidade_x, double nova_velocidade_y);
        double getVelocidade_x() const;
        double getVelocidade_y() const;

        // direcao usada para animacao ou para saber para onde ele esta olhando
        void setDirecao(int nova_direcao);
        int getDirecao() const;

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

        // pontuacao do jogador
        void somarPontos(int valor);
        void aumentarMultiplicador();
        void resetarMultiplicador();
        int getPontos() const;
        int getMultiplicador() const;

        // estados simples usados durante o jogo
        void setCavando(bool valor);
        bool estaCavando() const;
        void acordar();
        bool estaMachucado() const;
};

#endif
