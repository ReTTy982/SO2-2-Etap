
#include "../header/Philosopher.hpp"



using namespace std;

    Philosopher::Philosopher(int id, int left, int right, mutex *forks, mutex *print_guard){
        this -> id = id;
        this -> status = 0;
        this -> left = left;
        this -> right = right;
        this -> forks = forks;
        this -> print_guard = print_guard;
 
    
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
            forks[left].lock();
            forks[right].lock();
        }
        else{
            forks[right].lock();
            forks[left].lock();
        }
    }

    void Philosopher::think(int time){
        this_thread::sleep_for(chrono::seconds(time));
    }

    void Philosopher::decide(){
        // 0 - parzysta, 1 - nieparzysta
        eat(id % 2);

       
    }




