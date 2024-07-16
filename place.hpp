//314923822
//morberger444@gmail.com
#ifndef PLACE_HPP
#define PLACE_HPP
#include "road.hpp"
#include "settlement.hpp"
#include <ostream>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>

using namespace std;

namespace ariel {
    class Place {
    private:
        int name;
        int resource;
        int numLocation;
        std::list<int> roads;
        std::list<int> Settlements;
    public:
    enum namePlacesType {
        AgriculturalLand,
        Forest,
        Hills,
        Desert,
        PastureLand,
        Mountains,
    };
    enum resourcesType {
        WOOD,
        BRICK,
        WOOL,
        IRON,
        WHEAT,
        KNIGHT,
    };
        Place(int Inputname, std::list<int> Inputroads,int InputNumLocation,std::list<int> inputSettlements);
        Place();
        ~Place();
        int getNumLocation();
        int getResource();
        bool hasSettlement(int id);
    };
}
#endif