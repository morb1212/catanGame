//314923822
//morberger444@gmail.com
#include "settlement.hpp"
#include "place.hpp"
#include "road.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
#include <list>
using namespace std;
using namespace ariel;
ariel::Settlement::Settlement(std::list<int> Inputroads,int numinput)
{
    this->id=numinput;
    this->type=NONESettlement;
    this->roads=Inputroads;
}

ariel::Settlement::Settlement()
{
}

ariel::Settlement::~Settlement()
{
}

int ariel::Settlement::getType()
{
    return this->type;
}

int ariel::Settlement::getId()
{
    return this->id;
}

std::list<int> ariel::Settlement::getRoads()
{
    return this->roads;
}

void ariel::Settlement::updateType(int inputType)
{
    this->type=inputType;
}


bool ariel::Settlement::hasRoad(int id)
{
    for (int check: this->roads){
        if (check==id)
            return true;
    }
    return false;
}

std::list<int> ariel::Settlement::getPlaces()
{
    return this->places;
}


void ariel::Settlement::addPlace(int inputPlace)
{
    this->places.push_front(inputPlace);
}

