/*
 * File:   game.cpp
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
#include "saveToFile.h"
#include "game.h"
//Global Constants

//Default file name
const string fileName = "out.txt";
//Value the dealer will hit until it hand value is greater
const int DEALERSTANDVAL = 17; 
//3 is for Nat21
const int NORMAL = time(0);
const int TESTSPLIT = 1;
const int TESTDYNAMICACE= 8;

//Constructor
Game::Game(Player *player){
    //Sets the seed
    srand(14);
    //Store player in the game object for easy access
    this->player = player;
    
    //Create deck
    deck = new Deck();
    
    //Can add a load dealer later to have multiple dealers
    dealer = new Dealer(DEALERSTANDVAL, "Logan");
    
    //Aggregation, deck can exist without the same player or dealer. This is for multiplier if added.
    //Sets the current deck for each hand for easy access 
    player->hand->setCurrDeck(deck);
    player->splitHand->setCurrDeck(deck);
    dealer->hand->setCurrDeck(deck);
    resetAllGameVars();
}

//deconstructor
Game :: ~Game(){
    delete dealer;
    delete deck;
}

//A group function for the begining of the game //idk if these two funcs are necassary but condense stuff and group it in a understanable name
bool Game::startGame(){
    player->placeBet();
    //Game logic here
    gameLoop();
    return true;
}


//A group function
void Game :: gameLoop(){
    //Dish out cards+
    starterCards();
    playerTurn();
    if(!player->hasLost){
        dealerTurn();
    }
    payOut();
    Round rnd = Round(player, dealer);
    SaveToFile::save(fileName, player, rnd);
    resetAllGameVars();
}

//Prints all player options based on flags. ONLY PRINTS DOESNT HANDLE THE LOGIC
void Game :: printPlayerDecisionTree(){
    printHands();
    if(!player->hasLost){
        if(!player->hasSplit){
            cout<<"What will you do? "<<endl;
        }else if(player->currHand == 1){
            cout<<"What will you do for the first hand"<<endl;
        }else{
             cout<<"What will you do for the second hand"<<endl;
        }
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

//Handles all the players turn logic and loop
void Game :: playerTurn(){
    string userInp;
    do{
        //Prints what the player can do based on the players flags
        printPlayerDecisionTree();
        cout<<endl;
        bool acceptedInp = false;  
        //Actual player decison logic loop
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
                //Hit logic sets flags for options that are no longer possible
                acceptedInp = true;
                player->hasHit = true;
                player->canDouble = false;
                player->canSplit = false;
                player->nat21 = false;
                //Makes sure the right hand is hit if the player has split
                if(player->currHand==1) player->hand->hit();
                else player->splitHand->hit();
            }else if(userInp=="Stand"||userInp=="stand"){
                //Stand logic
                acceptedInp = true;
                //If stand while split go next hand else start the endRound or move next hand
                player->stand();
            }
        }while(!acceptedInp);
        checkPlayerStatus();
    }while(!player->endRound);
}

//Handles all the dealers turn logic and loop
void Game :: dealerTurn(){ 
    int bestPlrHandVal;
    dealer->hidden =false;
    if(player->nat21){
        bestPlrHandVal = 21;
    }else if(player->hasSplit){
        if(player->hand->getHandValue()>player->splitHand->getHandValue() && player->hand->getBusted()==false){
            bestPlrHandVal = player->hand->getHandValue();
        }else{
            bestPlrHandVal = player->splitHand->getHandValue();
        }
    }else{
        bestPlrHandVal = player->hand->getHandValue();
    }
    //Dealer plays until over the stand val or if the players value is higher than dealers
    printHands();
    while(dealer->hand->getHandValue()<dealer->standVal || bestPlrHandVal >dealer->hand->getHandValue()){
        dealer->hand->hit();
        dealer->hand->checkBusted();
        printHands();
    }
    if(bestPlrHandVal==dealer->hand->getHandValue())player->push =true;
    else if(dealer->hand->getBusted()) player->hasLost = false;
    else if(bestPlrHandVal <dealer->hand->getHandValue())player->hasLost =true;

}

//Prints both players hands and also handles split hand output
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

//Resets the variables so eveything works correctly
void Game :: resetAllGameVars(){
    player->resetPlayerVars();
    dealer->resetDealerVars();    
}

//Decides amount to pay player based on if they won or lost or got a blackjack
void Game :: payOut(){
    float multi, temp;

    if(player->push){
        cout<<"Push. Your money is returned. Total returned: $"<<player->bet<<endl<<"Balance: $"<<player->balance<<endl;
        return;
    }else if(!player->hasLost){
        if(player->nat21){
            multi = 1.5;
        }else multi =1;
        temp = player->bet;
        cout<<"Congratulations YOU WON! Total Winnings: $";
    }else{
        multi =-1;
        cout<<"You lose. Losings: $";
        temp = 0;
    }
    player->payOut+= player->bet * multi;
    if(!player->push)player->balance+=player->payOut;
    
    cout<<player->payOut+temp<<endl<<"Balance: $"<<player->balance<<endl;
}

//Hands out the two set of starter cards 
void Game :: starterCards(){
    player->hand->hit();
    player->hand->hit();
    dealer->hand->hit();
    dealer->hand->hit();
}

//Sets game flags for currhand and has lost
void Game :: checkPlayerStatus(){
    //If player hasnt split and busted
    if(!player->hasSplit &&  player->hand->getBusted()){
        player->hasLost =true;  
        player->endRound = true;
    }else{
        //If player has split and lost both hands
        if (player->hand->getBusted() && player->splitHand->getBusted()){
            player->hasLost ==true;
        //If players first hand busts move them to second hand
        }else if(player->hand->getBusted()&&player->currHand==1)player->currHand =2;
        //if the second hand busts end the round
        else if(player->splitHand->getBusted()){
            player->endRound = true;
        }
    }
}