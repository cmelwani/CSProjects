/*
 * playground.cpp
 * COMP11 Red Rover
 */

#include "playground.h"

using namespace std;

//Playground constructor
PlayGround::PlayGround(){
    team_1 = nullptr;
    team_2 = nullptr;

    makeTeams();
}

//Simulates the red rover game until a team wins
void PlayGround::playRover(){
    bool cont_game = true;
    bool team_one_runs = true;
    string runner, target;

    printGrounds();

    //Loop until one team wins
    while(cont_game){
        if(team_one_runs){
            cout << "Who will be running from Team 1: ";
            cin >> runner;
            cout << "Who will they be running at from Team 2: ";
            cin >> target;
        }else{
            cout << "Who will be running from Team 2: ";
            cin >> runner;
            cout << "Who will they be running at from Team 1: ";
            cin >> target;
        }

        // run(team_one_runs, runner, target);
        printGrounds();
        team_one_runs = !team_one_runs;

        //Check to see if one of the teams has won
        if(team_1 == nullptr){
            cout << "GAME OVER: Team 2 has won!" << endl;
            cont_game = false;
        }
        if(team_2 == nullptr){
            cout << "GAME OVER: Team 1 has won!" << endl;
            cont_game = false;
        }
    }
}

void PlayGround::run(bool team_one_runs, string runner, string target){
  Player *curr_r = team_1;
  Player *curr_p = team_2;
  Player *trail_r = nullptr;
  Player *trail_p = nullptr;
  Player *temp = nullptr;
  int runner_strength;
  int target_strength;

  while(curr_r->getName() != nullptr) {
    if(curr_r->getName() == runner) {
      runner_strength = curr_r->getStrength();
    }
    trail_r = curr_r;
    curr_r = curr_r->getNext();
  }

  while(curr_p->getName() != nullptr) {
    if(curr_p->getName() == target) {
      target_strength = (curr_p->getStrength() + curr_p->getNext()->getStrength()) / 2;
    }
    trail_p = curr_p;
    curr_p = curr_p->getNext();
  }

  if(runner_strength > target_strength) {
      temp = curr_p->getNext();
      curr_p->getNext() = curr_r->getNext();
      curr_r->getNext() = curr_p;
      if(curr_p != team_1){
        trail_p = temp;
      } else {
      team_1 = temp;
      }
  }
    /*------------------------------------------*/
    /*                                          */
    /*          YOUR CODE GOES HERE!            */
    /*                                          */
    /*------------------------------------------*/
}

//Prints the current state of the two teams
void PlayGround::printGrounds(){
    //Print Team 1
    Player *curr_p = team_1;
    cout << endl << "Team 1:  ";
    while(curr_p != nullptr){
        cout << curr_p->getName();

        if(curr_p->getNext() != nullptr){
            cout << "--";
        }

        curr_p = curr_p->getNext();
    }
    cout << endl << endl;

    //Print Team 2
    curr_p = team_2;
    cout << "Team 2:  ";
    while(curr_p != nullptr){
        cout << curr_p->getName();

        if(curr_p->getNext() != nullptr){
            cout << "--";
        }

        curr_p = curr_p->getNext();
    }
    cout << endl << endl;
}

void PlayGround::makeTeams(){
    team_1 = makeTeam(1);
    team_2 = makeTeam(2);
}

//Reads all players from a given team into a linked list
Player *PlayGround::makeTeam(int team_num){
    //Check for error opening file
    ifstream infile("rover.teams");
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check "
             << "rover.teams" << endl;
        exit(EXIT_FAILURE);
    }

    int team, strength;
    string name;
    Player *start = nullptr;
    Player *prev = nullptr;

    infile >> team >> name >> strength;
    while (!infile.eof()) {
        //Only add if the player is on the specified team
        if(team == team_num){
            Player *p = new Player(name, strength);

            if(start == nullptr){
                start = p;
                prev = p;
            }else{
                prev->setNext(p);
                prev = p;
            }
        }
        infile >> team >> name >> strength;
    }

    return start;
}

//Free the memory for the specified team
void PlayGround::deleteTeam(Player *team){
    if(team == nullptr){
        return;
    }else{
        deleteTeam(team->getNext());
        delete team;
    }
}

//Playground destructor
PlayGround::~PlayGround(){
    deleteTeam(team_1);
    deleteTeam(team_2);
}
