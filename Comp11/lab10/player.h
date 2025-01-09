/*
 * player.h
 * COMP11 Red Rover
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;


class Player {
  private:
    string name;
    int strength; 
    Player *next_player;
  public:
    //constructor
    Player(string name, int strength);

    //getters
    string getName();
    int getStrength();
    Player *getNext();

    //setters
    void setNext(Player *next_player);
};

#endif