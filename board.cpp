//314923822
//morberger444@gmail.com
#include "board.hpp"
#include "place.hpp"
#include "settlement.hpp"
#include "road.hpp"
#include <iostream>
#include <list>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
using namespace std;
using namespace ariel;

Board::Board(){
    for(int i = 0; i < 72; ++i) {
        listRoad[i]=Road(i);
    }
    listSettlement[0]=Settlement({0,1},0);
    listSettlement[1]=Settlement({1,2},1);
    listSettlement[2]=Settlement({2,3,32},2);
    listSettlement[3]=Settlement({3,4},3);
    listSettlement[4]=Settlement({4,5,35},4);
    listSettlement[5]=Settlement({5,6},5);
    listSettlement[6]=Settlement({6,7},6);
    listSettlement[7]=Settlement({7,8,37},7);
    listSettlement[8]=Settlement({8,9},8);
    listSettlement[9]=Settlement({9,10,40},9);
    listSettlement[10]=Settlement({10,11},10);
    listSettlement[11]=Settlement({11,12},11);
    listSettlement[12]=Settlement({12,13,42},12);
    listSettlement[13]=Settlement({13,14},13);
    listSettlement[14]=Settlement({14,15,45},14);
    listSettlement[15]=Settlement({15,16},15);
    listSettlement[16]=Settlement({16,17},16);
    listSettlement[17]=Settlement({17,18,47},17);
    listSettlement[18]=Settlement({18,19},18);
    listSettlement[19]=Settlement({19,20,50},19);
    listSettlement[20]=Settlement({20,21},20);
    listSettlement[21]=Settlement({21,22},21);
    listSettlement[22]=Settlement({22,23,52},22);
    listSettlement[23]=Settlement({23,24},23);
    listSettlement[24]=Settlement({24,25,55},24);
    listSettlement[25]=Settlement({25,26},25);
    listSettlement[26]=Settlement({26,27},26);
    listSettlement[27]=Settlement({27,28,57},27);
    listSettlement[28]=Settlement({28,29},28);
    listSettlement[29]=Settlement({29,0,30},29);
    listSettlement[30]=Settlement({30,31,59},30);
    listSettlement[31]=Settlement({31,32,33},31);
    listSettlement[32]=Settlement({33,34,62},32);
    listSettlement[33]=Settlement({34,35,36},33);
    listSettlement[34]=Settlement({36,37,38},34);
    listSettlement[35]=Settlement({38,39,64},35);
    listSettlement[36]=Settlement({39,40,41},36);
    listSettlement[37]=Settlement({41,42,43},37);
    listSettlement[38]=Settlement({43,44,66},38);
    listSettlement[39]=Settlement({44,46,66},39);
    listSettlement[40]=Settlement({46,47,48},40);
    listSettlement[41]=Settlement({48,49,68},41);
    listSettlement[42]=Settlement({49,50,51},42);
    listSettlement[43]=Settlement({51,52,70},43);
    listSettlement[44]=Settlement({53,54,70},44);
    listSettlement[45]=Settlement({54,55,56},45);
    listSettlement[46]=Settlement({56,57,58},46);
    listSettlement[47]=Settlement({58,59,60},47);
    listSettlement[48]=Settlement({60,61,71},48);
    listSettlement[49]=Settlement({61,62,63},49);
    listSettlement[50]=Settlement({63,64,65},50);
    listSettlement[51]=Settlement({65,66,67},51);
    listSettlement[52]=Settlement({67,68,69},52);
    listSettlement[53]=Settlement({69,70,71},53);
    
//go over the roads in order to add the connected settlemnts
    for(int i = 0; i < 72; ++i) {
        std::list<Settlement> Settlements;
        for(int j=0; j<54; j++){
            if(listSettlement[j].hasRoad(i))
                listRoad[i].addSettlement(j);
        }
    }

    this->map[0]=Place(Place::AgriculturalLand, {0,1,2,30,31,32}, 5,{0,1,2,29,30,31});
    this->map[1]=Place(Place::Forest, {3,4,35,34,33,32}, 4,{2,3,4,33,32,31});
    this->map[2]=Place(Place::Hills, {5,6,7,37,36,35}, 3,{4,5,6,7,34,33});
    this->map[3]=Place(Place::Desert, {8,9,40,39,38,37}, 0,{7,8,9,34,35,36});      
    this->map[4]=Place(Place::PastureLand, {10,11,12,42,41,40}, 11,{9,10,11,12,36,37});
    this->map[5]=Place(Place::Mountains, {13,14,45,44,43,42}, 8,{12,13,14,37,38,39});
    this->map[6]=Place(Place::Forest, {15,16,17,47,46,45}, 10,{14,15,16,17,39,40});
    this->map[7]=Place(Place::AgriculturalLand, {18,19,50,49,48,47}, 2,{17,18,19,40,41,42});
    this->map[8]=Place(Place::Hills, {20,21,22,52,51,50}, 9,{19,20,21,22,42,43});
    this->map[9]=Place(Place::PastureLand, {23,24,55,54,43,52}, 12,{22,23,24,43,44,45});
    this->map[10]=Place(Place::Mountains, {25,26,27,57,56,55}, 6,{24,25,26,27,45,46});
    this->map[11]=Place(Place::Forest, {28,29,30,59,58,57}, 3,{27,28,29,30,46,47});
    this->map[12]=Place(Place::AgriculturalLand, {31,33,62,61,60,59}, 6,{30,31,32,47,48,49});
    this->map[13]=Place(Place::PastureLand, {34,36,38,64,63,62}, 5,{32,33,34,35,50,49});
    this->map[14]=Place(Place::Mountains, {39,41,43,66,65,64}, 10,{35,36,37,38,51,50});
    this->map[15]=Place(Place::Hills, {66,67,68,48,46,44}, 8,{38,39,40,41,51,52});
    this->map[16]=Place(Place::Forest, {68,69,70,49,51,53}, 11,{41,42,43,44,52,53});
    this->map[17]=Place(Place::AgriculturalLand, {54,56,58,60,71,70}, 4,{44,45,46,47,48,53});
    this->map[18]=Place(Place::Mountains, {61,63,65,67,69,71}, 9,{48,49,50,51,52,53});

    //go over the settlemnts to add the connected places
    for(int i = 0; i < 54; ++i) {
        for(int j=0; j< 19; j++){
            if(map[j].hasSettlement(i))
                listSettlement[i].addPlace(j);
        }
    }
}

Board::~Board() {}

Road* ariel::Board::getRoad(int id)
{
    return &listRoad[id];
}

Settlement* ariel::Board::getSettlement(int id)
{
    return &listSettlement[id];
}

Place *ariel::Board::getPlace(int id)
{
    return &map[id];
}

std::list<int> ariel::Board::getResourcesOfSettlement(int id)
{
    std::list<int> resources;
    std::list<int> places=this->listSettlement[id].getPlaces();
    for(int place: places){
        resources.push_front(this->map[place].getResource());
    }
    return resources;
}

//checking if the place is availble
bool ariel::Board::placeSettelemnt(int idRequested)
{
    if(idRequested<0||idRequested>=54){
        std::cout << "unknown ID" << std::endl;
        return false;
    }
    if (this->listSettlement[idRequested].getType()==Settlement::NONESettlement)
    {
        //get the roads of the settlemnt in order to see if it has neighbors
        list<int>listOfRoadsSettlement=this->listSettlement[idRequested].getRoads();
        for (int road:listOfRoadsSettlement)
        {
            list<int> listfromRoad= getRoad(road)->getSettlement();
            for (int settlement:listfromRoad)
            {
                if ((settlement!=idRequested)&&(getSettlement(settlement)->getType()!=Settlement::NONESettlement))
                {
                    std::cout << "this settlement have neighbors" << std::endl;
                    return false;
                }
            }
        }
        this->listSettlement[idRequested].updateType(Settlement::VILLAGE);
        std::cout << "this settlement is availble ID:" << idRequested << std::endl;
        return true;
    }
    std::cout << "this settlement is unavailble ID:" << idRequested << std::endl;
    return false;
}

//check if the road is availble
bool ariel::Board::placeRoad(int idRequested)
{
    if(idRequested<0||idRequested>=72){
        std::cout << "unknown ID" << std::endl;
        return false;
    }
    if (!this->listRoad[idRequested].getIsTaken())
    {
        std::cout << "this road is availble ID:"<< idRequested << std::endl;
        this->listRoad[idRequested].setIsTaken(true);
        return true;
    }
    std::cout << "this road is unavailble ID:" << idRequested << std::endl;
    return false;
}

void ariel::Board::removeRoad(int SelectedRoad)
{
    this->listRoad[SelectedRoad].setIsTaken(false);
}
//update from village to city
bool ariel::Board::updateToCity(int idRequested)
{
    if(idRequested<0||idRequested>=54){
        std::cout << "unknown ID" << std::endl;
        return false;
    }
    if (getSettlement(idRequested)->getType()==Settlement::VILLAGE)
        {
            getSettlement(idRequested)->updateType(Settlement::CITY);
            return true;
        }
    std::cout << "this settlement not a village" << std::endl;
    return false;
}
