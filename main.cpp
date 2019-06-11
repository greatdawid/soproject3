#include <iostream>
#include <mutex>
#include <ncurses.h>
#include <unistd.h>
#include <condition_variable>
#include <vector>
#include <thread>
#include "Player.h"
#include "Ball.h"
#include "Invador.h"

std::condition_variable cv;
std::vector <Ball *> balls;
std::vector <Invador *> invadors;
Player *controlledPlayer;
int winX,winY;
bool isRunning = true;
std::mutex mtxBalls, mtxInvadors, mtx;

std::vector <std::thread> ballThreads;
std::vector <std::thread> invadorsThreads;

void updateScreen(){
    while(isRunning){
        clear();
        mtxInvadors.lock();
        for (int i = 0; i < invadors.size(); i++)
        {
            if(invadors[i]->health > 0){
            invadors[i]->paintInvador();
            }
        }
        controlledPlayer->paintPlayer();
        mtxInvadors.unlock();
        mtxBalls.lock();
        for (int i = 0; i < balls.size(); i++)
        {
            if(!balls[i]->hit){
            mvprintw(balls[i]->y, balls[i]->x,"o");
            }
        }
        mtxBalls.unlock();
        refresh();
        usleep(40000);
    }
}

bool isNear(int b1x,int b1y, int b2x, int b2y){

    if (abs(b1x-b2x) <= 1 && abs(b1y-b2y) <=1) {
        return true;
    }
    else
    {
        return false;
    }
}


bool ballOutofScreen(int y){
    if (y < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void checkingCollision(int number){
     if(ballOutofScreen(balls[number]->y)) {
         balls[number]->hit = true;
         }  

     for(int i = 0; i < invadors.size(); i++ )
        {
            if(invadors[i]->health < 0) continue;
            //if (i == number) continue;                 
                int x = invadors[i]->x;
                int y = invadors[i]->y;
                if (isNear(x,y,balls[number]->x, balls[number]->y)){
                    mtxInvadors.lock();
                    invadors[i]->health = -1;
                    mtxInvadors.unlock();
                    balls[number]->hit = true;
            }
      }
}


void ballFunction(int ballId){
    while (isRunning)
    {           
        mtxBalls.lock();
        checkingCollision(ballId);
        mtxBalls.unlock();   
        if (balls[ballId]->hit) break;
        mtxBalls.lock();
        balls[ballId]->move();
        mtxBalls.unlock();
        usleep(100000);
    }
    
}


bool invadorOutOfScreen(int y){
    if (y + 1 > winY)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void invadorFunction(int invadorId){
    while(isRunning && invadors[invadorId]->health > 0){
        if(invadorOutOfScreen(invadors[invadorId]->y)) break;

            std::unique_lock<std::mutex> lck(mtx);
            while (invadors[invadorId]->inSleep) cv.wait(lck);       
            mtxInvadors.lock();
            invadors[invadorId]->step();
            mtxInvadors.unlock();
            usleep(600000);
    }
}

void summonInvadors(){
    int i=0;
    int tmp;
    while (isRunning)
    {   
        sleep(2);
        int positionX = rand()%winX-2 + 2;
       // Invador *inv = new Invador(3,3,positionX,1);
        
        mtxInvadors.lock();
        do
        {
            tmp=rand()%3;
        } while (tmp==0);
        
        invadors.push_back(new Invador(3,3,positionX,-2,tmp));
        invadorsThreads.push_back(std::thread(invadorFunction,i));   
        mtxInvadors.unlock();
        i++;
     //  if(i>20) return;
        
    }
    
}


void controlFunction()
{   
    int i = 0;
    while (isRunning)
    {
		char key = getchar();
		if (key == 27)
        {
	    	isRunning = false;
            cv.notify_all();
        }
        if (key == 97)
            controlledPlayer->step(-1,0);
        if (key == 100)
            controlledPlayer->step(1,0);
        if (key == 32)
        {
            mtxBalls.lock();
            balls.push_back(controlledPlayer->shootBall());
            ballThreads.push_back(std::thread(ballFunction, i));
            mtxBalls.unlock();
            i++;
        }
    }
}

void setScreenSettings(){

    initscr();
    noecho();
    // invisble cursor is set
    curs_set(0);
    getmaxyx(stdscr,winY,winX);
}


int main() 
{
    srand(time(NULL));
    setScreenSettings();
    controlledPlayer = new Player(5,2,winX/2.0,winY/1.1);
    std::thread screenThread(updateScreen);
    std::thread invadorsThread(summonInvadors);
    std::thread controllThread(controlFunction);

    screenThread.join();
    controllThread.join();
    invadorsThread.join();
    for (int i = 0; i < invadors.size(); i++)
    {
        invadorsThreads[i].join();
    }
    for (int i = 0; i < balls.size(); i++)
    {
        ballThreads[i].join();
    }    
    
    endwin();


    return 0;
}