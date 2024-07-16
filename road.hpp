//314923822
//morberger444@gmail.com
#ifndef ROAD_HPP
#define ROAD_HPP
#include <ostream>
#include "place.hpp"
#include "settlement.hpp"
#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace ariel {
    class Settlement;
    class Road {
    private:
        bool isTaken;
        int id;
        std::list<int> Settlements;
    public:
        Road(int numInput);
        Road();
        ~Road();
        void addSettlement(int inputSettlements);
        std::list<int> getSettlement();
        int getRoadID();
        bool getIsTaken();
        void setIsTaken(bool taken);
        void buying();
    };
}
#endif