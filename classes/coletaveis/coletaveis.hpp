#ifndef coletaveis_hpp
#define coletaveis_hpp

#include <iostream>
using namespace std;

class player; //necessario já que será necessario para comparação

class Coletaveis
{
    protected:
        double lifetime; //tempo de vida de duração no mapa do coletavel
        double timer; //temporizador interno da classe
        bool ativo; //para saber se o coletavel esta presente no mapa ainda
        player* ponteiro;
    public:
        Coletaveis(player* ponteiro_interno, double self_lifetime);//construtor
        // self para diferenciar de lifetime
        ~Coletaveis();//destrutor

        virtual void ocorrencia_efeito() =0; //defini como um metodo virtual puro
        // irá obrigatoriamente ser reescrevido nas classes filhas com o efeito respectivo

        virtual void update();//chechar se o coletavel ainda estaria no mapa
        // alterando a variavel booleana ativo

        virtual bool ta_ativo() const;// checa o valor da variavel
};

//classe filha da classe coletavel
class vida : public Coletaveis{//em relação ao coletavel de vida
    public:
        vida(player* ponteiro_interno, double self_lifetime);//construtor da mesma

        void ocorrencia_efeito() override;//metodo que sera sobrescrito em todas as classes filhas

};

//classe filha da classe coletavel
class tempo : public Coletaveis{//relacionado ao coletavel que da mais tempo
    public:
        tempo(player* ponteiro_interno, double self_lifetime);//construtor da mesma

        void ocorrencia_efeito() override;//metodo que sera sobrescrito em todas as classes filhas

};

//classe filha da classe coletavel
class flag : public Coletaveis{//coletavel flag
    public:
        flag(player* ponteiro_interno, double self_lifetime);//construtor da mesma

        void ocorrencia_efeito() override;//metodo que sera sobrescrito em todas as classes filhas

};
#endif