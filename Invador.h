#pragma once

class Invador
{
private:
public:

    int width;
    int height;
    int x;
    int y;
    int ID;
    int scrX;
    int scrY;
    bool inSleep;
    bool outOfGame;
    int health;
    int angleX;
    int angleY;
    void paintInvador();
    void step();
    Invador(int width, int height, int x, int y, int speedY);
    ~Invador();
};


