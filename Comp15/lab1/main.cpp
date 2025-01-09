/********************************************
* Comp 15 - Fall 2019
* Lab 1
* Julia Lober
* July 26, 2019
* 
* main.cpp
* Implementation of the grocery list program 
* using ArrayList class
*
* Usage:  shop shoppinglist.txt
*********************************************/


#include <iostream>
#include <fstream> 
#include "ArrayList.h"
using namespace std; 

bool makeList  (ArrayList &toBuy, string     filename);
void atStore   (ArrayList &toBuy ,ArrayList &bought);
void buyItem   (ArrayList &toBuy ,ArrayList &bought, string item);
void printLists(ArrayList &toBuy, ArrayList &bought);

int main(int argc, char *argv[]) 
{
        if (argc != 2) {
                cerr << "Usage: ./shop input.txt\n";
        } else {
                ArrayList toBuy; 
                ArrayList bought;

                if (makeList(toBuy, argv[1]))
                        atStore(toBuy, bought);
        }
}

// Function makeList
// Parameters: ArrayList &toBuy - reference to ArrayList to fill in
//             string filename  - name of file to read
// Returns: true if successful, false otherwise
// Does: Puts all the items from the file into the ArrayList toBuy
bool makeList(ArrayList &toBuy, string filename)
{
        ifstream in; 
        in.open(filename);
        string item;
        
        //check for error opening file
        if (not in.is_open()) {
                cerr << "Error opening file.\n";
                return false; 
        }

        //read file and input information
        while (getline(in, item))
                toBuy.insert(item); 

        in.close();
        return true;
}

// Function atStore
// Parameters: ArrayList &toBuy  - shopping  list
//             ArrayList &bought - purchased list
// Returns: nothing
// Does: Handles main functionality of the program, gets user input and 
//       updates lists accordingly
void atStore(ArrayList &toBuy, ArrayList &bought) 
{
        string item = ""; 
        printLists(toBuy,bought);
        
        cout << "Welcome to the store!"
             << " What are you buying?"
             << endl
             << "You can always type "
             << "\"Quit\" to leave the store or \"Print\" to show your lists."
             << endl << endl; 
        while (toBuy.size() > 0) {
                getline(cin,item);
                if (item == "Print"){
                        cout << endl;
                        printLists(toBuy, bought);
                        cout << "Next item?\n";
                } else if (item == "Quit") {
                        break;
                } else {
                        buyItem(toBuy, bought, item);
                }
                
        }
        cout << "Leaving store!\n\n";
        printLists(toBuy, bought);
}

// Function buyItem
// Parameters: ArrayList &toBuy  - shopping list
//             ArrayList &bought - purchased list
//             string     item   - the item to purchase
// Returns: nothing
// Does: If item is found on the toBuy list, add to bought list
//       otherwise print an error message and leave lists unchanged
void buyItem(ArrayList &toBuy, ArrayList &bought, string item)
{
        if (toBuy.remove(item)) {
                bought.insert(item);
                if (toBuy.size() != 0) 
                        cout << "Next item?\n";
        } else {
                cout << "This item was not on the list,"
                     << " try buying something else.\n";
        }
}

// Function printLists
// Parameters: ArrayList &toBuy  - shopping list
//             ArrayList &bought - purchased list
// Returns: nothing
// Does: Displays number of items and items on each list on cout
void printLists(ArrayList &toBuy, ArrayList &bought)
{
        cout << "Shopping list has " << toBuy.size() << " item(s):\n";
        toBuy.print(cout);
        cout << endl;

        cout << "Purchased " << bought.size() << " item(s):\n";
        bought.print(cout);
        cout << endl;
}
