#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include <array>

using namespace std;
    class Interactions
    {
        private:
            bool left_click;
            bool left_press;

            bool right_click;
            bool right_press;
            
        public:
            Interactions(bool left_click, bool left_press, bool right_click, bool right_press); //constructor
            virtual ~Interactions(); //destructor


            //funcoes que serao usadas para modificar os bools relativos a interacao do mouse
            void set_left_click();
            void set_left_press();
            void reset_left_click();
            void reset_left_press();
            void set_right_click();
            void set_right_press();
            void reset_right_click();
            void reset_right_press();

            std::array<int, 2> position(array<int, 2> mPosPointer[2]);


    };



#endif
