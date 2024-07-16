//314923822
//morberger444@gmail.com
#ifndef CATAN_HPP
#define CATAN_HPP
#include <ostream>
#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"
#include "developmentCard.hpp"
#include "board.hpp"
using namespace std;

namespace ariel {
    class Player;
    class DevelopmentCard;
    class Catan {
    private:
        Player* p1;
        Player* p2;
        Player* p3;
        Player* currentMostRoadsPlayer;
        Board* board;
        DevelopmentCard* cards;
    public:
        Catan(Player* p1,Player* p2,Player* p3,Board* Board,DevelopmentCard* cards);
        ~Catan();
        void printWinner();
        Board* getBoard();
        Player* ChooseStartingPlayer();
        DevelopmentCard* getcards();
        void endTurn();
        void rollDice(Player &p, int sumDice);
        bool monopolyCard(int resource, string name);
        void hasMostRoads(Player* targetPlayer);
        Player* getFromName(string name);
        bool placeRoad(int SelectedRoad,Player* name);
        bool placeRoadCard(int SelectedRoad1, int SelectedRoad2, Player* target);
        bool isabletoplace(int id, int type, Player *target, bool firstTurn);
        bool placeSettelemnt(int selectedSettlement,Player* name,bool firstTurn);
        bool caseVillage(int selectedSettlement,Player* name,bool firstTurn);
        bool caseCity(int selectedSettlement,Player* name,bool firstTurn);
        bool caseRoad(int selectedSettlement,Player* name,bool firstTurn);
    };
}

#endif