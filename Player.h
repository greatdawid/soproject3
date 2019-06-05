#pragma once
#include "Ball.h"

class Player
{
private:
 
public:
    int height;
    int width;
    int x;
    int y;
    int scrX;
    int scrY;
    Player(int width, int height, int x, int y);
    ~Player();
    int getx();
    int gety();
    int getHeight();
    int getWidth();
    Ball* shootBall();
    void step(int shiftX, int shiftY);
    void paintPlayer();
};