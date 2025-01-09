/*
 * planet-driver.cpp
 * COMP15
 * Fall 2018
 *
 * Driver for the Linked List of Planets
 */

#include <iostream>
#include "LinkedList.h"

using namespace std;

// Function to reverse a linked list
void reverse_list(LinkedList &lst1, LinkedList &lst2);

// User string to stop entering planets
const string STOP   = "done";
const string PROMPT = "Enter a planet (or \""
                      + STOP
                      + "\" to stop)\n";

//
// Read a string from cin after printing prompt on cout
//
string get_string(string prompt)
{
        string result;

        cout << prompt;
        cin  >> result;

        return result;
}


//
// This main is too long
// If you have time, you can think about ways to factor out
// other useful functions
//
int main()
{
        // Make a list of planets and prompt user for names
        LinkedList planets, planets_inverse;
        string     name;

        cout << "PART 1: Inserting at the front of the list\n";

        name = get_string(PROMPT);
        while (name != STOP) {
                cout << endl;
                Planet p(name);
                planets.insert_planet(p);
                name = get_string(PROMPT);
        }

        // Print in default order (backwards)
        cout << "List of planets, default:\n";
        planets.print(cout);

        reverse_list(planets, planets_inverse);
        cout << "List of planets, correct order: " << endl;
        planets_inverse.print(cout);
        /*****************************************************/
        /* YOUR CODE HERE                                    */
        /* MAKE A SECOND LIST                                */
        /* AND CALL YOUR REVERSE FUNCTION                    */
        /* AND PRINT                                         */
        /*****************************************************/


        cout << "PART 2: Inserting at the back of the queue\n";
        cout << "This time with insert_planet_at_back\n";
        name = get_string(PROMPT);
        while (name != STOP) {
                cout << endl;
                Planet p(name);
                planets_inverse.insert_planet_at_back(p);
                name = get_string(PROMPT);
        }

        // Print in order of arrival
        cout << "List of planets."
             << "  We inserted at the back, so should be"
             << " in correct order already\n";
        planets_inverse.print(cout);

        return 0;
}

// YOUR CODE HERE
// Store the elements of lst1 into lst2 in reverse order
// No need to return anything; both are passed by reference
void reverse_list(LinkedList &lst1, LinkedList &lst2)
{
  for(int i = 0; i < lst1.get_length(); i++) {
    Planet p = lst1.get_next_planet();
    lst2.insert_planet(p);
  }
}
