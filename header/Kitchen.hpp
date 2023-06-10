#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <queue>
#include <vector>
#include <iostream>
#include "../header/Dish.hpp"



class Kitchen
{
private:

    std::vector<Dish> spaggettiVector;
    std::vector<Dish> sushiVector;

    int spaggettiGivenCounter = 0;
    int sushiGivenCounter = 0;

public:
    

   void cookDish(Dish dish);
   Dish giveDish(std::string dishName);
   void displayDishes();
    int getSushiGivenCounter();
    int getSpaggettiGivenCounter();


};


#endif


