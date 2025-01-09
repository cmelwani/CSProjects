#ifndef __PASSENGER_H__
#define __PASSENGER_H__

struct Passenger {
        int id, from, to;
        Passenger() : Passenger(-1,-1,-1) {}
        Passenger(int newId, int arrivalStation, int departureStation)
            : id(newId), from(arrivalStation), to(departureStation) {}
};

#endif