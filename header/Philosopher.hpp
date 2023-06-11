#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP
#include <mutex>
#include <iostream>
#include <thread>
#include "Dish.hpp"
#include "Kitchen.hpp"
#include <ncurses.h>
using namespace std;


class Philosopher{
private:
    int id;
    int status;
    int leftFork;
    int rightFork;
    int leftStick;
    int rightStick;

    int* zmienna;
    mutex* mtx;

    mutex* sticks;
    mutex* forks;
    mutex* print_guard;

    Kitchen kitchen;
    bool mealType =0; //0- spagetti, 1- sushi

    int testIterator = 0;

    WINDOW* win_spaggetti;
    WINDOW* win_left_spaggetti;
    WINDOW* win_right_spaggetti;

    WINDOW* win_sushi;
    WINDOW* win_left_sushi;
    WINDOW* win_right_sushi;

    /*
    0 - Thinking
    1 - Hungry
    2 - Eating
    
    */


    public:
        Philosopher(int id,int left, int right, mutex forks[],mutex *print_guard);
        Philosopher(int id, int leftFork, int rightFork, int leftStick, int rightStick, mutex * sticks, mutex * forks, mutex * print_guard, Kitchen kitchen, int * zmienna, mutex *mtx);
void setId(int id);
        void setStatus(int status);
        int getId();
        int getStatus();
        void decide();
        void eat(int firstFork);
        void eatSpaggetti(int firstFork);
        void eatSushi(int firstStick);
        void think(int time);
        void runPhilosopher();
        std::thread initPhilosopher();
        void addZmienna();
        void setWindowDisplay(WINDOW* win_spaggetti,WINDOW* win_left_spaggetti,WINDOW* win_right_spaggetti,WINDOW* win_sushi,WINDOW* win_left_sushi,WINDOW* win_right_sushi);
        void clearBoxes();
        void printBox(int foodType, int side, int color,const char* text);

};
#endif