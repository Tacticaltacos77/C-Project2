/* 
 * File:   round.h
 * Author: James Fregeau
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

