
#include "../header/Philosopher.hpp"

    Philosopher::Philosopher(int id){
        this -> id = id;
        this -> status = 0;
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

