#include <iostream>

using namespace std;

#include "player.h"
//Constructor
Player::Player(string name):Person(name){
    //gets player name
    
    bool accInp =true;

    cout<<"Enter a starting balance: ";
    cin>>balance;
    if(balance <0) throw InvalidBalance();
        

    startBalance = balance;
   
    //Creates a hand with a size that would be big enough(21 is overkill but if you were to increase the decksize this would allow 21 aces)
    hand = new Hand();


    //For the second hand if player splits
    splitHand = new Hand();
}
bool Player::placeBet(){
    cout<<"Current balance: $"<<balance<<endl;
    cout<<"Enter an amount to bet: ";
    do{
        cin>>bet;
        cout<<endl;
        //Makes sure that if the user inputs a non int the program wont break.
        if(cin.fail()){
            cin.clear();
            cin.ignore();
        }
        //If user doesnt want to bet anymore
       
        if(bet==0){
            return false;
        }else if(bet > balance){
            cout<<"Player doesn't have enough money to bet that"<<endl;
        }

    }while(bet<0||bet > balance);
    cout<<endl;
    
    return true;
}
//Spefic print for the player if the player has split.
//Is formatted to put both hands on screen
void Player::printSplitHand(){
    for(int i=0;i<hand->getNumCards();i++){
        cout<<hand->getCard(i)->getSymbol()<<" ";
    }
    cout<<" | ";
    for(int i=0;i<splitHand->getNumCards();i++){
        cout<<splitHand->getCard(i)->getSymbol()<<" ";
    }
    cout<<endl;
    cout<<"First Hand Total: "<<hand->getHandValue()<<endl;
    cout<<"Second Hand Total: "<<splitHand->getHandValue()<<endl;
}
void Player::split(){
    //Split logic
    //sets flags
    hasSplit = true;
    canSplit =false;
    canDouble = false;
    //Moves card form orignal hand to split hand
    splitHand->setCard(0, hand->getCard(1));
    splitHand->setHandVal(hand->getCard(1)->getValue());
    hand->setHandVal(hand->getCard(0)->getValue());
    hand->setCard(1,nullptr);
    //corrects players hand number of cards
    --hand;
    ++splitHand;
}
void Player::hitDouble(){
    bet*=2;
    hand->hit();
    hand->checkBusted();
}
void Player :: stand(){
    if(hasSplit ==true && currHand==1){
        currHand =2;
    }else endRound = true;
}
void Player :: resetPlayerVars(){
    hasHit= false;
    canSplit= false;
    canDouble = false;
    hasSplit = false;
    hasDouble = false; 
    nat21 = false;
    endRound =false; 
    hasLost = false;
    push = false;
    payOut = 0;
    currHand =1;
}

