#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "hand.h"
using namespace std;
//Abstract Class for dealer and player
class Person{
    protected:
        string name, status;
        Hand *hand;

    public:
        //Shares access to game for convenience 
        friend class Game;
        Person(string name){this->name=name;};
        ~Person(){delete hand; hand=nullptr;};
        //Getters
        string getName(){return name;};
        string getStatus(){return status;};
        //Makes class abstract
        virtual void printInfo()=0;
};
#endif /* PERSON_H */
