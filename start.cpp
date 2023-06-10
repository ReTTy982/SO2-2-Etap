#include <iostream>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include "header/Dish.hpp"
#include "header/Philosopher.hpp"


using namespace std;
int main()
{
    Philosopher obj1 = Philosopher(0);
    Dish obj2 = Dish("lody");

    cout << obj1.getId() << endl;
    cout << obj2.getDishName() << endl;

    return 0;

}




