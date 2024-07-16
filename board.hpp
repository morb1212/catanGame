//314923822
//morberger444@gmail.com
#ifndef BOARD_HPP
#define BOARD_HPP
#include <ostream>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "place.hpp"
#include "settlement.hpp"
#include "road.hpp"
using namespace std;

namespace ariel {
    class Board {
    private:
        Place map[19];
        Road listRoad[72];
        Settlement listSettlement[54];

        
    public:
        Board();
        ~Board();
        Road* getRoad(int id);
        Settlement* getSettlement(int id);
        Place* getPlace(int id);
        std::list<int> getResourcesOfSettlement(int id);
        bool placeSettelemnt(int idRequested);
        bool placeRoad(int SelectedRoad);
        void removeRoad(int SelectedRoad);
        bool updateToCity(int idRequested);
    };
}

#endif