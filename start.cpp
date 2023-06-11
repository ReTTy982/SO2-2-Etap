#include <iostream>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include "header/Dish.hpp"
#include "header/Philosopher.hpp"
#include "header/Kitchen.hpp"


using namespace std;
int PHIL_LEN = 20;


int main()
{   
    cbreak();
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4,COLOR_WHITE,COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);

    int HEIGHT = 40;
    int WIDTH = 60;

    int starty = LINES - HEIGHT - 1;
    int startx = COLS - WIDTH -1;

    WINDOW* kitchen_win = newwin(HEIGHT,WIDTH,starty,startx);
    werase(kitchen_win);
    
    int zmienna = 0;
    mutex sticks[PHIL_LEN];
    mutex forks[PHIL_LEN];
    mutex print_guard;
    thread philosophers[PHIL_LEN];
    mutex mtx;
    WINDOW* win_spaggetti[PHIL_LEN];
    WINDOW* win_left_spaggetti[PHIL_LEN];
    WINDOW* win_right_spaggetti[PHIL_LEN];

    WINDOW* win_sushi[PHIL_LEN];
    WINDOW* win_left_sushi[PHIL_LEN];
    WINDOW* win_right_sushi[PHIL_LEN];

    // TO BEDZIE DOBRZE

    vector<Dish> spaggettiVector;
    vector<Dish> sushiVector;
    mutex kitchenMutex;
    Kitchen kitchen;
    kitchen.setWindow(kitchen_win,&print_guard);
    kitchen.setVectors(&kitchenMutex, spaggettiVector, sushiVector);
    //Philosopher(int id, int leftFork, int rightFork, int leftStick, int rightStick, mutex * sticks, mutex * forks, mutex * print_guard);

    // Philosopher fil1 = Philosopher(i,i,(i + 1) % PHIL_LEN,i,(i + 1) % PHIL_LEN,sticks,forks, &print_guard, kitchen,&zmienna,&mtx);
    // i =1;
    // Philosopher fil2 = Philosopher(
    // i,
    // i,
    // (i + 1) % PHIL_LEN,
    // i,
    // (i + 1) % PHIL_LEN,
    // sticks,forks,
    // &print_guard, 
    // kitchen,
    // &zmienna,&mtx);


    
  

    thread kitchenThread;

    // philosophers[0] = thread(&Philosopher::testMutex, &fil1);
    // philosophers[1] = thread(&Philosopher::testMutex, &fil2);
    //philosophers[0] = thread(Philosopher::testMutex(),fil1,0);
    //philosophers[1] = thread(fil2.testMutex(),1);



   
    // philosophers[0].join();
    // philosophers[1].join();
    

    // philosophers[0] = thread(&Philosopher::addZmienna, &fil1);
    // philosophers[1] = thread(&Philosopher::addZmienna, &fil2);





    

 
    for(int i =0; i < PHIL_LEN; i++){
        Philosopher fil = Philosopher(
        i,
        i,
        (i + 1) % PHIL_LEN,
        i,
        (i + 1) % PHIL_LEN,
        sticks,
        forks,
        &print_guard, 
        kitchen,
        &zmienna,
        &mtx);

        win_spaggetti[i] = newwin(3, 30, i * 3, 0);
        win_left_spaggetti[i] = newwin(3,15,i*3,0);
        win_right_spaggetti[i] = newwin(3,15,i*3,15);
        win_sushi[i] = newwin(3,30,i*3,30);
        win_left_sushi[i] = newwin(3,15,i*3,30);
        win_right_sushi[i] = newwin(3,15,i*3,45);


        //wrefresh(win[i]);
        fil.setWindowDisplay(win_spaggetti[i],win_left_spaggetti[i],win_right_spaggetti[i],win_sushi[i],win_left_sushi[i],win_right_sushi[i]);

        // philosophers[i] = fil.initPhilosopher();
        philosophers[i] = thread(&Philosopher::runPhilosopher,fil);
    }

    

    kitchenThread =  kitchen.runKitchen();



    for(int i=0; i<PHIL_LEN;i++){
        philosophers[i].join();
    }
        kitchenThread.join();


    // ========= TO DZIALA ==============
        // int i  =0;
        // Philosopher fil1 = Philosopher(
        // i,
        // i,
        // (i + 1) % PHIL_LEN,
        // i,
        // (i + 1) % PHIL_LEN,
        // sticks,
        // forks,
        // &print_guard, 
        // kitchen,
        // &zmienna,
        // &mtx);
        // i=1;
        // Philosopher fil2 = Philosopher(
        // i,
        // i,
        // (i + 1) % PHIL_LEN,
        // i,
        // (i + 1) % PHIL_LEN,
        // sticks,
        // forks,
        // &print_guard, 
        // kitchen,
        // &zmienna,
        // &mtx);
        // philosophers[0] = thread(&Philosopher::runPhilosopher,&fil1);
        // philosophers[1] = thread(&Philosopher::runPhilosopher,&fil2);
        // philosophers[0].join();
        // philosophers[1].join();
        // kitchenThread.join();




    int wait;
    std::cin>>wait;
    endwin();
    

    return 0;

}




