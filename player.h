/* 
 * File:   player.h
 * Author: James Fregeau
 * Purpose:  To store player vars and funcs
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

const int NAMEBUFFER = 20;

#include "person.h"


class Player : public Person{
    private:
        float balance, startBalance, payOut;
        int bet, currHand,sWins, sLoses,sTotal, sBlackJacks;
        bool hasHit, canSplit, canDouble, hasSplit, hasDouble, nat21, hasLost, endRound, push;
        Hand  *splitHand;
        
    public:
        friend class Game;
        Player(string name);
        ~Player();
        class InvalidBalance{};
        void printInfo(){};
        bool placeBet();
        void printSplitHand();
        void split();
        void hitDouble();
        void stand();
        void resetPlayerVars();
        float getPayOut(){return payOut;};
        bool hasSplt(){return hasSplit;};
        void setLost(bool lost){hasLost = lost;};
        Hand *getHand(int i){if(i==1)return hand;else return splitHand;};
        void printSessionStats();
};

#endif /* PLAYER_H */

