#include <iostream>
#include "classes\campo minado\campo_minado.cpp"
#include <vector>
using namespace std;

// main para o projeto :)
int main(){
    
    CampoMinado* campo = new CampoMinado(10, 0.2);
    campo->gerarCampoMinado();
    std::cout << "campo gerado!" << std::endl;
    std::cout << *campo << std::endl;
    campo->revelarQuadro(0, 0);
    std::cout << *campo << std::endl;
    delete campo;

    return 0;
}