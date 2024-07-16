//314923822
//morberger444@gmail.com
#include "road.hpp"
#include "settlement.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
#include <list>
using namespace std;
using namespace ariel;


ariel::Road::Road(int numInput)
{
    this->isTaken=false;
    this->id=numInput;
}
ariel::Road::Road()
{
}

ariel::Road::~Road()
{
}

void ariel::Road::addSettlement(int inputSettlement)
{
    this->Settlements.push_front(inputSettlement);
}

std::list<int> ariel::Road::getSettlement()
{
    return this->Settlements;
}

int ariel::Road::getRoadID()
{
   return this->id;
}

bool ariel::Road::getIsTaken()
{
    return this->isTaken;
}

void ariel::Road::setIsTaken(bool taken)
{
    this->isTaken=taken;
}

void ariel::Road::buying()
{
    bool status= this->isTaken;
    if(!status){
        this->isTaken=!status;
    }
}
