#ifndef HAND_H
#define HAND_H

#include "deck.h"
//Constant
const int MAXHANDSIZE = 21;

class Hand{
    private:
        int value, numCards;
        bool busted, dynamicAce;
        Card **cards;
        Deck *curDeck;
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
        void setCurrDeck(Deck *deck){
            curDeck = deck;
        }
        bool getBusted(){return busted;};

        //Overloaded operators 
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

