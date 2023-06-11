
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

    void Philosopher::clearBoxes(){
        werase(win_spaggetti);
        werase(win_left_spaggetti);
        werase(win_right_spaggetti);
        werase(win_sushi);
        werase(win_left_sushi);
        werase(win_right_sushi);

    }
    //foodType -0spagetti, int side 0-centar, 1-left, 2right, int color <0,5>, const char*text
    void Philosopher::printBox(int foodType, int side, int color,const char* text){
            WINDOW* window;
            if(foodType == 0){ // 0 - spaggetti 1 - sushi
                if ((side ==0 )){
                    window = win_spaggetti;
                }
                else if(side == 1){
                    window = win_left_spaggetti;
                }
                else if(side ==2){
                    window = win_right_spaggetti;
                }
            } else{
                
                if ((side ==0 )){
                    window = win_sushi;
                }
                else if(side == 1){
                    window = win_left_sushi;
                }
                else if(side ==2){
                    window = win_right_sushi;
                }

            }

            box(window, 0, 0);
            mvwprintw(window, 1, 1,"%s", text);
            wbkgd(window, COLOR_PAIR(color));
            wrefresh(window);
    }

    void Philosopher::eatSpaggetti(int firstFork){
        if (firstFork == 0){
            forks[leftFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();

                printBox(0,1,4,"Left");
                printBox(0,2,1," ");

            }
            std::this_thread::sleep_for(chrono::seconds(2));
            forks[rightFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(0, 1, 4 ,"Left");
                
                clearBoxes();
                printBox(0, 2, 4 ,"Right");
                
                
            }

        }
        else{
            forks[rightFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(0,1,1," ");
                printBox(0,2,4,"Right");
            }
            std::this_thread::sleep_for(chrono::seconds(2));
            forks[leftFork].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                clearBoxes();
                printBox(0,1,4,"Left");
                printBox(0,2,4,"Right");


            }
            
        }
            this_thread::sleep_for(chrono::seconds(2));
            Dish dish = kitchen.giveDish(1);
            while(dish.getDishName() == "nie ma"){   
                { 
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(0,0,5,"Waiting for food");    
                }
                dish = kitchen.giveDish(1);

                this_thread::sleep_for(chrono::seconds(1));
                
            }
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(0,0,3,"Eating");
            }
            
            this_thread::sleep_for(chrono::seconds(2)); 
            forks[leftFork].unlock();
            forks[rightFork].unlock();

    }


    void Philosopher::eatSushi(int firstStick){

        if (firstStick == 0){
            sticks[leftStick].lock();
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();

                printBox(1,1,4,"Left");
                printBox(1,2,1," ");

            }
            std::this_thread::sleep_for(chrono::seconds(2));
            sticks[rightStick].lock();
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(1, 1, 4 ,"Left");
                
                clearBoxes();
                printBox(1, 2, 4 ,"Right");
                
                
            }

        }
        else{
            sticks[rightStick].lock();
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(1,1,1," ");
                printBox(1,2,4,"Right");
            }
            std::this_thread::sleep_for(chrono::seconds(2));
            sticks[leftStick].lock();
            {
                lock_guard<mutex> lock(*print_guard);
                clearBoxes();
                printBox(1,1,4,"Left");
                printBox(1,2,4,"Right");


            }
            
        }
            this_thread::sleep_for(chrono::seconds(2));
            Dish dish = kitchen.giveDish(2);
            while(dish.getDishName() == "nie ma"){   
                { 
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(1,0,5,"Waiting for food");    
                }
                dish = kitchen.giveDish(2);

                this_thread::sleep_for(chrono::seconds(1));
                
            }
            {
                lock_guard<mutex> lock(*print_guard);

                clearBoxes();
                printBox(1,0,3,"Eating");
            }
            
            this_thread::sleep_for(chrono::seconds(2)); 
            sticks[leftStick].unlock();
            sticks[rightStick].unlock();


    }
        


    void Philosopher::eat(int firstFork){
        {
            lock_guard<mutex> lock(*print_guard);
            clearBoxes();
            printBox(1,0,1,"Hungry");
        }
        eatSushi(firstFork);

    }
            
            

    void Philosopher::think(int time){
        {
            lock_guard<mutex> lock(*print_guard);
            clearBoxes();
            //printBox(0,0,2,"Thinking");
            printBox(1,0,2,"Thinking");
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


    void Philosopher::setWindowDisplay(WINDOW* win_spaggetti,WINDOW* win_left_spaggetti,WINDOW* win_right_spaggetti,WINDOW* win_sushi,WINDOW* win_left_sushi,WINDOW* win_right_sushi){

    
        this-> win_spaggetti = win_spaggetti;
        this-> win_left_spaggetti = win_left_spaggetti;
        this-> win_right_spaggetti = win_right_spaggetti;
        this-> win_sushi = win_sushi;
        this-> win_left_sushi = win_left_sushi;
        this-> win_right_sushi = win_right_sushi;
    }

