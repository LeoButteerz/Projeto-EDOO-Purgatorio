#include "campo_minado.hpp"
//bibliotecas para embaralhar o campo minado
#include <algorithm>
#include <random>

//definição do construtor
CampoMinado::CampoMinado(int tamanho, double densidade, Player* player) {
    this->tamanho = tamanho;
    this->linhas = tamanho;
    this->colunas = tamanho;
    this->densidade = densidade;
    this->player = player;
    
    this->campoMinado.assign(this->linhas, std::vector<int>());
    this->campoRevelado.assign(this->linhas, std::vector<int>(this->colunas, 0));
    this->campoEstado.assign(this->linhas, std::vector<int>(this->colunas, 0));

    this->quadros = this->linhas * this->colunas;
    this->bombas = int(this->quadros * densidade);
    this->quadrosLivres = this->quadros - this->bombas;
    this->quadrosDescobertos = 0;
    this->vitoria = false;
    this->primeiroClique = true;
}

CampoMinado::~CampoMinado() {
    //destrutor vazio, pois não há alocação dinâmica de memória
}

//permite acessar o tamanho do campo
int CampoMinado::getTamanho() {
    return this->tamanho;
}

int CampoMinado::getBombas() {
    return this->bombas;
}

int CampoMinado::getQuadrosDescobertos() {
    return this->quadrosDescobertos;
}

void CampoMinado::gerarCampoMinado() {
    //cria um vetor unidimensional que lista os quadros livres e as bombas
    // 0 -> quadro livre || 1 -> bomba
    std::vector<int> shallowCampo;
    for (int i = 0; i<this->quadrosLivres; i++) {
        shallowCampo.push_back(0);
    }
    for (int i = 0; i<this->bombas; i++) {
        shallowCampo.push_back(1);
    }

    //a função de shuffle foi tirada dessa resposta do stackoverflow: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(shallowCampo), std::end(shallowCampo), rng);

    //campoMinado é um vetor bidimensional, que tem j elementos em cada vetor i
    this->campoMinado.assign(this->linhas, std::vector<int>());
    for (int i = 0; i<this->linhas; i++) {
        for (int j = 0; j<this->colunas; j++) {
            this->campoMinado[i].push_back(shallowCampo[i*this->colunas + j]);
        }
    }
}

void CampoMinado::contarBombasVizinhas(int linha, int coluna) {
    int contador = 0;
    //vetor bidimensional com as coordenadas dos quadros vizinhos
    std::vector<std::vector<int>> vizinhos = {
        {linha-1, coluna-1}, {linha-1, coluna}, {linha-1, coluna+1},
        {linha, coluna-1}, {linha, coluna+1},
        {linha+1, coluna-1}, {linha+1, coluna}, {linha+1, coluna+1}
    };

    //loop que checa se cada quadro vizinho é uma bomba
    for (int k=0; k<8; k++) {
        int vizinhoLinha = vizinhos[k][0];
        int vizinhoColuna = vizinhos[k][1];

        //esse if checa se o quadro existe dentro da matriz/campo minado
        if (this->linhas > vizinhoLinha && vizinhoLinha >= 0 && this->colunas > vizinhoColuna && vizinhoColuna >= 0) {
            if (this->campoMinado[vizinhoLinha][vizinhoColuna] == 1) {
                contador++;
            }
        }
    }
    
    this->campoRevelado[linha][coluna] = contador;
}

//chama contarbombasvizinhas para cada quadro do campo
void CampoMinado::contarBombas() {
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            this->contarBombasVizinhas(i, j);
        }
    }
}

void CampoMinado::revelarQuadro(int linha, int coluna, bool quadroInicial) {
    //só revela o quadro se não tiver sido marcado com uma bandeira
    if (!(this->campoEstado[linha][coluna] == 2 && quadroInicial)) {
        
        //coordenadas dos quadros vizinhos
        std::vector<std::vector<int>> vizinhos = {
            {linha-1, coluna-1}, {linha-1, coluna}, {linha-1, coluna+1},
            {linha, coluna-1}, {linha, coluna+1},
            {linha+1, coluna-1}, {linha+1, coluna}, {linha+1, coluna+1}
        };

        //impossível errar na primeira jogada
        if (this->primeiroClique) {
            
            this->primeiroClique = false;

            //o primeiro clique foi em uma bomba
            if (this->campoMinado[linha][coluna] == 1) {
                this->campoMinado[linha][coluna] = 0;
                this->bombas--;
                this->quadrosLivres++;
            }

            this->quadrosDescobertos++;
            this->campoEstado[linha][coluna] = 1;
            this->contarBombas();
            
            //essa próxima parte faz o mesmo processo de checar os vizinhos para revelar os quadros
            for (int k=0; k<8; k++) {
                int vizinhoLinha = vizinhos[k][0];
                int vizinhoColuna = vizinhos[k][1];

                //esse if checa se o quadro existe dentro da matriz/campo minado
                if (this->linhas > vizinhoLinha && vizinhoLinha >= 0 && this->colunas > vizinhoColuna && vizinhoColuna >= 0) {
                    //apenas revela o quadro se ele não tiver sido revelado e se o quadro atual nn tiver nenhum contador de bombas
                    if (this->campoEstado[vizinhoLinha][vizinhoColuna] != 1 && this->campoRevelado[linha][coluna] == 0) {
                        this->revelarQuadro(vizinhoLinha, vizinhoColuna, false);
                    }
                }
            }
        }

        //bomba acertada
        else if (this->campoMinado[linha][coluna] == 1 && this->campoEstado[linha][coluna] != 3) {
            this->campoEstado[linha][coluna] = 3;
            this->player->receberDano(1);
            this->player->resetarMultiplicador();
            this->player->somarPontos(-30);
        }

        //revelou quadro normal
        else if (this->campoMinado[linha][coluna] != 1 && this->campoEstado[linha][coluna] != 1 && this->campoEstado[linha][coluna] != 3) {
            this->quadrosDescobertos++;
            this->campoEstado[linha][coluna] = 1;

            //essa próxima parte faz o mesmo processo de checar os vizinhos para revelar os quadros
            for (int k=0; k<8; k++) {
                int vizinhoLinha = vizinhos[k][0];
                int vizinhoColuna = vizinhos[k][1];

                //esse if checa se o quadro existe dentro da matriz/campo minado
                if (this->linhas > vizinhoLinha && vizinhoLinha >= 0 && this->colunas > vizinhoColuna && vizinhoColuna >= 0) {
                    //apenas revela o quadro se ele não tiver sido revelado e se o quadro atual nn tiver nenhum contador de bombas
                    if (this->campoEstado[vizinhoLinha][vizinhoColuna] != 1 && this->campoRevelado[linha][coluna] == 0) {
                        this->revelarQuadro(vizinhoLinha, vizinhoColuna, false);
                    }
                }
            }
        }
    }
}

void CampoMinado::marcarBandeira(int linha, int coluna) {
    //só marca a bandeira se o quadro não tiver sido revelado
    if (this->campoEstado[linha][coluna] != 1) {
        //se o quadro já tiver uma bandeira, remove a bandeira
        if (this->campoEstado[linha][coluna] == 2) {
            this->campoEstado[linha][coluna] = 0;
        }
        else if (this->campoEstado[linha][coluna] == 0) {
            this->campoEstado[linha][coluna] = 2;
        }
        this->player->usarBandeira(1);
        this->player->somarPontos(10);
    }
}

bool CampoMinado::verificarVitoria() {
    //o jogador vence se revelar todos os quadros livres
    if (this->quadrosDescobertos == this->quadrosLivres) {
        this->vitoria = true;
    }
    return this->vitoria;
}

std::ostream& operator<<(std::ostream& os, const CampoMinado& campo) {
    for (int i = 0; i < campo.linhas; i++) {
        for (int j = 0; j < campo.colunas; j++) {
            if (campo.player->getX() == i && campo.player->getY() == j) {
                os << " P ";
            }
            else if (campo.coletavelVida != nullptr && campo.coletavelVida->ta_ativo() && campo.coletavelVida->getPosicaoX() == i && campo.coletavelVida->getPosicaoY() == j) {
                os << " + ";
            }
            else if (campo.coletavelTempo != nullptr && campo.coletavelTempo->ta_ativo() && campo.coletavelTempo->getPosicaoX() == i && campo.coletavelTempo->getPosicaoY() == j) {
                os << " % ";
            }
            else if (campo.coletavelFlag != nullptr && campo.coletavelFlag->ta_ativo() && campo.coletavelFlag->getPosicaoX() == i && campo.coletavelFlag->getPosicaoY() == j) {
                os << " ! ";
            }
            else if (campo.campoEstado[i][j] == 2) {
                os << " F ";
            }
            else if (campo.campoEstado[i][j] == 3) {
                os << " X ";
            }
            else if (campo.campoEstado[i][j] == 1) {
                os << " " << campo.campoRevelado[i][j] << " ";
            }
            else {
                os << " # ";
            }

            if (j != campo.colunas - 1) {
                os << "|";
            }
        }
        os << "\n";
    }
    os << std::endl;
    return os;
}

void CampoMinado::adicionarColetavelVida(Coletaveis* coletavel) {
    this->coletavelVida = coletavel;
}

void CampoMinado::adicionarColetavelTempo(Coletaveis* coletavel) {
    this->coletavelTempo = coletavel;
}

void CampoMinado::adicionarColetavelFlag(Coletaveis* coletavel) {
    this->coletavelFlag = coletavel;
}