#include <iostream>

using namespace std;

#include "game.h"

//Execution begins here
int main(){
    //Maybe add player selection later or load create player or something
    string name;
    cout<<"Welcome enter your name: "<<endl;
    cin >>name;
    
    //Aggregation
    //Create player outside game to allow for easier time to add diffrent types of games later.(Not tied to blackjack)
    bool accInp = false;
    Player *player;
    do{
        try{
            player = new Player(name);
            accInp =true;
            
        }catch(Player::InvalidBalance){
            cout<<"The balance you entered is invalid. Balance must $0 or more. Try again."<<endl;
        }
    }while(!accInp);
    string cont = "Yes";
    Game game = Game(player);
    do{
        game.startGame();
        cout<<"Do you want to play again?"<<endl;
        cin >> cont;
    }while(cont=="Yes"||cont=="yes");
   
    return 0;
}
