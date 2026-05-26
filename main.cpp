#include <iostream>
#include "classes\campo minado\campo_minado.cpp"
#include "classes\player\player.cpp"
#include "classes\coletaveis\coletaveis.cpp"
//#include "classes\interaction\interaction.cpp"
#include <vector>
using namespace std;

// main para o projeto :)
int main(){
    
    bool simulacao = true; //variavel para controlar o jogo
    int tamanho;
    double densidade;
    //introdução do jogo
    cout << "Bem vindo ao Purgatorio!" << endl;
    
    if (simulacao) {
        cout << "Esta é uma simulação fixa do jogo, com um board de 10x10 e densidade de 0.3."
            << "/n Para alterar os parametros, basta setar a variavel simulacao para false." << endl;

        tamanho = 10;
        densidade = 0.3;
    }
    else {
        cout << "Selecione o tamanho do campo minado (deve ser um numero inteiro positivo): ";
        cin >> tamanho;
        cout << "Selecione a densidade de bombas (deve ser um numero entre 0 e 1): ";
        cin >> densidade;
    }
    

    //gera os objetos que serão utilizados
    Player* player = new Player();
    CampoMinado* campo = new CampoMinado(tamanho, densidade, player);
    Coletaveis* coletavelVida = new Vida(player, 15, 9, 1);
    campo->adicionarColetavelVida(coletavelVida);
    Coletaveis* coletavelTempo = new Tempo(player, 10, 2, 5);
    campo->adicionarColetavelTempo(coletavelTempo);
    Coletaveis* coletavelFlag = new Flag(player, 5, 7, 6);
    campo->adicionarColetavelFlag(coletavelFlag);

    campo->gerarCampoMinado();
    cout << *player << endl;
    cout << *campo << endl;

    //loop de jogo
    while (!campo->verificarVitoria() && player->estaVivo() && player->getAcoesRestantes() > 0) {

        cout << "Digite sua acao: revelar (r), marcar bandeira (f) ou mover (m): ";
        char acao;
        cin >> acao;
        player->usarAcao();
        int linha, coluna;

        //faz ações diferentes dependendo da escolha do jogador
        if (acao == 'f') {
            cout << "Digite a linha e a coluna para marcar/desmarcar a bandeira (linha coluna): ";
            cin >> linha >> coluna;
            
            campo->marcarBandeira(linha, coluna);
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
        }
        else {
            cout << "Acao invalida. Tente novamente." << endl;
        }

        //checagem com os coletáveis (para o jogador coletar)
        if (coletavelVida->ta_ativo()){
            if (player->getX() == coletavelVida->getPosicaoX() && player->getY() == coletavelVida->getPosicaoY()) {
                coletavelVida->ocorrencia_efeito(1);
                cout << "Voce coletou um coracao! +1 vida." << endl;
                coletavelVida->set_ativo(false);
            }
            else {
                coletavelVida->update();
            }
        }
        if (coletavelTempo->ta_ativo()){
            if (player->getX() == coletavelTempo->getPosicaoX() && player->getY() == coletavelTempo->getPosicaoY()) {
                coletavelTempo->ocorrencia_efeito(3);
                cout << "Voce coletou um relogio! +3 acoes restantes." << endl;
                coletavelTempo->set_ativo(false);
            }
            else {
                coletavelTempo->update();
            }
        }
        if (coletavelFlag->ta_ativo()){
            if (player->getX() == coletavelFlag->getPosicaoX() && player->getY() == coletavelFlag->getPosicaoY()) {
                coletavelFlag->ocorrencia_efeito(1);
                cout << "Voce coletou uma bandeira! +1 bandeira." << endl;
                coletavelFlag->set_ativo(false);
            }
            else {
                coletavelFlag->update();
            }
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
    delete coletavelVida;
    delete coletavelTempo;
    delete coletavelFlag;

    return 0;
}