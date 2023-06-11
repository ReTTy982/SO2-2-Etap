#ifndef DISH_HPP
#define DISH_HPP
#include <string>
#include <stdexcept>
#include <map>

class Dish{

enum FreshType{

        FRESH,
        STALE,
        OUTDATED

    };

FreshType freshType;


int expirationValue = 500; 
    int expirationSubtract = 1; //jak szybko danie sie zuzywa
    std::string dishName;

    int freshMax =100;
    int staleMax = 50;
    int outdatedMax = 20;
    int id;

void setFreshEnum();
public:

    void setExpirationValue(int expirationValue);
    void setExpirationSubtract(int expirationSubtract);
    void setDishName(std::string dishName);
    Dish(int id, int expirationValue, int expirationSubtract, std::string dishName);
    Dish(int id, std::string dishName);
    Dish();
    int getExpirationValue() const;
    int getExpirationSubtract();
    int getDishId();
    std::string getDishName();
    void expirationValueGoesDownInCycle();
    
};
#endif