#include "Invador.h"
#include <ncurses.h>


Invador::Invador(int width, int height, int x, int y, int speedY)
{
    this->height = height;
    this->width = width;
    this->x = x;
    this->y = y;
    this->health = 1;
    this->angleX = 0;
    this->outOfGame = false;
    this->angleY = speedY;
}

Invador::~Invador()
{
}

void Invador::paintInvador(){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mvprintw(this->y+i-1,this-> x+j-1,"@");
        }
        
    }
    
}

void Invador::step(){
            // int tmpY = y + this->angleY;
            // int tmpX = x + this->angleX;
            // if (! (tmpX < 0 || tmpX > scrX)) 
            //     x += this->angleX;
            // if (! (tmpY < 0 || tmpY > scrY))              
            //     y += this->angleY;
        this->y = this->y+ this->angleY;
}