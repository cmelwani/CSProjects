/*
phone_tree.cpp
Purpose: read an input file and finds out whether the phone tree of moms works
to call every mom in the input file. Outputs to the user whether that tree
is bungled or it works. If it works, the program also outputs the first mom
that should be called and the total time it will take for all the moms to be
called.
Created by Cheryl Melwani (cmelwa01)
Date: Oct 17, 2019
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Mom {
  string name;
  int time;
  Mom *next_mom;
  string next_mom_name;
  bool been_called;
};

int find_num_moms(string filename);
Mom *read_file(string filename, int *num_moms);
void fill_moms_array(Mom *moms, int num_moms);
void find_time_and_mom(Mom *moms, int num_moms);

/* PURPOSE:
To call the other functions and to check if the input file opened properly.
*/
int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "ERROR: No filename provided as an argument" << endl;
    exit(EXIT_FAILURE);
  }

  int num_moms = find_num_moms(argv[1]);
  Mom *moms = read_file(argv[1], &num_moms);
  find_time_and_mom(moms, num_moms);
  }

int find_num_moms(string filename) {
  int num_moms = 0;
  ifstream infile(filename.c_str());
  infile >> num_moms;
  return num_moms;
}

/* PURPOSE:
Reads in the data in the file and creates an array of structs with a size that
is equal to the number of moms in the input file. Calls fill_moms_array to make
sure array of moms structs don't hold garbage values. After, the function
fills the array of mom structs with information from the input file.
*/
Mom *read_file(string filename, int *num_moms) {
  ifstream infile(filename.c_str());

  if (infile.fail()) {
    cerr << "ERROR: Error opening file - ";
    cerr << "please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
  }
  infile >> *num_moms;
  if (infile.fail()) {
    cerr << "ERROR: Reading the number of moms failed." << endl;
    exit(EXIT_FAILURE);
  }

  Mom *new_moms = new Mom[*num_moms];
  fill_moms_array(new_moms, *num_moms);

  string name;
  int time;
  string next_mom_name;

  for(int i = 0; i < *num_moms; i++) {
    infile >> name >> time >> next_mom_name;
    new_moms[i].name = name;
    new_moms[i].time = time;
    new_moms[i].next_mom_name = next_mom_name;
  }

  for(int i = 0; i < *num_moms; i++) {
    for(int j = 0; j < *num_moms; j++) {
      if(new_moms[i].next_mom_name == new_moms[j].name) {
        new_moms[i].next_mom = &new_moms[j];
      }
    }
  }
  return new_moms;
}

/* PURPOSE:
Initialize every element of the mom struct in the array to get rid of any
garbage value. */
void fill_moms_array(Mom *moms, int num_moms) {
  for (int i = 0; i < num_moms; i++) {
    moms[i].name = "";
    moms[i].time = 0;
    moms[i].next_mom = nullptr;
    moms[i].been_called = false;
  }
}

/* PURPOSE:
1. checks whether all the moms have been called, and finds the
first mom that should be called if the phone tree works.
2. finds the total time taken for the phone tree to work.
3. outputs whether the tree works or not and how long it will take to the user.
*/
void find_time_and_mom(Mom *moms, int num_moms) {
  int count = 0;
  Mom *current_mom;
  bool being_success = false;
  bool works = true;
  int total_time = 0;

  for (int i = 0; i < num_moms; i++) {
    current_mom = &moms[i];

    for (int j = 0; j < num_moms; j++) {
      current_mom = &moms[j];
      current_mom->been_called = false;
    }

    current_mom = &moms[i];
    current_mom->been_called = true;

    while (count < num_moms) {
      if(count != num_moms - 1) {
        total_time += current_mom->time;
      }
      current_mom = current_mom->next_mom;
      current_mom->been_called = true;
      count++;
    }

    for (int i = 0; i < num_moms; i++) {
      if (moms[i].been_called == false) {
        works = false;
        break;
      }
    }

    if (works == true) {
      cout << "Starting with " << moms[i].name << " the phone tree will succeed
      in " << total_time << " seconds!" << endl;
      being_success = true;
    }
    total_time = 0;
    count = 0;
    works = true;
  }

  if(being_success == false) {
    cout << "Another bungled phone tree, Sharon." << endl;
  }
}
