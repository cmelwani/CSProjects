/* Cheryl Melwani (cmelwa01)
 * Feb 12, 2020
 */

#include "PassengerQueue.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/* Purpose: front returns the first passanger in the passenger array.
Return: a passenger
Parameter: none */
Passenger PassengerQueue::front() {
    return passenger_array.front();
}

/* Purpose: dequeue erases the first passenger in the passenger queue.
Return: void
Parameter: none */
void PassengerQueue::dequeue() {
    passenger_array.erase(passenger_array.begin());
}

/* Purpose: enqueue adds a passenger to the back of the passenger queue.
Return: void
Parameter: a passenger that is passed by reference using the & operator */
void PassengerQueue::enqueue(const Passenger& passenger) {
    passenger_array.push_back(passenger);
}

/* Purpose: size returns the size of the passenger queue.
Return: integer called size
Parameter: none */
int PassengerQueue::size() {
    int size = passenger_array.size();
    return size;
}

/* Purpose: print prints out the passengers in the queue including their
arrival and destination stations.
Return: void
Parameter: none */
void PassengerQueue::print() {
    for (int i = 0; i < size(); i++) {
        Passenger curr_p = passenger_array.at(i);
        cout << "[" << curr_p.id << ", " << curr_p.from+1 << "->" << curr_p.to+1
        << "]";
    }
}
