//314923822
//morberger444@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <ostream>
#include <iostream>
#include <vector>
#include "board.hpp"
#include "place.hpp"
#include "catan.hpp"
#include "settlement.hpp"
#include <string>
#include <list>
#include <map>
#include "developmentCard.hpp"

using namespace std;

namespace ariel {
    class Catan;
    class Player {
    private:
        string name;
        int resources[6];
        int points;
        std::list<int> cards;
        std::list<int> roads;
        std::list<int> villages;
        std::list<int> cities;
        bool turn;
    public:
        Player(string nameInput);
        Player();
        ~Player();
        bool checkListResources(const std::list<int> checkResources);
        void removeRoad(int selectedRoad);
        void updateONEResource(int resourceInput, bool action);
        void updateResources(std::list<int> checkResources, bool action);
        bool checkResources(std::list<int> checkResources);
        void updateResourcesCITY();
        bool checkResourcesCITY();
        void addSettlement(int selectedSettlement, int type);
        bool trade(Player* otherPlayer, int thisPlayerCard, int otherPlayerCard, int thisPlayerAmount, int otherPlayerAmount);
        string getName(){return this->name;};
        int getPoints(){return this->points;};
        std::list<int> getRoads(){return this->roads;};
        bool HasRoad(int id);
        bool HasSettlement(int id);
        void addPoints(int i);
        std::list<int> getSettlements(); 
        bool hasCard(int cardType);
        void removeCard(int cardType);
        std::list<int> getCities();
        std::list<int> getVillages();
        int* getResources() {return resources;}
        int getResourcesSize();
        void removeHalfResources();
        void printPoints();
        bool isItMyTurn();
        bool getTurn();
        void setTurn(bool turnNow);
        void printResources();
        std::list<int> getCards();
        void setName(string inputname);
        bool monopolyCard(int resource, Catan catan);
        bool freeResources(int resource1,int resource2);
        bool buyDevelopmentCard(DevelopmentCard *cardsAvailble, int selectedCard);
        bool addRoad(int SelectedRoad);
    };
}

#endif