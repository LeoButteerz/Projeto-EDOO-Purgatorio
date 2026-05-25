#ifndef PLAYER_HPP
#define PLAYER_HPP

class player
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

        double limitar_velocidade(double velocidade) const;
        double reduzir_velocidade(double velocidade) const;

    public:
        player();
        player(int vidas_iniciais, int bandeiras_iniciais,
               double velocidade_max, double acc,
               double dampen, double cdamp);
        ~player();

        // movimenta o player usando as quatro direcoes basicas
        void mover(bool esquerda, bool direita, bool cima, bool baixo);

        // posicao do player na tela ou no tabuleiro
        void set_posicao(int novo_x, int novo_y);
        int get_x() const;
        int get_y() const;

        // velocidade atual do player
        void set_velocidade(double nova_velocidade_x, double nova_velocidade_y);
        double get_velocidade_x() const;
        double get_velocidade_y() const;

        // direcao usada para animacao ou para saber para onde ele esta olhando
        void set_direcao(int nova_direcao);
        int get_direcao() const;

        // controle de vida
        void receber_dano(int valor);
        void curar(int valor);
        bool esta_vivo() const;
        int get_vidas() const;
        int get_max_vidas() const;

        // controle das bandeiras disponiveis
        void ganhar_bandeira(int valor);
        void usar_bandeira(int valor);
        int get_bandeiras() const;
        int get_max_bandeiras() const;

        // pontuacao do jogador
        void somar_pontos(int valor);
        void aumentar_multiplicador();
        void resetar_multiplicador();
        int get_pontos() const;
        int get_multiplicador() const;

        // estados simples usados durante o jogo
        void set_cavando(bool valor);
        bool esta_cavando() const;
        void acordar();
        bool esta_machucado() const;
};

#endif
