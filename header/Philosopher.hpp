#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP
#include <mutex>
#include <iostream>
#include <thread>
#include "Dish.hpp"
#include "Kitchen.hpp"
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
        void testMutex();
        void decide();
        void eat(int firstFork);
        void think(int time);
        void runPhilosopher();
        std::thread initPhilosopher();
        void addZmienna();
        


};
#endif