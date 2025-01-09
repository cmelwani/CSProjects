/*
 * predator.h
 * COMP11 AVP
 */

#ifndef PREDATOR_H
#define PREDATOR_H
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class BattleGround;

class Predator {
  public:
    Predator();
    bool readPredator(ifstream *infile); 
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
    Predator *getNext();
    void setNext(Predator *next);
    void weaken();

    //for debugging
    void print();

  private:
    static const int MAX_DIM = 20; 
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 15;
    static const int MAX_STRENGTH = 10;
    static const int RELEASE_INTERVAL = 100; 
    float MAX_SPEED; 
        
    float v_pos;
    float h_pos;
    float v_speed;
    float h_speed;
    int height;
    int width;
    int strength; 
    char image[MAX_DIM][MAX_DIM];
    Predator *next_in;
};

#endif