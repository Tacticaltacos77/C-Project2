/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Array Structure Specification
 */

#ifndef HAND_H
#define HAND_H
#include <string>
using namespace std;
#include "card.h"
#include "deck.h"

const int MAXHANDSIZE = 21;
class Player;
class Hand{
    private:
        int value, numCards;
        bool busted, dynamicAce;
        Card **cards;
    public:
        
        Hand();
        Hand(Deck *currDeck);
        void clearHand(); //Clears hand for new round
        void addCardVal(int cardVal); //Adds value of card to hand value
        void printHand();
        void hit();
        void checkBusted();
        void printFirstCard();
        int getNumCards(){return numCards;};
        int getHandValue(){return value;};
        Card *getCard(int i){return cards[i];}
        void setCard(int i, Card *card){cards[i] = card;};
        void setHandVal(int newVal){value =newVal;};
        //Operator Overload

        //Adds the card val to the hand val
        Hand& operator+=(Card& c){
            addCardVal(c.getValue());
            return *this;
        }
        //Subtracts the card val from the hand val
        Hand& operator-=(Card& c){
            value-= c.getValue();
            return *this;
        }
        //These Overloaded Operators make splitting slightly more clean however does add a level of compleexity due to += meaning something diffrent

        //Increments the Hand Size
        Hand& operator++(){
            ++numCards;
            return *this;
        }
        //Decremnets the Hand Size
        Hand& operator--(){
            --numCards;
            return *this;
        }

};

#endif /* CARD_H */

