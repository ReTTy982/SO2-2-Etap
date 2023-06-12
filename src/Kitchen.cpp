#include "../header/Kitchen.hpp"




void Kitchen::cookDish(int groupId, int id){ //1-spaggetti, 2-sushi

    if(groupId ==1){
        Dish dish = Dish(id, "spaggetti");
        (*spaggettiVector).push_back(dish);
        {
                printBox();
        }
    } else if(groupId ==2){
        Dish dish = Dish(id, "sushi");
        (*sushiVector).push_back(dish);

        {
            
                printBox();

        }
    }

}

Dish Kitchen::giveDish(int id){ //0- nie ma, 1-spaggetti, 2-sushi

    Dish currentDish;

    if(id==1){
       // std::cout << "TEST SIZE: " << (*spaggettiVector).size() << std::endl;
        if((*spaggettiVector).size()>0){
            currentDish = (*spaggettiVector).front();
            (*spaggettiVector).erase((*spaggettiVector).begin());
            spaggettiGivenCounter++;
        }
        else{
            return Dish(0, "nie ma");
        }

    } else if(id ==2){

        if((*sushiVector).size()>0){
            currentDish = (*sushiVector)[0];
            (*sushiVector).erase((*sushiVector).begin());
            sushiGivenCounter++;
        }
        else{
            return Dish(1, "nie ma");
        }

    }

    //tutaj
    {
                
                printBox();
              

    }



     return currentDish;

}

void Kitchen::displayDishes(){

    for(auto dish : (*sushiVector)){
        std::cout<<dish.getDishId()<<" "<<dish.getExpirationValue()<<"\n";
        //dish.
    }

    for(auto dish : (*spaggettiVector)){
        std::cout<<dish.getDishId()<<" "<<dish.getExpirationValue()<<"\n";
    }


}

int Kitchen::getSpaggettiGivenCounter(){
    return spaggettiGivenCounter;
    
    
}


int Kitchen::getSushiGivenCounter(){
    return sushiGivenCounter;

}

std::thread Kitchen::runKitchen(){

    return std::thread(&Kitchen::startCooking, this);

}

void Kitchen::startCooking(){

    int foodId = 0;
    

    while(true){

        for(int i=0; i<HOW_MANY_SPAGGETTI_IN_CYCLE; i++){

            cookDish(1, foodId);
            foodId++;
            expirationOnVectors();
            std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_COOK_DISH));
        }


        for(int i=0; i<HOW_MANY_SUSHI_IN_CYCLE; i++){

            cookDish(2, foodId);
            foodId++;
            expirationOnVectors();
            std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_COOK_DISH));
        }


    }
   
}

void Kitchen::setVectors(std::mutex *kitchenMutex, std::vector<Dish> &spagettiVector, std::vector<Dish> &sushiVector){

    this->kitchenMutex = kitchenMutex;
    this->spaggettiVector = &spagettiVector;
    this->sushiVector = &sushiVector;
}

void Kitchen::setWindow(WINDOW *kitchenWindow, std::mutex* print_guard){
    this->kitchenWindow = kitchenWindow;
    this-> print_guard = print_guard;
}

void Kitchen::expirationOnVectors(){

    for(auto& dish : *spaggettiVector){
        dish.expirationValueGoesDownInCycle();
    }

        for(auto& dish : *sushiVector){
        dish.expirationValueGoesDownInCycle();
    }
}

void Kitchen::printBox(){
        {
                std::lock_guard<std::mutex> lock(*print_guard);
                werase(kitchenWindow);
                box(kitchenWindow, 0, 0);
                int i = 0;
                for(auto& dish : *spaggettiVector){
                    int dishId = dish.getDishId(); 
                    int dishExpiration = dish.getExpirationValue();
                     
                    mvwprintw(kitchenWindow,i+1,1, "%d ; %d", dishId,dishExpiration);
                    i++;
                }
                i =0;
                for(auto& dish : *sushiVector){
                    int dishId = dish.getDishId(); 
                    int dishExpiration = dish.getExpirationValue();
                     
                    mvwprintw(kitchenWindow,i+1,30, "%d ; %d", dishId,dishExpiration);
                    i++;
                }
                
                wrefresh(kitchenWindow);
                
        }
}

bool Kitchen::compareDishes(){

    int spaggettiVal;
    int sushiVal;

    if((*spaggettiVector).size()>0){
        spaggettiVal =  (*spaggettiVector).front().getExpirationValue();
    } else{
        return false;
    }
       
    if((*sushiVector).size()>0){

        sushiVal = (*sushiVector).front().getExpirationValue();
    } else{
        return true;
    }
   
    if((*spaggettiVector).size() + VECTOR_OPTIMALIZATION < (*sushiVector).size()){
        return false;
    } else if((*spaggettiVector).size() + VECTOR_OPTIMALIZATION > (*sushiVector).size()){
        return true;
    }


    //return false;

  if(spaggettiVal>sushiVal){
    return false;
  }
  return true;

}
