#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <queue>
#include <vector>
#include <iostream>
#include "../header/Dish.hpp"
#include <thread>


class Kitchen
{
private:

    std::vector<Dish> spaggettiVector;
    std::vector<Dish> sushiVector;

    int spaggettiGivenCounter = 0;
    int sushiGivenCounter = 0;

public:
    

   void cookDish(int groupId, int id);
   Dish giveDish(int id);
   void displayDishes();
    int getSushiGivenCounter();
    int getSpaggettiGivenCounter();
    std::thread runKitchen();
    void startCooking();
    void setVectors(std::vector<Dish> &spagettiVector, std::vector<Dish> &sushiVector);
};


#endif


