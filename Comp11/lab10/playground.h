/*
 * playground.h
 * COMP11 Red Rover
 */

#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "player.h"

using namespace std;


class PlayGround {
  public:
    //constructor
    PlayGround();

    //destructor
    ~PlayGround();

    void playRover();
  private:
    //helper functions
    void makeTeams();
    Player *makeTeam(int team_num);
    void printGrounds();
    void run(bool team_one_runs, string runner, string target);
    void deleteTeam(Player *team);

    Player *team_1;
    Player *team_2;
};

#endif