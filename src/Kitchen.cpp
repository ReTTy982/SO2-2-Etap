#include "../header/Kitchen.hpp"




void Kitchen::cookDish(int groupId, int id){

    if(groupId ==1){
        std::cout << "TESTUJE" << std::endl;
        Dish dish = Dish(id, "spagetti");
        this->spaggettiVector.push_back(dish);
        std::cout << "PIERWSZY SIZE: " << spaggettiVector.size() << std::endl;
    } else if(id ==2){
        Dish dish = Dish(id, "sushi");
        this->sushiVector.push_back(dish);
    }

}

Dish Kitchen::giveDish(int id){ //0- nie ma, 1-spaggetti, 2-sushi

    Dish currentDish;

    if(id==1){
        std::cout << "TEST SIZE: " << spaggettiVector.size() << std::endl;
        if(spaggettiVector.size()>0){
            currentDish = spaggettiVector[0];
            std::cout << "TEST: " << currentDish.getDishName() << std::endl;
            spaggettiVector.erase(spaggettiVector.begin());
            spaggettiGivenCounter++;
        }
        else{
            return Dish(0, "nie ma");
        }

    } else if(id ==2){

        if(sushiVector.size()>0){
            currentDish = sushiVector[0];
            sushiVector.erase(sushiVector.begin());
            sushiGivenCounter++;
        }

    }

     return currentDish;

}

void Kitchen::displayDishes(){

    for(auto dish : sushiVector){
        std::cout<<dish.getDishName()<<" "<<dish.getExpirationValue()<<"\n";
    }

    for(auto dish : spaggettiVector){
        std::cout<<dish.getDishName()<<" "<<dish.getExpirationValue()<<"\n";
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
    //threadObj.detach();
    
}

void Kitchen::startCooking(){

    int random = 0;

    while(true){

        std::this_thread::sleep_for(std::chrono::seconds(2));
        if(random%2==0){
            
            cookDish(1, random);
        } else{
            Dish dish = Dish(random, "sushi");
            cookDish(2, random);
        }
        random++;
    }
}