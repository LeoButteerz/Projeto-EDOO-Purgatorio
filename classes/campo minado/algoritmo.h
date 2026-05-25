#ifndef ALGORITMO_H
#define ALGORITMO_H
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
        void imprimirCampoMinado();
        void contarBombasVizinhas(int linha, int coluna);
        void contarBombas();

        void revelarQuadro(int linha, int coluna, bool quadroInicial=true);
        void revelarQuadrosVizinhos(int linha, int coluna);
        bool verificarVitoria();
        int getTamanho();
};

#endif // ALGORITMO_H