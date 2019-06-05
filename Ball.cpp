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
    else if (this->x + speedx >= scrx)
    {
        // if (this->x + speedx == scrx) this->x = scrx-1;
        // speedx *= -1; 
    }
    else
    {
        this->x += speedx; 
    }

    if (this->y <= 0 )
    {
        if (this->y == 0) 
            this->y = -1;
        //else
                //this->Y = abs(this->Y + speedY); // speed higher than discance
        //this->speedy *= -1;
    }

    // if (this -> y  > scry - 1 ) 
    // {
    //     this -> y = scry - 1;
    //     speedy *=  0.55;
    //     speedy *= -1;
    //     if (abs(speedy) < 6.00) 
    //         speedy *= 0.3; 
    //     if (abs(speedy) < 2.0) 
    //         this->y = scry; 
    // }
    else 
    {
        this->y += speedy;
    }
}
// bool Ball::inside(int tmpx, int tmpy){
//     return (( x >= tmpx && x <= tmpx + width) && ( y >= tmpy && y <= tmpy + height));
// }

