#include "interaction.hpp"
#include <string>
#include <math.h>

//definição construtor da classe Interactions
Interactions::Interactions(bool left_click, bool left_press, bool right_click, bool right_press)
{
    // bools de interação de mouse
    left_click = left_click;
    left_press = left_press;
    right_click = right_click;
    right_press = right_press;

    // mpubpos é pointer de mpos, já que não podemos modificar mpos diretamente por ela ser private
    mpubpos = &mpos;

}
//destrutor da classe Interactions
Interactions::~Interactions()
{

}

//funções para modificar os bools de Interactions, relativos às interações do mouse
    //left
void inline Interactions::set_left_click() // click esquerdo true
{left_click = true;}

void inline Interactions::set_left_press() // press esquerdo true
{left_press = true;}

void inline Interactions::reset_left_click() // reseta o valor de left_click pro default (false)
{left_click = false;}

void inline Interactions::reset_left_press() // reseta o valor de left_press pro default (false)
{left_press = false;}

    //right
void inline Interactions::set_right_click()
{right_click = true;}

void inline Interactions::set_right_press()
{right_press = true;}

void inline Interactions::reset_right_click()
{right_click = false;}

void inline Interactions::reset_right_press()
{right_press = false;}


//função placeholder, na prática seria responsável por pegar as coordenadas do mouse
void get_mouse_pos()
{
    *Interactions::mpubpos = {0,0};
}



void const position(std::vector<int> mousePointer)  // mousePointer seria vector de tamanho 2 que contem a posicao do mouse
{   
    get_mouse_pos(); //atualiza posicao do mouse

    try{
        if(floor(mousePointer[0]) == mousePointer[0] && floor(mousePointer[1]) == mousePointer[1]){} // confere se são ints
        else
        { // se não forem ints, joga erro de posição inválida
            throw("INVALID_POSITION");
        }
    }
    

    catch(std::string error_msg) //fallback; caso por algum motivo a posição não esteja no formato válido, defaulta pra {0,0}
    {
        if(error_msg == "INVALID_POSITION"){ // confere se foi o erro de valores inválidos pra mousePointer

            *Interactions::mpubpos = {0,0}; // muda o valor de mPos para {0,0}
        }
        
    }
}

