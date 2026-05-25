#include "interaction.hpp"
// #include <iostream>

//definicao construtor da classe Interactions
Interactions::Interactions(bool left_click, bool left_press, bool right_click, bool right_press)
{
    left_click = left_click;
    left_press = left_press;
    right_click = right_click;
    right_press = right_press;
}
//destrutor da classe Interactions
Interactions::~Interactions()
{

}

//funcoes para modificar os bools de Interactions, relativos as interacoes do mouse
    //left
void Interactions::set_left_click() 
{left_click = true;}

void Interactions::set_left_press()
{left_press = true;}

void Interactions::reset_left_click()
{left_click = false;}

void Interactions::reset_left_press()
{left_press = false;}

    //right
void Interactions::set_right_click()
{right_click = true;}

void Interactions::set_right_press()
{right_press = true;}

void Interactions::reset_right_click()
{right_click = false;}

void Interactions::reset_right_press()
{right_press = false;}



std::array<int, 2> position(array<int, 2> mousePointer[2])  // mPosPointer seria a array de tamanho 2 que contem a posicao do mouse
{
    return mousePointer[2];
}





void dig() //funcao que cava um ladrilho
{

}
