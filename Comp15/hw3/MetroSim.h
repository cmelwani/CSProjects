/* Cheryl Melwani (cmelwa01)
 * Feb 12, 2020
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Put any other necessary includes here


// Put any other structs you need here
struct Station {
    string name;
    PassengerQueue passenger_queue;
};

class MetroSim
{
public:
    MetroSim();
    void openFile(string filename);
    void readFile(ifstream *infile);
    void addPassenger(int from, int to);
    void metroMove(ofstream &outfile);
    void readInputFile(string filename, ofstream &outfile);
    void readCinFile(ofstream &outfile);
    void print();

private:
    vector<Station> station_array;
    vector<PassengerQueue> train;
    int passenger_id;
    int curr_station;
};

#endif
