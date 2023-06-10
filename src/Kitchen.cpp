#include "../header/Kitchen.hpp"




void Kitchen::cookDish(Dish dish){

    if(dish.getDishName() == "spaggetti"){
        spaggettiVector.push_back(dish);
    } else if( dish.getDishName() == "sushi"){
        sushiVector.push_back(dish);
    }

}

Dish Kitchen::giveDish(std::string dishName){

    Dish currentDish;

    if(dishName == "spaggetti"){

        if(spaggettiVector.size()>0){
            currentDish = spaggettiVector.front();
            spaggettiVector.erase(spaggettiVector.begin());
            spaggettiGivenCounter++;
        }

    } else if(dishName == "sushi"){

        if(sushiVector.size()>0){
            currentDish = sushiVector.front();
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


int Kitchen::getSpaggettiGivenCounter(){
    return sushiGivenCounter;
}

