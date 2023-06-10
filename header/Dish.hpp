#ifndef DISH_HPP
#define DISH_HPP
#include <string>
#include <stdexcept>

class Dish{

enum FreshType{

        FRESH,
        STALE,
        OUTDATED

    };

FreshType freshType;


int expirationValue = 100; //100 świeże, 50 jako takie, 20- filozof sie zatruje
    int expirationSubtract = 10; //jak szybko danie sie zuzywa
    std::string dishName;

    int freshMax =100;
    int staleMax = 50;
    int outdatedMax = 20;

void setFreshEnum();
public:

    void setExpirationValue(int expirationValue);
    void setExpirationSubtract(int expirationSubtract);
    void setDishName(std::string dishName);
    Dish(int expirationValue, int expirationSubtract, std::string dishName);
    Dish(std::string dishName);
    int getExpirationValue();
    int getExpirationSubtract();
    std::string getDishName();
    void expirationValueGoesDownInCycle();
};
#endif