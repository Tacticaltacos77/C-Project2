/*
 * File:   main.cpp
 * Author: James Fregeau
 * Created on November 7th, 2025, 12:30 AM
 * Created blackjack
 */


//Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
//Headers
#include "game.h"
//Global Constants
const int DEALERSTANDVAL = 17; //Value the dealer will hit until it hand value is greater

const int NORMAL = time(0);
const int TESTSPLIT = 1;
const int TESTDYNAMICACE= 8;
//Function Prototypes
Game::Game(Player *player){
    
    srand(NORMAL);
    //Store player
    this->player = player;
    
    //Create deck
    deck = new Deck();
    
    //Can add a load dealer later to have multiple dealers
    dealer = new Dealer(DEALERSTANDVAL, "Logan");
    
    //Aggregation, deck can exist without the same player or dealer. This is for multiplier if added. 
    player->hand->setCurrDeck(deck);
    player->splitHand->setCurrDeck(deck);
    dealer->hand->setCurrDeck(deck);
}
Game :: ~Game(){

}

bool Game::startGame(){
    //Resets game variables
    player->placeBet();
    //Game logic here
    gameLoop();
    return true;
}
//The game logic once player has placed a bet

void Game :: gameLoop(){
    //Dish out cards+
    starterCards();
    playerTurn();
    if(!player->hasLost){
        dealerTurn();
    }
    payOut();
}
void Game :: printPlayerDecisionTree(){
    printHands();
    if(!player->hasLost){
        cout<<"What will you do? "<<endl;
        cout<<"Hit/stand";
        if(!player->hasHit){
            //Can only double if player has enough money and they havent hit yet
            if(player->balance >=player->bet*2){
                cout<<"/double";
                player->canDouble = true;
            }//Split
            if(player->hand->getCard(0)->getValue()==player->hand->getCard(1)->getValue()){
                cout<<"/split";
                player->canSplit = true;
            }else{
                player->canSplit = false;
            }
            player->hasHit = true;
        }else player->canDouble = false;
    }else{
        cout<<"You have busted. "<<endl;
    }      
}

void Game :: playerTurn(){
    string userInp;
    do{
        printPlayerDecisionTree();
        cout<<endl;
        bool acceptedInp = false;  
        //Actual player decison logic
        do{
            cin>>userInp;
            if(player->canDouble && (userInp =="Double"||userInp=="double")){
                //Double logic
                acceptedInp = true;
                player->hitDouble();
            }else if(player->canSplit == true &&(userInp =="Split"||userInp=="split")){
                //Split logic
                acceptedInp = true;
                player->split();
               
            }else if(userInp=="hit"||userInp=="Hit"){
                //Hit logic
                acceptedInp = true;
                player->hasHit = true;
                player->canDouble = false;
                player->canSplit = false;
                player->nat21 = false;
                player->hand->hit();
            }else if(userInp=="Stand"||userInp=="stand"){
                //Stand logic
                acceptedInp = true;
                //If stand while split go next hand else start the endRound or move next hand
                player->stand();
            }
        }while(!acceptedInp);
    }while(!player->endRound);
}

void Game :: dealerTurn(){ 
    int bestPlrHandVal;
    if(player->nat21){
        bestPlrHandVal = 21;
    }else if(player->hasSplit){
        if(player->hand->getHandValue()>player->splitHand->getHandValue()){
            bestPlrHandVal = player->hand->getHandValue();
        }else{
            bestPlrHandVal = player->splitHand->getHandValue();
        }
    }else{
        bestPlrHandVal = player->hand->getHandValue();
    }
    //Dealer plays until over the stand val or if the players value is higher than dealers
    while(dealer->hand->getHandValue()<dealer->standVal || bestPlrHandVal >dealer->hand->getHandValue()){
        dealer->hand->hit();
        dealer->hand->checkBusted();
        printHands();
    }
}
void Game :: printHands(){
    cout <<"=================================="<< endl;
    cout <<"Dealer's Hand:"<<endl;
    if(dealer->hidden){
        dealer->hand->printFirstCard();
    }else{
        dealer->hand->printHand();
    }
    cout <<"----------------------------------"<< endl;
    if(player->hasSplit){
        cout<<"Player's hands"<<endl;
        player->printSplitHand();
    }else{
        cout<<"Player's hand"<<endl;
        player->hand->printHand();
    }   
    cout <<"=================================="<< endl;
}
void Game :: resetAllGameVars(){
    player->resetPlayerVars();
    dealer->resetDealerVars();    
}
void Game :: payOut(){
    float multi;
    if(player->push)return;
    else if(!player->hasLost){
        if(player->nat21){
            multi = 1.5;
        }else multi =1;
    }else{
        multi =-1;
    }
    player->payOut = player->bet * multi;
    player->balance+=player->payOut;
}
void Game :: starterCards(){
    player->hand->hit();
    player->hand->hit();
    dealer->hand->hit();
    dealer->hand->hit();
}
//Sets game flags for currhand and has lost
void Game :: checkPlayerStatus(){
    if(!player->hasSplit &&  player->hand->getBusted()){
        player->hasLost =true;  
    }else{
        if (player->hand->getBusted() && player->splitHand->getBusted()){
            player->hasLost ==true;
        }else if(player->hand->getBusted()&&player->currHand==1)player->currHand =2;
    }
}