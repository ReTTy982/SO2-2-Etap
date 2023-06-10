#include "../header/Dish.hpp"

void Dish::setFreshEnum()
{

    if (expirationValue > staleMax)
    {
        freshType = FreshType::FRESH;
    }
    else if (expirationValue > outdatedMax)
    {
        freshType = FreshType::STALE;
    }
    else
    {
        freshType = FreshType::OUTDATED;
    }

    }


    void Dish::setExpirationValue(int expirationValue){

        if(expirationValue < 0 || expirationValue >100){
            throw std::invalid_argument("expiration point must be between 0 and 100");
        }
        else{
            expirationValue = expirationValue;
            setFreshEnum();
        }
    }

    void Dish::setDishName(std::string dishName){

        this->dishName = dishName;
    }

    Dish::Dish(int id, int expirationValue, int expirationSubtract, std::string dishName){
        
        this->id= id;
        setExpirationSubtract(expirationSubtract);
        setDishName(dishName);
        setExpirationValue(expirationValue);
    }

    Dish::Dish(int id, std::string dishName){
        this ->id = id;
        this->setDishName(dishName);
        setFreshEnum();
    }

    Dish::Dish(){}

    

    void Dish::setExpirationSubtract(int expirationSubtract){

        this->expirationSubtract = expirationSubtract;

    }


    int Dish::getExpirationValue() const{
        return expirationValue;
    }

    int Dish::getExpirationSubtract(){
        return expirationSubtract;
    }

    std::string Dish::getDishName(){
        return dishName;
    }

    void Dish::expirationValueGoesDownInCycle(){

        expirationValue -=expirationSubtract;
        if(expirationValue < 0){
            expirationValue = 0;
        }

        setFreshEnum();

    }
