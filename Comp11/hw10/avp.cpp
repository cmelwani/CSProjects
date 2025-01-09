/*
 * avp.cpp
 * COMP11 AVP
 */

#include <iostream>
#include "battleground.h"

using namespace std;

const bool STEPWISE = true;

int main(int argc, char *argv[]){
    //check for the correct number of arguments
    if(argc < 3){
        cerr << "ERROR: Expecting an alien army and a predator army as command-line arguments." << endl;
        exit(EXIT_FAILURE);
    }

    BattleGround bg;
    if(bg.setupBattle(argv[1], argv[2])){
        bg.simulate(STEPWISE);
    }

	return 0;
}
