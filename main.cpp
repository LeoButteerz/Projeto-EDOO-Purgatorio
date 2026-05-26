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

    Player* player = new Player();
    CampoMinado* campo = new CampoMinado(tamanho, densidade, player);
    campo->gerarCampoMinado();
    cout << *player << endl;
    cout << *campo << endl;

    while (!campo->verificarVitoria() && player->estaVivo() && player->getAcoesRestantes() > 0) {
        cout << "Digite sua acao: revelar (r), marcar bandeira (f) ou mover (m): ";
        char acao;
        cin >> acao;
        player->usarAcao();
        int linha, coluna;

        if (acao == 'f') {
            cout << "Digite a linha e a coluna para marcar/desmarcar a bandeira (linha coluna): ";
            cin >> linha >> coluna;
            
            campo->marcarBandeira(linha, coluna);
            cout << *player << endl;
            cout << *campo << endl;
        }
        else if (acao == 'm') {
            cout << "Digite a linha e a coluna para mover o player (linha coluna): ";
            cin >> linha >> coluna;

            player->setPosicao(linha, coluna);
        }
        else if (acao == 'r') {
            cout << "Digite a linha e a coluna para revelar (linha coluna): ";
            cin >> linha >> coluna;
            
            campo->revelarQuadro(linha, coluna);
            cout << *player << endl;
            cout << *campo << endl;
        }
        else {
            cout << "Acao invalida. Tente novamente." << endl;
        }

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
    }

    if (campo->verificarVitoria()) {
        cout << "Parabens! Voce venceu o jogo!" << endl;
    }

    delete campo;
    delete player;

    return 0;
}