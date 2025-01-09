
/* CHERYL MELWANI (cmelwa01)
18th February 2020
*/

#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include "Datum.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class DatumStack
{
public:
    DatumStack();
    DatumStack(Datum new_array[], int size);
    ~DatumStack();
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum d);
private:
    vector<Datum> datum_vector;

};

#endif
