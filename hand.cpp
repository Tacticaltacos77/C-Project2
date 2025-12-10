#include <iostream>

using namespace std;

#include "hand.h"
Hand::Hand(){
    cards = new Card*[MAXHANDSIZE];
    numCards =0;
    value =0;
    busted = false;
    dynamicAce = false;//If true that means an ace can be collapsed to equal 1
}
void Hand::clearHand(){
    for(int i=0;i<numCards;i++){
        cards[i]=nullptr;
    }
    numCards =0;
    value =0;
    busted = false;
    dynamicAce = false;
}  
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
    cout<<"Total: "<<value<<endl;
}
