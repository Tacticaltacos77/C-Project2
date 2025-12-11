#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "saveToFile.h"
void SaveToFile::saveToFile(string file, Player *player, Round round){
    bool found =false;
    string line, srch;
    fstream f(file, ios::in | ios::out);
    streampos pos;
    srch = "Player: "+player->getName();
    while(getline(f, line)){
        if(line == srch){
            found = true;
            getline(f, line);
            pos = f.tellg();
            break;
        }
        getline(f, line);
    }
    if(found){
        f.seekp(pos);
        f<< line << "Rounds: {Dealer: "<<round.getDealerName()<<", Payout: "<<round.getPayOut()<<" ";
    }else{
        f.clear();
        f.seekp(0, ios::end);
        f <<"\n"<< srch <<"\n" << "Rounds: {Dealer: "<<round.getDealerName()<<", Payout: "<<round.getPayOut()<<" ";
    }
    f.close();
}
