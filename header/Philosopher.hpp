#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP
#include <mutex>
#include <iostream>
#include <thread>
using namespace std;


class Philosopher{
private:
    int id;
    int status;
    int leftFork;
    int rightFork;
    int leftStick;
    int rightStick;

    mutex* sticks;
    mutex* forks;
    mutex* print_guard;

    bool mealType =0; //0- spagetti, 1- sushi

    /*
    0 - Thinking
    1 - Hungry
    2 - Eating
    
    */


    public:
        Philosopher(int id,int left, int right, mutex forks[],mutex *print_guard);
        Philosopher(int id, int leftFork, int rightFork, int leftStick, int rightStick, mutex * sticks, mutex * forks, mutex * print_guard);
void setId(int id);
        void setStatus(int status);
        int getId();
        int getStatus();
        void testMutex();
        void decide();
        void eat(int firstFork);
        void think(int time);


};
#endif