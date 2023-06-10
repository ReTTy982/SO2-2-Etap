#include <iostream>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include "header/Dish.hpp"
#include "header/Philosopher.hpp"
#include "header/Kitchen.hpp"


using namespace std;
int PHIL_LEN = 10;


int main()
{   
    

    
    int i = 0;
    mutex tab[PHIL_LEN];
    mutex print_guard;
    thread philosophers[2];

    Philosopher fil1 = Philosopher(i,i,(i + 1) % PHIL_LEN,tab, &print_guard);
    i =1;
    Philosopher fil2 = Philosopher(i,i,(i + 1) % PHIL_LEN,tab, &print_guard);


    philosophers[0] = thread(&Philosopher::testMutex, &fil1);
    philosophers[1] = thread(&Philosopher::testMutex, &fil2);
    //philosophers[0] = thread(Philosopher::testMutex(),fil1,0);
    //philosophers[1] = thread(fil2.testMutex(),1);
    philosophers[0].join();
    philosophers[1].join();

    Dish obj2 = Dish("lody");


    cout << obj2.getDishName() << endl;

    return 0;

}




