/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  To allow for documentation of individual rounds of a game mode. Also allows for use to reuse when we add diffrent game modes like roulette
 */

#ifndef ROUND_H
#define ROUND_H

using namespace std;
#include "game.h"

class Round{
    private:
        string playerName, dealerName;
        float payOut;
    public:
        Round(Player *player, Dealer *dealer);
        string getDealerName(){return dealerName;};
        double getPayOut(){return payOut;};
};

#endif /* ROUND_H */

