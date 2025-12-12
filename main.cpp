#include <iostream>

using namespace std;

#include "game.h"

//Execution begins here
int main(){
    //Maybe add player selection later or load create player or something
    string name;
    cout<<"Welcome enter your name: "<<endl;
    cin >>name;
    

    //Create player outside game to allow for easier time to add diffrent types of games later.(Not tied to blackjack)
    //Will still have to rework the game class to be an Abstract and fork into blackJack and other games
    bool accInp = false;
    Player *player;
    //Creates the Player OBJ and makes sure they have an acceptable balance
    do{
        try{
            player = new Player(name);
            accInp =true;
            
        }catch(Player::InvalidBalance){
            cout<<"The balance you entered is invalid. Balance must $0 or more. Try again."<<endl;
        }
    }while(!accInp);
    //Player Continue check var
    string cont = "Yes";
    //Makes and starts the game with the player
    Game game = Game(player);
    do{
        game.startGame();
        //Continue check
        cout<<"Do you want to play again?"<<endl;
        cin >> cont;
    }while(cont=="Yes"||cont=="yes");
    //Prints sessions stats
    player->printSessionStats();
    //Cleanup
    //Alot of the ptrs are deleted by game when exiting scope
    delete player;

    return 0;
}
