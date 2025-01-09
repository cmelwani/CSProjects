/*
 * predator.cpp
 * COMP11 AVP
 */

#include "predator.h"
#include "battleground.h"

using namespace std;

//Predator contstructor
Predator::Predator(){
    for (int i = 0; i < MAX_DIM; i++) {
        for (int j = 0; j < MAX_DIM; j++) {
            image[i][j] = '$';
        }
    }

    MAX_SPEED = 1.0;
    v_pos = 0.0;
    h_pos = 0.0;
    v_speed = 0.0;
    h_speed = 0.0;
    height = 0;
    width = 0;
    strength = 0;
    next_in = nullptr;
}

//read in an Predator from the provided data file
bool Predator::readPredator(ifstream *infile){
    string data_type;
    ifstream *read_from;
    ifstream pfile;
    
    //make sure that we have the right army file
    (*infile) >> data_type;    
    if ((!(*infile).eof()) && (data_type == "predator")) {
        (*infile) >> data_type;

        //load in the default predator image
        if(data_type == "d"){
            height = DEFAULT_H;
            width = DEFAULT_W;

            pfile.open("predator.default");
            if (pfile.fail()) {
                cerr << "ERROR: Error opening file, please check " 
                    << "predator.default" << endl;
                exit(EXIT_FAILURE);
            }

            read_from = &pfile;
        //read the custom predator image
        }else{
            (*infile) >> height >> width;
            read_from = infile;
        }

        //read in the remaining predator fields
        (*infile) >> v_pos >> h_pos;
        (*infile) >> v_speed >> h_speed;
        (*infile) >> strength;
        (*infile).ignore();

        //make sure the predator meets spec
        float speed = sqrt(pow(v_speed, 2.0) + pow(h_speed, 2.0));
        if(speed > MAX_SPEED || height > MAX_DIM || width > MAX_DIM
            || strength > MAX_STRENGTH){
            cerr << "INVALID PREDATOR: Exiting..." << endl;
            exit(3);
        }

        //populate the image array
        string line;
        for(int i = 0; i < height; i++){
            getline((*read_from), line);
            int length = line.length();

            for (int j = 0; j < length; j++) {
                image[i][j] = line[j];
            }
        }
        
        return true;
    }
    return false;   
}

//updates the predator's position based on it's vertical and horizontal speed
void Predator::move(int bgHeight, int bgWidth){
    v_pos = v_pos + v_speed;
    h_pos = h_pos + h_speed;
    
    if ((h_speed < 0) && (h_pos < 0)) {
        h_pos = bgWidth + h_pos;
    } else if ((h_speed > 0) && (h_pos >= bgWidth)) {
        h_pos = h_pos - bgWidth;
    }
    
    if ((v_speed < 0) && (v_pos < 0)) {
        v_pos = bgHeight + v_pos;
    } else if ((v_speed > 0) && (v_pos >= bgHeight)) {
        v_pos = v_pos - bgHeight;
    }
}

//draws the predator on the provided BattleGround canvas
void Predator::draw(BattleGround *bg){
    int  row = roundf(v_pos);
    int  col = roundf(h_pos);
    int  i = 0, j = 0; 
    
    for (int r = row; r < (row + getHeight()); r++, i++) {
        for (int c = col; c < (col + getWidth()); c++, j++) {
            if (image[i][j] != '$') {
                bg->updateAt(r % bg->getHeight(),
                           c % bg->getWidth(),
                           image[i][j]);
            }
        }
        j = 0;
    }
}

/*--------------------------------------------------------------------*/
/*                        Getters and setters                         */
/*--------------------------------------------------------------------*/

//getter: returns the predator's strength
int Predator::getStrength(){
    return strength;
}

//getter: returns the predator's vertical position
float Predator::getVPos(){
    return v_pos;
}

//getter: returns the predator's horizontal position
float Predator::getHPos(){
    return h_pos;
}

//getter: returns the predator's vertical speed
float Predator::getVSpeed(){
    return v_speed;
}

//getter: returns the predator's horizontal speed
float Predator::getHSpeed(){
    return h_speed;
}

//getter: returns the predator's height
int Predator::getHeight(){
    return height;
}

//getter: returns the predator's width
int Predator::getWidth(){
    return width;
}

//getter: returns the interval before the next predator is released
int Predator::getRelease(){
    return RELEASE_INTERVAL;
}

//getter: returns the next predator to be released
Predator *Predator::getNext(){
    return next_in;
}

//setter: sets the next predator to be released
void Predator::setNext(Predator *next){
    next_in = next;
}

//setter: decrements the predator's strength after a battle
void Predator::weaken(){
    strength--;
}

/*--------------------------------------------------------------------*/
/*           Print function to help with any debugging                */
/*--------------------------------------------------------------------*/

//prints the predator (for debugging/testing)
void Predator::print(){
    cout << "Predator: " << endl;
    cout << "  height: " << height << endl
         << "   width: " << width << endl
         << "   v_pos: " << v_pos << endl
         << "   h_pos: " << h_pos << endl
         << " v_speed: " << v_speed << endl
         << " h_speed: " << h_speed << endl;
         
    cout << "   image:\n";
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            cout << image[r][c];
        }
        cout << endl;
    }
    cout << endl;
}



