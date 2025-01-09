/*
NAME: Cheryl Melwani / cmelwa01
Date: 20th November, 2019
 * alien.h
 * COMP11 AVP
 */

#ifndef ALIEN_H
#define ALIEN_H
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class BattleGround;

class Alien {
  public:
    Alien();
    bool readAlien(ifstream *infile);
    void move(int tank_hgt, int tank_wid);
    void draw(BattleGround *bg);

    //getters and setters
    int getStrength();
    float getVPos();
    float getHPos();
    float getVSpeed();
    float getHSpeed();
    int getHeight();
    int getWidth();
    int getRelease();
    Alien *getNext();
    void setNext(Alien *next);
    void weaken();

    //for debugging
    void print();

  private:
    static const int MAX_DIM = 15;
    static const int DEFAULT_H = 12;
    static const int DEFAULT_W = 15;
    static const int MAX_STRENGTH = 7;
    static const int RELEASE_INTERVAL = 50;
    float MAX_SPEED;

    float v_pos;
    float h_pos;
    float v_speed;
    float h_speed;
    int height;
    int width;
    int strength;
    char image[MAX_DIM][MAX_DIM];
    Alien *next_in;
};

#endif
