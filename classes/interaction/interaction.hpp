#ifndef _INTERACTION_H_ // evita definir novamente
#define _INTERACTION_H_

#include <vector> // para a posição do mouse

using namespace std;
    class Interactions // classe que abriga dados e métodos necessários para que ocorram interações após utilizar o mouse
    {
        private:
            bool left_click;
            bool left_press;

            bool right_click;
            bool right_press;

            vector<int> static mpos; // guarda a posição do mouse. como precisaríamos disso a todo momento no jogo completo, esse vetor é static

            void const position(); // função que obtém a posição do mouse atual

        public:
            Interactions(bool left_click, bool left_press, bool right_click, bool right_press); // constructor de Interactions
            virtual ~Interactions(); // destructor de Interactions

            static vector<int>* mpubpos; // inicializado em 'interaction.hpp', aponta para mpos, que é private

            // funções que serão usadas para modificar os bools relativos à interação do mouse, seguindo a lógica do jogo original
            void set_left_click();
            void set_left_press();      //lado esquerdo
            void reset_left_click();
            void reset_left_press();

            void set_right_click();
            void set_right_press();     //lado direito
            void reset_right_click();
            void reset_right_press();


            
    };



#endif
