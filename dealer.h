/* 
 * File:   dealer.h
 * Author: Games Fregeau
 * Purpose:  Dealer header file
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
        ~Dealer();
        void playTurn();
        void printInfo();
        void resetDealerVars();     
        void introduce();
};

#endif /* DEALER_H */
