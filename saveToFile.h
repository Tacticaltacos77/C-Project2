/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  To allow for documentation of individual rounds of a game mode. Also allows for use to reuse when we add diffrent game modes like roulette
 */

#ifndef SAVETOFILE_H
#define SAVETOFILE_H_H

using namespace std;
#include "game.h"
#include "round.h"
class SaveToFile{
    public:
        static void saveToFile(string file, Player *player, Round round);
};

#endif /* ROUND_H */

