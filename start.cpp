#include <iostream>
#include <thread>
#include <mutex>
// #include <ncurses.h>
#include "header/Dish.hpp"
#include "header/Philosopher.hpp"
#include "header/Kitchen.hpp"


using namespace std;
int PHIL_LEN = 10;


int main()
{   
    
    
    int zmienna = 0;
    int i = 0;
    mutex sticks[PHIL_LEN];
    mutex forks[PHIL_LEN];
    mutex print_guard;
    thread philosophers[2];
    mutex mtx;

    Kitchen kitchen;
    //Philosopher(int id, int leftFork, int rightFork, int leftStick, int rightStick, mutex * sticks, mutex * forks, mutex * print_guard);

    Philosopher fil1 = Philosopher(i,i,(i + 1) % PHIL_LEN,1,1,sticks,forks, &print_guard, kitchen,&zmienna,&mtx);
    i =1;
    Philosopher fil2 = Philosopher(
    i,
    i,
    (i + 1) % PHIL_LEN,
    1,
    1,
    sticks,forks,
    &print_guard, 
    kitchen,
    &zmienna,&mtx);


    
  

    thread kitchenThread;

    // philosophers[0] = thread(&Philosopher::testMutex, &fil1);
    // philosophers[1] = thread(&Philosopher::testMutex, &fil2);
    //philosophers[0] = thread(Philosopher::testMutex(),fil1,0);
    //philosophers[1] = thread(fil2.testMutex(),1);

    // philosophers[0] = fil1.initPhilosopher();

    // philosophers[1] = fil2.initPhilosopher();

    // kitchenThread =  kitchen.runKitchen();
    // philosophers[0].join();
    // philosophers[1].join();
    // kitchenThread.join();

    philosophers[0] = thread(&Philosopher::addZmienna, &fil1);
    philosophers[1] = thread(&Philosopher::addZmienna, &fil2);
    philosophers[0].join();
    philosophers[1].join();





    

    return 0;

}




