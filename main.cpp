#include <iostream>
#include "classes\campo minado\campo_minado.cpp"
#include "classes\player\player.cpp"
#include "classes\coletaveis\coletaveis.cpp"
//#include "classes\interaction\interaction.cpp"
#include <vector>
using namespace std;

// main para o projeto :)
int main(){
    
    cout << "Bem vindo ao Purgatorio!" << endl;
    cout << "Selecione o tamanho do campo minado (deve ser um numero inteiro positivo): ";
    int tamanho;
    cin >> tamanho;
    cout << "Selecione a densidade de bombas (deve ser um numero entre 0 e 1): ";
    double densidade;
    cin >> densidade;

    CampoMinado* campo = new CampoMinado(tamanho, densidade);
    Player* player = new Player();
    campo->gerarCampoMinado();
    cout << *player << endl;
    cout << *campo << endl;

    while (!campo->verificarVitoria() && player->estaVivo() && player->getAcoesRestantes() > 0) {
        int linha, coluna;
        cin >> linha >> coluna;
        player->usarAcao();

        campo->revelarQuadro(linha, coluna);
        cout << *player << endl;
        cout << *campo << endl;

        if (!player->estaVivo()) {
            cout << "Game Over! Voce perdeu todas as suas vidas." << endl;
            break;
        }
        if (player->getAcoesRestantes() <= 0) {
            cout << "Game Over! Voce não tem mais acoes restantes." << endl;
            break;
        }

        break;
    }

    delete campo;
    delete player;

    return 0;
}