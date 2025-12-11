/*
 * File:   saveToFile.cpp
 * Author: James Fregeau
 * Created on November 7th, 2025, 12:30 AM
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
    bool found =false;
    string line, srch;
    ifstream f(file);
    streampos pos;
    srch = "Player: "+player->getName();
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
    //If it isnt found at it to the end
    if(found){
        //Wipes file and rewrites it with the new data appended to that player
        ofstream f(file, ios::trunc);
        for(int i=0; i<data.size();i++){
            cout<<data[i]<<endl;
            f <<data[i]<<"\n";
        }
    }else{
        //Opens the file and just appends it to the end of the file
        ofstream f(file, ios::app);
        f <<"\n"<<srch<<"\n";
        f << "Rounds: {Dealer: "<< round.getDealerName() << ", Payout: " << round.getPayOut()<<"} ";
    }
    f.close();
}
