/*
 * Planet.h
 * COMP15
 * Fall 2018
 *
 * Interface for a Planet class
 */


#ifndef PLANET_H_
#define PLANET_H_

#include <string>
#include <ostream>

class Planet
{
public:
    Planet();
    Planet(std::string name);

    void print(std::ostream &out) const;

    bool operator== (const Planet &other);
    
private:
    std::string name;
};

#endif
