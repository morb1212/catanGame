//314923822
//morberger444@gmail.com
#include "place.hpp"
#include "road.hpp"
#include "player.hpp"
#include "settlement.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
using namespace std;
using namespace ariel;

ariel::Place::Place(int Inputname, std::list<int> Inputroads,int InputNumLocation,std::list<int> inputSettlements)
{
    this->name=Inputname;
    this->Settlements=inputSettlements;
    this->roads=Inputroads;
    this->numLocation=InputNumLocation;
    switch (Inputname) {
        case AgriculturalLand:
            this->resource=WHEAT;
            break;

        case Forest:
            this->resource=WOOD;
            break;

        case Hills:
            this->resource=BRICK;
            break;

        case Desert:
            this->resource=-1;
            break;

        case PastureLand:
            this->resource=WOOL;
            break;

        case Mountains:
            this->resource=IRON;
            break;
                
        default:
            std::cout << "unknown option" << std::endl;
            break;
    }
}

ariel::Place::Place()
{
}

Place::~Place() {}

int ariel::Place::getNumLocation()
{
    return this->numLocation;
}

int ariel::Place::getResource()
{
    return this->resource;
}

bool ariel::Place::hasSettlement(int id)
{
    for (int check: this->Settlements){
        if (check==id)
            return true;
    }
    return false;
}

