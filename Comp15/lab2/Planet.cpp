/* 
 * Planet.cpp
 * COMP15
 * Fall 2018
 *
 * Interface for a Planet class
 */

#include <fstream>

#include "Planet.h"

using namespace std;

Planet::Planet()
{
    name = "Earth";
}

Planet::Planet(string name)
{
    this->name = name;
}

void Planet::print(ostream &out) const
{
    out << name;
}

bool Planet::operator== (const Planet &other)
{
    return (name == other.name);
}

