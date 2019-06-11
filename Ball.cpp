#include "Ball.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

Ball::Ball(int x, int y)
{
    this->y = y;
    this->x = x;
    this->speedy = -1;
    this->hit = false;
    this->scrx = getmaxx(stdscr);
    this->scry = getmaxy(stdscr);
}

Ball::~Ball()
{
}

void Ball::move(){
    
    if (this->x + speedx <= 0)
    {
        if (this->x + speedx == 0) this->x=0;
        else 
               // this->x = abs(this->x + speedx); // speed higher than discance
        speedx *= -1; 
    }
    else
    {
        this->x += speedx; 
    }

    if (this->y <= 0 )
    {
        if (this->y == 0) 
            this->y = -1;
        
    }
    else 
    {
        this->y += speedy;
    }
}


