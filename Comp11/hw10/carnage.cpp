/*
 * carnage.cpp
 * COMP11 AVP
 */

#include <iostream>
#include <stdio.h>
#include "carnage.h"
#include "battleground.h"
#include "termfuncs.h"

using namespace std;

//Carnage contstructor
Carnage::Carnage(){
    string img = "   .      .    . O   O 0           0 00 O   .   O00  00OO . .  0 00000        O 00  0 O         O0   .      .    O                 .   ";
    int index = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[i][j] = img[index];
            index++;
        }
    }

    v_pos = 0.0;
    h_pos = 0.0;
    v_speed = 1.0;
    h_speed = 0.0;
    next_in = nullptr;
}

//setter: sets the position of the carnage
void Carnage::setPos(float v_pos, float h_pos){
    this->v_pos = v_pos;
    this->h_pos = h_pos;   
}

//setter: sets the next carnage 
void Carnage::setNext(Carnage *next){
    next_in = next;
}

//getter: returns the vertical speed of the carnage
float Carnage::getVSpeed(){
    return v_speed;
}

//getter: returns the horizontal speed of the carnage
float Carnage::getHSpeed(){
    return h_speed;
}

//getter: returns the height of the carnage
int Carnage::getHeight(){
    return HEIGHT;
}

//getter: returns the width of the carnage
int Carnage::getWidth()
{
    return WIDTH;
}

//getter: returns the next in the list
Carnage *Carnage::getNext(){
    return next_in;
}

//updates the position based of the carnage based on it's vertical speed
void Carnage::move(int bgHeight, int bgWidth){
    (void)bgWidth;
    if(v_pos > bgHeight){
        return;
    }

    v_pos = v_pos + v_speed;
    h_pos = h_pos + h_speed;
}

//draws the carnage on the provided BattleGround canvas
void Carnage::draw(BattleGround *bg){
    int  row = (int) v_pos;
    int  col = (int) h_pos;
    int  i = 0, j = 0; 
    bool flip = false;

    if(row > bg->getHeight()){
        return;
    }
    
    for (int r = row; r < (row + getHeight()) && r < bg->getHeight(); r++, i++) {
        for (int c = col; c < (col + getWidth()); c++, j++) {
            if (image[i][j] != ' ') {
                bg->updateAt(r % bg->getHeight(),
                           c % bg->getWidth(),
                           image[i][j]);

                if(flip){
                    bg->colorAt(r % bg->getHeight(),
                           c % bg->getWidth(),
                           'r');
                }else{
                    bg->colorAt(r % bg->getHeight(),
                           c % bg->getWidth(),
                           'g');
                }
                flip = !flip;
            }
        }
        j = 0;
    }
}

//prints the carnage (for debugging/testing)
void Carnage::print(){
    cout << "Carnage: " << endl;
    cout << " height: " << HEIGHT << endl
         << "  width: " << WIDTH << endl
         << "  v_pos: " << v_pos << endl
         << "  h_pos: " << h_pos << endl
         << "v_speed: " << v_speed << endl
         << "h_speed: " << h_speed << endl;
         
    cout << "  image:\n";
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            cout << image[r][c];
        }
        cout << endl;
    }
    cout << endl;
}



