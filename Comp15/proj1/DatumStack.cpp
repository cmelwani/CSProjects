
/* CHERYL MELWANI (cmelwa01)
18th February 2020
*/

#include "DatumStack.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

/* Default Constructor */
DatumStack::DatumStack() {

}

/* Array Constructor */
DatumStack::DatumStack(Datum new_array[], int size) {
    for (int i = size-1; i >= 0; i--) {
        datum_vector.push_back(new_array[i]);
    }
}

/* Destructor */
DatumStack::~DatumStack() {
    clear();
}

/* Purpose: A function that checks if the stack is empty or not
Return type: boolean
Parameters: none
*/
bool DatumStack::isEmpty() {
    return datum_vector.empty();
}

/* Purpose: A function that clears the stack
Return type: void
Parameters: none
*/
void DatumStack::clear() {
    datum_vector.clear();
}

/* Purpose: A function that returns the size of the stack
Return type: integer
Parameters: none
*/
int DatumStack::size() {
    int size = datum_vector.size();
    return size;

}

/* Purpose: A function that finds the top of the stack and returns that value
Return type: a Datum
Parameters: none
*/
Datum DatumStack::top() {
    if (isEmpty() == true) {
        throw runtime_error ("empty_stack");
    }
    return datum_vector.front();
}

/* Purpose: A function that pops the top of the stack off the stack
Return type: void
Parameters: none
*/
void DatumStack::pop() {
    if (isEmpty() == true) {
        throw runtime_error ("empty_stack");
    }
    datum_vector.erase(datum_vector.begin());
}

/* Purpose: A function that inserts at the front of the stack
Return type: void
Parameters: none
*/
void DatumStack::push(Datum d) {
    datum_vector.insert(datum_vector.begin(), d);
}
