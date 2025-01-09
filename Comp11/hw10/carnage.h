/*
 * carnage.h
 * COMP11 AVP
 */

#ifndef CARNAGE_H
#define CARNAGE_H
#include <iostream>
#include <fstream>

using namespace std;

class BattleGround;

class Carnage {
  public:
    Carnage();

    void setPos(float v_pos, float h_pos);
    void setNext(Carnage *next);
    float getVSpeed();
    float getHSpeed();
    int getHeight();
    int getWidth();
    Carnage *getNext();

    void move(int tank_hgt, int tank_wid);
    void draw(BattleGround *bg);
    void print();
    
  private:
    static const int WIDTH  = 15;
    static const int HEIGHT  = 9;

    float v_pos;
    float h_pos;
    float v_speed;
    float h_speed;
    char image[HEIGHT][WIDTH];
    Carnage *next_in;
};

#endif