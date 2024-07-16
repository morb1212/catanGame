//314923822
//morberger444@gmail.com
#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP
#include <ostream>
#include "place.hpp"
#include "road.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

namespace ariel {
    class Road;
    class Settlement {
    private:
        int type;
        int id;
        std::list<int> roads;
        std::list<int> places;
        std::list<int> Settlements;
    public:
    enum type {
        VILLAGE,
        CITY,
        NONESettlement,
    };
    
        Settlement(std::list<int> Inputroads,int numinput);
        Settlement();
        ~Settlement();
        int getType();
        int getId();
        std::list<int> getRoads();
        void updateType(int inputType);
        bool hasRoad(int id);
        std::list<int> getPlaces();
        void addPlace(int inputPlace);
    };
}
#endif