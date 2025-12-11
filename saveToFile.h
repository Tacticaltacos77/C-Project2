/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  To allow for documentation of individual rounds of a game mode. Also allows for use to reuse when we add diffrent game modes like roulette
 */
#ifndef SAVETOFILE_H
#define SAVETOFILE_H

#include <string>
#include "round.h"
#include "player.h"   // or the correct file where Player is defined

class SaveToFile {
public:
    static void save(const string& file, Player* player, Round round);
};

#endif // SAVETOFILE_H
