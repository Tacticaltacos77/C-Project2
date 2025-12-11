/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Array Structure Specification
 */

#ifndef DEALER_H
#define DEALER_H

#include "person.h"

class Dealer : public Person{
    private:
        int standVal;
        bool hidden;
    public:
        friend class Game;
        Dealer(int standVal, string name);
        void playTurn();
        void printInfo();
        void printHiddenHand();
        void resetDealerVars();
        
};

#endif /* DEALER_H */
