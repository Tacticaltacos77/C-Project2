#include <iostream>
using namespace std;

#include "player.h"
//Constructor
Hand::Hand(){
    curDeck = nullptr;
    cards = new Card*[MAXHANDSIZE];
    //Initialize all card pointers to nullptr
    for(int i = 0; i < MAXHANDSIZE; i++){
        cards[i] = nullptr;
    }
    numCards =0;
    value =0;
    busted = false;
    dynamicAce = false;
}
//Clears the hand of cards 
void Hand::clearHand(){
    for(int i=0;i<numCards;i++){
        cards[i]=nullptr;
    }
    numCards =0;
    value =0;
    busted = false;
    dynamicAce = false;
}  

//Actually adds the the card value to the hand. Includes ace logic and busted logic
void Hand::addCardVal(int cardVal) {
    if (cardVal == 11) {
        if (value + 11 > 21) {
            value += 1;
        } else {
            value += 11;
            dynamicAce =true;  // sets this flag to true so that 11 can be compressed to 1 if need to
        }
    } else {
        value += cardVal;
    }
    //Ace compression
    if(dynamicAce && value > 21) {
        value -= 10;
        dynamicAce =false;//sets to false so that it doesnt happen when isnt suppsoe to
    }
    ++numCards;
    checkBusted();
}
//Checks to make sure that busted flag is set if the value is above 21
void Hand::checkBusted(){
    if(value>21){
        busted = true;
    }
}

//Prints the first cards of the Hand and its value as the total
//For the dealer print 
void Hand::printFirstCard(){
    cout<<cards[0]->getSymbol()<<" H";
    cout<<endl;
    cout<<"Total: "<<cards[0]->getValue()<<endl;
}
//Prints the selected Hand
void Hand::printHand(){
    for(int i=0;i<numCards;i++){
        cout<<cards[i]->getSymbol()<<" ";
    }
    cout<<endl;
    cout<<"Total: "<<value;
    if(busted){
        cout<<" Busted. ";
    }
    cout<<endl;
}
//Adds the card to the hand and adds it to the handvalue 
void Hand::hit(){
    Card *card = curDeck->removeCardFromDeck();
    cards[numCards] = card;
    //addCardVal handles the increment
    addCardVal(card->getValue());
}
