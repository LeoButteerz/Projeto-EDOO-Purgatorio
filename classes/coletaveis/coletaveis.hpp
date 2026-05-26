#ifndef COLETAVEIS_HPP
#define COLETAVEIS_HPP
#include <iostream>

class Player; //necessario já que será necessario para comparação

class Coletaveis
{
    protected:
        double lifetime; //tempo de vida de duração no mapa do coletavel
        double timer; //temporizador interno da classe
        bool ativo; //para saber se o coletavel esta presente no mapa ainda
        Player* ponteiro;
    public:
        Coletaveis(Player* ponteiro_interno, double self_lifetime);//construtor
        // self para diferenciar de lifetime
        ~Coletaveis();//destrutor

        virtual void ocorrencia_efeito(const int qnt) =0; //defini como um metodo virtual puro
        // irá obrigatoriamente ser reescrevido nas classes filhas com o efeito respectivo

        virtual void update();//chechar se o coletavel ainda estaria no mapa
        // alterando a variavel booleana ativo

        virtual bool ta_ativo() const;// checa o valor da variavel
};

//classe filha da classe coletavel
class Vida : public Coletaveis{//em relação ao coletavel de vida
    public:
        Vida(Player* ponteiro_interno, double self_lifetime);//construtor da mesma

        void ocorrencia_efeito(const int qnt) override;//metodo que sera sobrescrito em todas as classes filhas

};

//classe filha da classe coletavel
class Tempo : public Coletaveis{//relacionado ao coletavel que da mais tempo
    public:
        Tempo(Player* ponteiro_interno, double self_lifetime);//construtor da mesma

        void ocorrencia_efeito(const int qnt) override;//metodo que sera sobrescrito em todas as classes filhas

};

//classe filha da classe coletavel
class Flag : public Coletaveis{//coletavel flag
    public:
        Flag(Player* ponteiro_interno, double self_lifetime);//construtor da mesma

        void ocorrencia_efeito(const int qnt) override;//metodo que sera sobrescrito em todas as classes filhas

};
#endif