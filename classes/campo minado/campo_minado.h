#ifndef CAMPO_MINADO_H
#define CAMPO_MINADO_H
#include <iostream>
#include <vector> //usando para administrar o campo minado 2d como um vetor de vetores

class CampoMinado {
    private:
        //mesmos atributos que estão no projeto original
        int tamanho;
        int linhas;
        int colunas;
        double densidade;
        
        std::vector<std::vector<int>> campoMinado;
        std::vector<std::vector<int>> campoRevelado;
        std::vector<std::vector<int>> campoEstado; // 0 -> não revelado, 1 -> revelado, 2 -> marcado, 3 -> bomba acertada
        
        int quadros;
        int bombas;
        int quadrosLivres;
        int quadrosDescobertos;
        bool vitoria;
        bool primeiroClique;

    public:
        //construtor e destrutor
        CampoMinado(int tamanho, double densidade);
        virtual ~CampoMinado();

        //funções para gerar e administrar o campo minado
        void gerarCampoMinado();
        //void imprimirCampoMinado();
        void contarBombasVizinhas(int linha, int coluna);
        void contarBombas();

        void revelarQuadro(int linha, int coluna, bool quadroInicial=true);
        void marcarBandeira(int linha, int coluna);
        bool verificarVitoria();
        
        int getTamanho();
        int getBombas();
        int getQuadrosDescobertos();

        friend std::ostream& operator<<(std::ostream& os, const CampoMinado& campo);
};

#endif