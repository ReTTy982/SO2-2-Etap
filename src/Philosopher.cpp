
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
        
        


        if (firstFork == 0){
            forks[leftFork].lock();
            forks[rightFork].lock();

        }
        else{
            forks[rightFork].lock();
            forks[leftFork].lock();
            
        }
            Dish dish = kitchen.giveDish(1);
            while(dish.getDishName() == "nie ma"){
                this_thread::sleep_for(chrono::seconds(1));
                dish = kitchen.giveDish(1);
            }
            std::cout << "ID " << id << "je " << dish.getDishName() << std::endl;
            this_thread::sleep_for(chrono::seconds(2));
            forks[leftFork].unlock();
            forks[rightFork].unlock();

    }

    void Philosopher::think(int time){
        std::cout << "ID: " << id << " mysli" << std::endl;
        this_thread::sleep_for(chrono::seconds(time));
    }

    void Philosopher::decide(){
        // 0 - parzysta, 1 - nieparzysta
        eat(id % 2);

       
    }

    void Philosopher::runPhilosopher(){
        while(true){
            think(2);
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




