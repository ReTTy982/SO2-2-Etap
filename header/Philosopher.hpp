#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP


class Philosopher{
private:
    int id;
    int status;
    /*
    0 - Thinking
    1 - Hungry
    2 - Eating
    
    */

    public:
        Philosopher(int id);
        void setId(int id);
        void setStatus(int status);
        int getId();
        int getStatus();

};
#endif