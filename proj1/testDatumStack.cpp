
/* CHERYL MELWANI (cmelwa01)
18th February 2020
*/

#include <iostream>
#include "DatumStack.h"

using namespace std;

void testArrayConstructor();

/* Purpose: To test the other functions in the DatumStack.cpp class.
Return type: int
Parameters: none
*/
int main() {
    DatumStack ds;
    Datum d1 (3);
    Datum d2 (4);
    Datum d3 (true);
    Datum d4 (7);
    //TESTING PUSH
    ds.push(d1);
    ds.push(d2);
    ds.push(d3);
    ds.push(d4);

    cout << "Size of the vector: " << ds.size() << endl;
    //TESTING TOP
    Datum top = ds.top();
    cout << "Top element in the vector: " << top.getInt() << endl;
    //TESTING POP
    ds.pop();
    Datum top2 = ds.top();
    cout << "Top element in the vector after popping: " << top2.getBool() << endl;
    //TESTING SIZE
    cout << "Size of the vector: " << ds.size() << endl;
    //TESTING CLEAR
    ds.clear();
    cout << "Size of the vector after clear: " << ds.size() << endl;
    //TESTING EMPTY
    if(ds.isEmpty() == true) {
        cout << "Vector is Empty!!" << endl;
    }
    //TESTING ARRAY CONSTRUCTOR
    testArrayConstructor();
}

/* Purpose: A function that checks the array constructor in the DatumStack.cpp
Return type: void
Parameters: none
*/
void testArrayConstructor() {
    Datum d1 (3);
    Datum d2 (4);
    Datum d3 (5);
    Datum new_array[3] = {d1, d2, d3};
    DatumStack stack(new_array, 3);
    Datum top = stack.top();
    cout << "Element: " << top.getInt() << endl;
}
