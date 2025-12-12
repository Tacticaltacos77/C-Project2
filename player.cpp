/*
 * File:   player.cpp
 * Author: James Fregeau
 * Created on November 7th, 2025, 12:30 AM
 * Created blackjack
 */

#include <iostream>

using namespace std;

#include "player.h"
//Constructor
Player::Player(string name):Person(name){
    bool accInp =true;
    //Gets player balance
    cout<<"Enter a starting balance: ";
    cin>>balance;
    //If player tries to create an object with a negative balance 
    if(balance <0) throw InvalidBalance();
    //Sets start balance for future implmentation of total made 
    startBalance = balance;
   
    //Creates a hand with a size that would be big enough(21 is overkill but if you were to increase the decksize this would allow 21 aces)
    hand = new Hand();
    //For the second hand if player splits
    splitHand = new Hand();
    resetPlayerVars();
    sWins =0;
    sLoses =0;
    sTotal =0;
    sBlackJacks = 0;
}

Player :: ~Player(){
    hand->clearHand();
    splitHand->clearHand();
    delete[] hand;
    hand = nullptr;
    delete[] splitHand;
    splitHand = nullptr;
}

//Makes sure that the players bet amount is enough and if it is can still play at 0 FOR FUN 
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
        //Makes sure the bet amount is above 0
        }else if(bet > balance){
            cout<<"Player doesn't have enough money to bet that"<<endl;
        }

    }while(bet<0||bet > balance);
    cout<<endl;
    
    return true;
}
//Spefic print for the player if the player has split.
//Is formatted to put both hands on screen in a nicly formated way
void Player::printSplitHand(){
    for(int i=0;i<hand->getNumCards();i++){
        cout<<hand->getCard(i)->getSymbol()<<" ";
    }
    cout<<" |  ";
    for(int i=0;i<splitHand->getNumCards();i++){
        cout<<splitHand->getCard(i)->getSymbol()<<" ";
    }
    cout<<endl;
    cout<<"First Hand Total: "<<hand->getHandValue();
    if(hand->getBusted()){
        cout<<" Busted. ";
    }
    cout<<endl;
    cout<<"Second Hand Total: "<<splitHand->getHandValue();
    if(splitHand->getBusted()){
        cout<<" Busted. ";
    }
    cout<<endl;
}

//Player split logic
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
    //Changes hand sizes
    //Need to derefrence to use 
    --*hand;
    ++*splitHand;
}
//Player Double logic
void Player::hitDouble(){
    bet*=2;
    hand->hit();
    hand->checkBusted();
}

//Player stand logic
void Player :: stand(){
    //Swaps hands if on first hand and split otherwise end round
    if(hasSplit ==true && currHand==1){
        currHand =2;
    }else endRound = true;
}
//Resets all player vars to the defualt
void Player :: resetPlayerVars(){
    hand->clearHand();
    splitHand->clearHand();
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
//Prints seesion stats
void Player :: printSessionStats(){
    cout<<"Thanks for playing!"<<endl;
    cout<<"Session stats: "<<endl;
    cout<<"Total Rounds: "<<sTotal<<endl;
    cout<<"Total Wins: "<<sWins<<endl;
    cout<<"Total Loses: "<<sLoses<<endl;
    cout<<"Total BlackJacks: "<<sBlackJacks<<endl;
}