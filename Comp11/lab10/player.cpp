/*
 * player.cpp
 * COMP11 Red Rover
 */

#include "player.h"

using namespace std;

Player::Player(string name, int strength){
    this->name = name;
    this->strength = strength;
}

string Player::getName(){
    return name;
}

int Player::getStrength(){
    return strength;
}

Player *Player::getNext(){
    return next_player;
}

void Player::setNext(Player *next_player){
    this->next_player = next_player;
}