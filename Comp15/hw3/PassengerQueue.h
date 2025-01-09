/* Cheryl Melwani (cmelwa01)
 * Feb 12, 2020
 */

#ifndef _PASSENGERQUEUE_H_
#define _PASSENGERQUEUE_H_

#include <string>
#include <iostream>
#include <vector>
#include "Passenger.h"

using namespace std;

class PassengerQueue
{
public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger& passenger);
    int size();
    void print();

private:
    vector<Passenger> passenger_array;
};

#endif
