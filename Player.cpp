#include "Player.h"
#include <ncurses.h>

void Player::step(int shiftX, int shiftY)  
{   
            int tmpY = y + shiftY;
            int tmpX = x + shiftX;
            if (! (tmpX < -1 || tmpX +width-1 > scrX)) 
                x += shiftX;
            if (! (tmpY < 0 || tmpY > scrY))              
                y += shiftY;
}

Player::Player(int width, int height, int x, int y)
{
    this->scrX = getmaxx(stdscr);
    this->scrY = getmaxy(stdscr);
    this->height = height;
    this->width = width;
    this->y = y;
    this->x = x;
}

Ball* Player::shootBall(){
    
    Ball* ball = new Ball(this->x +width/2, this->y - 2);

    return ball;
}

void Player::paintPlayer(){
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            mvprintw(this->y +i,this->x +j, "&");
        }
        
    }
    
}

