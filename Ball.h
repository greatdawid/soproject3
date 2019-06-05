#pragma once

class Ball
{
private:
    
public:
    int x;
    int y; 
    int scrx;
    int scry;
    double speedx;
    double speedy;
    bool hit;
    Ball(int x, int y);
    void move();
    bool inside(int x, int y); //not here in enemy class
    ~Ball();
};


