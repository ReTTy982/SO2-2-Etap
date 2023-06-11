
#include "../header/Philosopher.hpp"


    Philosopher::Philosopher(int id, int leftFork, int rightFork, int leftStick, int rightStick, mutex *sticks, mutex *forks, mutex *print_guard, Kitchen kitchen, int *zmienna,mutex *mtx){
        this -> id = id;
        this -> status = 0;
        this -> leftFork = leftFork;
        this -> rightFork = rightFork;

        this -> leftStick = leftStick;
        this -> rightStick = rightStick;

        this -> sticks = sticks;
        this -> forks = forks;
        this -> print_guard = print_guard;
        this -> kitchen = kitchen;
        this -> zmienna = zmienna;
        this -> mtx = mtx;
 
    
    }
       

    void Philosopher::setId(int id){
        this -> id  = id;
    }

    void Philosopher::setStatus(int status){
        this -> status = status;
    }

    int Philosopher::getId(){
        return id;
    }


    int Philosopher::getStatus(){
        return status;
    }

    void Philosopher::testMutex(){
        while(true){
            this_thread::sleep_for(chrono::seconds(2));
            {
                lock_guard<mutex> lock(*print_guard);
                cout << "ID: " << id << "   Oczekuje " << endl;
            }
            forks[0].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                cout << "ID: " << id << "   Mam" << endl;
            }
            this_thread::sleep_for(chrono::seconds(2));
            {
                lock_guard<mutex> lock(*print_guard);
                cout << "ID: " << id << "   Zostawiam" << endl;
            }
            forks[0].unlock();


        }


         //std::unique_lock<std::mutex> left_lock(forks[left], std::defer_lock);
    }

    void Philosopher::eat(int firstFork){
        
        {
            lock_guard<mutex> lock(*print_guard);
            werase(win);
            box(win, 0, 0);
            mvwprintw(win, 1, 1, "Hungry");
            wbkgd(win, COLOR_PAIR(1));
            wrefresh(win);
        }


        if (firstFork == 0){
            forks[leftFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                werase(win);
                box(win_left,0,0);
                wbkgd(win_left,COLOR_PAIR(4));
                mvwprintw(win_left, 1, 1, "Left");
                box(win_right,0,0);
                wbkgd(win_right, COLOR_PAIR(1));
                mvwprintw(win_right, 1, 1, " ");
                wrefresh(win_right);
                wrefresh(win_left);
            }
            std::this_thread::sleep_for(chrono::seconds(2));
            forks[rightFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                werase(win);
                box(win_left,0,0);
                wbkgd(win_left,COLOR_PAIR(4));
                mvwprintw(win_left, 1, 1, "Left");
                box(win_right,0,0);
                wbkgd(win_right, COLOR_PAIR(4));
                mvwprintw(win_right, 1, 1, "Right");
                wrefresh(win_right);
                wrefresh(win_left);
            }

        }
        else{
            forks[rightFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                werase(win);
                box(win_left,0,0);
                wbkgd(win_left,COLOR_PAIR(1));
                mvwprintw(win_left, 1, 1, " ");
                box(win_right,0,0);
                wbkgd(win_right, COLOR_PAIR(4));
                mvwprintw(win_right, 1, 1, "Right");
                wrefresh(win_right);
                wrefresh(win_left);
            }
            std::this_thread::sleep_for(chrono::seconds(2));
            forks[leftFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                werase(win);
                box(win_left,0,0);
                wbkgd(win_left,COLOR_PAIR(4));
                mvwprintw(win_left, 1, 1, "Left");
                box(win_right,0,0);
                wbkgd(win_right, COLOR_PAIR(4));
                mvwprintw(win_right, 1, 1, "Right");
                wrefresh(win_right);
                wrefresh(win_left);

            }
            
        }
            this_thread::sleep_for(chrono::seconds(2));
            Dish dish = kitchen.giveDish(1);
            while(dish.getDishName() == "nie ma"){   
                { 
                lock_guard<mutex> lock(*print_guard);
                werase(win_left);
                werase(win_right);
                werase(win);
                box(win, 0, 0);
                mvwprintw(win, 1, 1, "Waiting for food");
                wbkgd(win, COLOR_PAIR(5));
                wrefresh(win);     
                }
                dish = kitchen.giveDish(1);

                this_thread::sleep_for(chrono::seconds(1));
                
            }
            {
                lock_guard<mutex> lock(*print_guard);
                werase(win_left);
                werase(win_right);
                werase(win);
                box(win, 0, 0);
                mvwprintw(win, 1, 1, "Eating");
                wbkgd(win, COLOR_PAIR(3));
                wrefresh(win);
            }
            
            this_thread::sleep_for(chrono::seconds(2)); 
            forks[leftFork].unlock();
            forks[rightFork].unlock();
            
            



    }

    void Philosopher::think(int time){
        {
            lock_guard<mutex> lock(*print_guard);
            werase(win);
            box(win,0,0);
            //init_pair(2, COLOR_WHITE, COLOR_GREEN);
            wbkgd(win,COLOR_PAIR(2));
            mvwprintw(win,1,1,"MYSLI %d", id );
            wrefresh(win);
            testIterator++;
            

        }
        this_thread::sleep_for(chrono::seconds(time));
    }

    void Philosopher::decide(){
        // 0 - parzysta, 1 - nieparzysta
        eat(id % 2);

       
    }

    void Philosopher::runPhilosopher(){
        while(true){
            think(3);
            decide();

        }
    }

    std::thread Philosopher::initPhilosopher(){
        return std::thread(&Philosopher::runPhilosopher, this);

    }

    void Philosopher::addZmienna(){
        while(true){
            std::lock_guard<std::mutex> lock(*mtx);

            (*zmienna)++;
            std::cout << *zmienna << " " << id << std::endl;
            std::cout << "test" << std::endl;
            mtx->unlock();
            this_thread::sleep_for(chrono::seconds(2));
        }

    }


    void Philosopher::setWindowDisplay(WINDOW* win,WINDOW* win_left,WINDOW* win_right){

        this-> win = win;
        this-> win_left = win_left;
        this-> win_right = win_right;
    }

