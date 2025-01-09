// advising.cpp
// Purpose: Query advising bureaucracy
// Written by: Cheryl Melwani (cmelwa01)
// Date: 12 November, 2019

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    string name;
    Node *supervisee_1;
    Node *supervisee_2;
    int advisee_count;
};

const string PRINT = "p";
const string TOTAL = "t";
const string SLACKER = "s";
const string QUIT = "q";

void print_advisees(Node *curr_node, string bureaucracy);
Node *new_node(string name);
Node *read_file(string filename);
Node *find_node(Node *curr_node, string name);
int total_advisees(Node *curr_node);
void query_slacker(Node *curr_node);
void query_quit(Node *curr_node);

int count = 0;

int main(){
  //Prompt the user for the data file name
  string filename;
  cout << "Enter data file name: ";
  cin >> filename;
	Node *boss = read_file(filename);
  //Loop to continually prompt for queries
  string c;
  string name;
  cout << "Enter a query: ";
  while (cin >> c) {
    if (c == PRINT) {
    print_advisees(boss, "");
  }
  else if (c == TOTAL) {
    cin >> name;
    count = 0;
    /* using find node to find the node of the name that the user inputs */
    total_advisees(find_node(boss, name));
    /* if the find_node equals a nullptr that means the name doesn't exist,
    so to account for this edge case find_node should not equal a nullptr.
    If it does then print out that the person doesn't work here */
    if(find_node(boss, name) != nullptr) {
      cout << name << " is responsible for " << count << " advisee(s)."
      << endl;
    } else {
      cout << name << " doesn't work here!" << endl;
    }
  }
  else if (c == SLACKER) {
    query_slacker(boss);
  }
  else if (c == QUIT) {
    query_quit(boss);
    return 0;
  }
  else {
    cout << c << " not recognized." << endl;
  }
  cout << endl << "Enter a query: ";
  }
  return 0;
}

//Print the tree path of every person who has advisees
void print_advisees(Node *curr_node, string bureaucracy){
    //Base Case: If we are at a person who has advisees, print the count
    if(curr_node->advisee_count > 0){
        cout << bureaucracy;
        cout << curr_node->name + "->";
        cout << curr_node->advisee_count << endl;
    /* Recursive Cases: If we are at a person who doesn't have advisees,
    recurse to their subtrees */
    }else{
        if(curr_node->supervisee_1 != nullptr){
            string bureaucracy_left = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_1, bureaucracy_left);
        }

        if(curr_node->supervisee_2 != nullptr){
            string bureaucracy_right = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_2, bureaucracy_right);
        }
    }
}

//Read file and build tree structure, returning root "boss" node
Node *read_file(string filename){
    //Open the given file
    ifstream infile(filename.c_str());
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: "
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    //Read the first line of the file
    string supervisor;
    string supervisee;

    infile >> supervisor;
    infile >> supervisee;
    Node *boss = new_node(supervisor);
    bool first_line = true;

    //Process each line of the file
    while(!infile.eof()){
        Node *supervisor_node;

        //Initialize the root node if we're on the first line of the file
        if(first_line){
            supervisor_node = boss;
            first_line = false;
        }else{
            supervisor_node = find_node(boss, supervisor);
        }

        //Check if we're dealing with an advisor or a supervisor
        if(supervisee == "Advisee"){
            supervisor_node->advisee_count++;
        }else{
            /* Determine if the supervisee should be the first or second
            supervisee */
            if(supervisor > supervisee){
                supervisor_node->supervisee_1 = new_node(supervisee);
            }else{
                supervisor_node->supervisee_2 = new_node(supervisee);
            }
        }

        //Read the next line
        infile >> supervisor;
        infile >> supervisee;
    }

    return boss;
}

//Finds and returns the node with the given name
Node *find_node(Node *curr_node, string name){
//Base Case: If curr_node is the person we're looking for, return it
  if(curr_node->name == name){
    return curr_node;
  //Recursive Cases: Search either the left or right subtree for the name
  } else if(curr_node->name > name){
    if(curr_node->supervisee_1 == nullptr) return nullptr;
    return find_node(curr_node->supervisee_1, name);
  } else {
    if(curr_node->supervisee_2 == nullptr) return nullptr;
    return find_node(curr_node->supervisee_2, name);
  }
  return nullptr;
}

//Returns a new node that is blank except for the provided name
Node *new_node(string name){
    Node *new_node = new Node;

    new_node->name = name;
    new_node->supervisee_1 = nullptr;
    new_node->supervisee_2 = nullptr;
    new_node->advisee_count = 0;

    return new_node;
}

/* Purpose: find the total number of advisees for each node*/
int total_advisees(Node *curr_node) {
  /* if the person doesn't exist at that node then return a 0 */
  if(curr_node == nullptr) {
    return 0;
  }
  /* Base Case: If the node is a leaf which means supervisee_1
  and supervisee_2 are nullptrs then add the advisee_count to count */
  if(curr_node->supervisee_1 == nullptr && curr_node->supervisee_2 == nullptr) {
    count += curr_node->advisee_count;
  } else {
    /* recurse through both the supervisee_1 and supervisee_2 if either are not
    a nullptr to check all the other advisees to add up the total */
    if(curr_node->supervisee_1 != nullptr){
      total_advisees(curr_node->supervisee_1);
    }
    if(curr_node->supervisee_2 != nullptr){
      total_advisees(curr_node->supervisee_2);
    }
  }
  /* return the total advisee count */
  return count;
}

/* Purpose: find the slackers within the input file */
void query_slacker(Node *curr_node){
  /* BASE CASE: if the node you're checking is a slacker then print out the
  name of the slacker */
  if(curr_node->supervisee_1 == nullptr && curr_node->supervisee_2 == nullptr
  && curr_node->advisee_count == 0) {
    cout << "Slacker: " << curr_node->name << endl;
  } else {
    /* recurse through the supervisee_1 and supervisee_2 of that curr_node
    if they don't equal a nullptr */
    if(curr_node->supervisee_1 != nullptr){
      query_slacker(curr_node->supervisee_1);
    }
    if(curr_node->supervisee_2 != nullptr){
      query_slacker(curr_node->supervisee_2);
    }
  }
}

/* Purpose: to quit the function and make sure to delete memory */
void query_quit(Node *curr_node) {
  /* BASE CASE: if the current node doesn't exist then return */
  if(curr_node == nullptr) {
    return;
  }
  /* recurse through all the other supervisees and delete their information */
  query_quit(curr_node->supervisee_1);
  query_quit(curr_node->supervisee_2);
  delete curr_node;
}
