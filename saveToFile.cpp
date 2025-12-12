/*
 * File:   saveToFile.cpp
 * Author: James Fregeau
 * Created on December 11th, 2025, 4:21 PM
 * To save the games to a file for trackability 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "saveToFile.h"
//Saves the Player, and dealer to file. Also stores the round that was played and how much the player won/ lost
void SaveToFile :: save(const string &file, Player *player, Round round){
    vector<string> data;
    //Player exists boolean
    bool found =false;
    string line, srch;
    ifstream f(file);
    //Player to serach if exists
    srch = "Player: "+player->getName();

    //Need to store the file in a vector for if we need to append the round to an existing player 
    while(getline(f, line)){
        //Overwrites the data of Round if the player already exists
        if(line == srch){
            found = true;
            data.push_back(line);
            getline(f,line);
            //Rounds payout down to nearest int. Shouldnt be an issue because you can only get a decimal as payout if blackjack is hit and it is such a small amount of money
            line += ", {Dealer: "+ round.getDealerName() + "| Payout: " + to_string(static_cast<int>(round.getPayOut()))+"} ";
            data.push_back(line);
        }else{
            data.push_back(line);
        }
    }
    f.clear();
    f.close();
    //if player exists
    if(found){
        //Wipes file and rewrites it with the new data appended to that player
        ofstream f(file, ios::trunc);
        for(int i=0; i<data.size();i++){
            cout<<data[i]<<endl;
            f <<data[i]<<"\n";
        }
    //If player doesnt exist
    }else{
        //Opens the file and just appends it to the end of the file
        ofstream f(file, ios::app);
        f <<"\n"<<srch<<"\n";
        f << "Rounds: {Dealer: "<< round.getDealerName() << ", Payout: " << round.getPayOut()<<"} ";
    }
    f.close();
}
