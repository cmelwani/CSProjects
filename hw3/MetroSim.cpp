/* Cheryl Melwani (cmelwa01)
 * Feb 12, 2020
 */


#include "MetroSim.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/* Constructor
Purpose: To initialize the private variables in the class */
MetroSim::MetroSim() {
    curr_station = 0;
    passenger_id = 0;
}

/* Purpose: openFile opens the file and checks if the file for some reason
cannot be opened. It calls the readFile function.
Return: void
Parameter: filename of the text file */
void MetroSim::openFile(string filename) {
  ifstream infile(filename.c_str());
  if (infile.fail()) {
    cerr << " Error: could not open file " << filename;
    exit(EXIT_FAILURE);
  }
  readFile(&infile);
}

/* Purpose: readFile actually reads in the file and populates the station_array
and populates the train vector with empty passenger queues.
Return: void
Parameter: takes the ifstream created in the openFile function */
void MetroSim::readFile(ifstream *infile) {
    istringstream line_stream;
    string line_info;
    getline(*infile, line_info);

    while (!infile->eof()) {
      line_stream.str(line_info);
      Station new_station;
      new_station.name = line_info;
      station_array.push_back(new_station);
      line_stream.clear();
      getline(*infile, line_info);
  }
  for (int i = 0; i < (int)station_array.size(); i++) {
      PassengerQueue new_queue;
      train.push_back(new_queue);
  }
}

/* Purpose: addPassenger adds a passenger to the passenger queue in the station
struct.
Return: void
Parameter: takes in as parameters the arrival and destination station */
void MetroSim::addPassenger(int from, int to) {
    Passenger new_p;
    new_p.from = from-1;
    new_p.to = to-1;
    passenger_id++;
    new_p.id = passenger_id;
    station_array[from-1].passenger_queue.enqueue(new_p);
}

/* Purpose: metroMove moves the train from one station to the next (where
curr_station keeps track of where the train is at). The function enqueue's
people on the train and dequeue's them from the station. Moves the train and
then dequeue's the passengers off the train.
Return: void
Parameter: Takes in the outfile as a parameter */
void MetroSim::metroMove(ofstream &outfile) {
    while (station_array[curr_station].passenger_queue.size() != 0) {
        Passenger curr_p = station_array[curr_station].passenger_queue.front();
        train[curr_p.to].enqueue(curr_p);
        station_array[curr_station].passenger_queue.dequeue();
    }

    if (curr_station == (int)station_array.size()-1) {
        curr_station = 0;
    } else {
        curr_station++;
    }

    while (train.at(curr_station).size() != 0) {
        outfile << "Passenger " << train.at(curr_station).front().id
        << " left train at station " << station_array[curr_station].name << endl;
        train[curr_station].dequeue();
    }
    print();
}

/* Purpose: Reads the command file if the user inputs one.
Return: void
Parameter: takes in the name of the input file and the stream to the output
file */
void MetroSim::readInputFile(string input_file, ofstream &outfile) {
    ifstream input;
    string command, command2;
    input.open(input_file);
    print();
    if (input.fail()) {
        cerr << " Error: could not open file " << input_file;
        exit(EXIT_FAILURE);
    }
    while (!input.eof()) {
        cout << "Command? ";
        input >> command;
        if (command == "m") {
            input >> command2;
            if (command + command2 == "mm") {
                metroMove(outfile);
            } else if (command + command2 == "mf") {
                cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
                break;
            }
        } else if (command == "p") {
            int from, to;
            input >> from;
            input >> to;
            addPassenger(from, to);
            print();
        }
    }
}
/* Purpose: readCinFile reads the commands given by the user if they do not
input a test_command file while running. It keeps on asking for commands
until the user inputs the command m f.
Return: void
Parameter: the output stream to the output file */
void MetroSim::readCinFile(ofstream &outfile) {
    string command, command2;
    bool check = false;
    print();
    while (check == false) {
        cout << "Command? ";
        cin >> command;
        if (command == "m") {
            cin >> command2;
            if (command + command2 == "mm") {
                metroMove(outfile);
            } else if (command + command2 == "mf") {
                cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
                check = true;
            }
        } else if (command == "p") {
            int from, to;
            cin >> from;
            cin >> to;
            addPassenger(from, to);
            print();
        }
    }
}
/* Purpose: print prints out the metro simulation to the user everytime its
called.
Return: void
Parameter: none */
void MetroSim::print() {
    int x = 1;
    cout << "Passengers on the train: " << "{";
    for (int i = 0; i < (int)train.size(); i++) {
        train[i].print();
    }
    cout << "}" << endl;
    for (int i = 0; i < (int)station_array.size(); i++) {
        if (i == curr_station) {
            cout << "TRAIN: ";
        } else {
            cout << "       ";
        }
        cout << "[" << x << "] ";
        cout << station_array[i].name;
        cout << " {";
        station_array[i].passenger_queue.print();
        cout << "}" << endl;
        x++;
    }
}
