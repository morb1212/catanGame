//314923822
//morberger444@gmail.com
#include "player.hpp"
#include "developmentCard.hpp"
#include "board.hpp"
#include "catan.hpp"
#include "settlement.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
using namespace std;
using namespace ariel;

ariel::Player::Player(string nameInput)
{
    this->name=nameInput;
    this->points=0;
    this->turn=false;
    this->resources[Place::WOOD] = 0;
    this->resources[Place::BRICK] = 0;
    this->resources[Place::WOOL] = 0;
    this->resources[Place::IRON] = 0;
    this->resources[Place::WHEAT] = 0;
    this->resources[Place::KNIGHT] = 0;
}

Player::Player() {}

Player::~Player() {}
bool ariel::Player::checkListResources(const std::list<int> checkResources)
{
    int amount=0;
    int amountList=0;
    for(int i=0;i<6;i++){
        amount=this->resources[i];
        for(int check:checkResources){
            if (check==i)
                amountList++;
        }
        if (amount!=amountList)
        {
            return false;
        }
        amountList=0;
    }
    return true;
}
void ariel::Player::removeRoad(int selectedRoad)
{
    for(int road:this->roads){
        roads.remove(road);
    }
}
// true is + false is 0-
void ariel::Player::updateONEResource(int resourceInput,bool action)
{
    if(action)
        this->resources[resourceInput]++;
    else if(this->resources[resourceInput]>0)
        this->resources[resourceInput]--;
        else throw invalid_argument("doesn't have enougfh resources");
}
//true is + false is 0-
void ariel::Player::updateResources(std::list<int> checkResourcesList, bool action)
{
    if(action){
        for(int i:checkResourcesList){
            this->resources[i]++;
        }
    }
    else { if (checkResources(checkResourcesList))
    {
        for(int i:checkResourcesList){
            this->resources[i]--;
        }
    }
    else throw invalid_argument("doesn't have enougfh resources");
    }
}

bool ariel::Player::checkResources(std::list<int> checkResources)
{
    for(int i:checkResources){
        if(this->resources[i]==0)
        return false;
    }
    return true;
}

void ariel::Player::updateResourcesCITY()
{
    this->resources[Place::IRON]-=3;
    this->resources[Place::WHEAT]-=2;

}

bool ariel::Player::checkResourcesCITY()
{
    if ((this->resources[Place::IRON]>=3)&&(this->resources[Place::WHEAT]>=2))
        return true;
    return false;
}

//add the settelment to the correct list, if it is a city it will delete it from the villages
void ariel::Player::addSettlement(int selectedSettlement,int type)
{
    switch (type)
    {
    case Settlement::VILLAGE:
        points++;
        this->villages.push_front(selectedSettlement);
        break;
    case Settlement::CITY:
        for (int village:villages)
        {
            if(selectedSettlement==village){
                villages.remove(village);
                this->cities.push_front(selectedSettlement);
                points++;
                break;
            }
        }
        break;
    default:
        break;
    }
}

void ariel::Player::setTurn(bool turnNow)
{
    this->turn=turnNow;
}
void ariel::Player::printResources()
{
    string resourceNames[6] = {"WOOD", "BRICK", "WOOL", "IRON", "WHEAT", "KNIGHT"};
    std::cout << "resources of: "<< this->name << std::endl;
    for (int i=0;i<6;i++)
    if (this->resources[i]>0)
    {
        std::cout << resourceNames[i] << " = " << this->resources[i] << std::endl;
    }  
}
bool ariel::Player::HasRoad(int id)
{
    for (int check: roads){
        if (check==id)
            return true;
    }
    return false;
}

bool ariel::Player::HasSettlement(int id)
{
    for (int check: villages){
        if (check==id){
            std::cout << id << " is a village " << std::endl;
            return true;
        }
    }
        for (int check: cities){
        if (check==id){
            std::cout << id << " is a city " << std::endl;
            return true;
        }
    }
    return false;
}

void ariel::Player::addPoints(int i)
{
    this->points+=i;
}

std::list<int> ariel::Player::getSettlements()
{
    std::list<int> settlements;
    for(int village:villages){
        settlements.push_front(village);
    }
    for(int city:cities){
        settlements.push_front(city);
    }
    return settlements;
}

bool ariel::Player::hasCard(int cardType) {
    int card;
    for (int card:cards){
        if ( card== cardType) {
                return true;
            }
        }

    std::cout << this->name + " doesn't have that card" << endl;
    return false;
}
void ariel::Player::removeCard(int cardType) {
    int card;
    for (int card:cards){
        if ( card== cardType) {
                cards.remove(card);
                break;
            }
        }
}

std::list<int> ariel::Player::getCities()
{
    return this->cities;
}

std::list<int> ariel::Player::getVillages()
{
    return this->villages;
}

int ariel::Player::getResourcesSize()
{
    int size=0;
    for (int resource:this->resources){
        size+=resource;
    }
    return size;
}

void ariel::Player::removeHalfResources()
{
    int size=getResourcesSize();
    int list[size];
    int index=0;
    for (int i=0;i<6;i++){
        int sizeofResource=this->resources[i];
        for(int j=0;j<sizeofResource;j++){
            list[index]=i;
            index++;
        }
    }
    for(int i=0;i<size;i++){
        if(i%2==0){
            int removeResource=list[i];
            this->updateONEResource(removeResource,false);
            }
    }
}

void ariel::Player::printPoints()
{
    std::cout << this->name + " has "+ to_string(this->points) + " points " << endl;
}

bool ariel::Player::isItMyTurn()
{
    if(!turn)
        std::cout << this->name + " not your turn " << endl;
    return this->turn;
}
bool ariel::Player::getTurn()
{
    return this->turn;
}


std::list<int> ariel::Player::getCards()
{
    return this->cards;
}

void ariel::Player::setName(string inputname)
{
    this->name=inputname;
}
//activate only if it is the player turn, throgh catan get all the cards
bool ariel::Player::monopolyCard(int resource, Catan catan)
{
    if(isItMyTurn()){
        if (hasCard(DevelopmentCard::MONOPOLY)&&isItMyTurn()) {
            removeCard(DevelopmentCard::MONOPOLY);
            return catan.monopolyCard(resource,this->name);
        }
        else{
            return false;
        }
        return false;
    }
    return false;
}
//activate only if it is the player turn
bool ariel::Player::freeResources(int resource1, int resource2)
{
    if(isItMyTurn()){
        if(hasCard(DevelopmentCard::FREE_RESOURCES)){
        removeCard(DevelopmentCard::FREE_RESOURCES);
        this->resources[resource1]++;
        this->resources[resource2]++;
        return true;
        }
        return false;
    }  
    return false;
}
//switch case according to the selected card
bool ariel::Player::buyDevelopmentCard(DevelopmentCard* cardsAvailble,int selectedCard)
{
    if(isItMyTurn()){
    if((this->resources[Place::IRON]>0)&&(this->resources[Place::WHEAT]>0)&&(this->resources[Place::WOOL]>0)){
        int card=cardsAvailble->randomCard(selectedCard);
        if(card !=-1){
            this->resources[Place::IRON]--;
            this->resources[Place::WHEAT]--;
            this->resources[Place::WOOL]--;
            switch (card) {
                case DevelopmentCard::MONOPOLY:
                    std::cout << "You got a Monopol card!" << std::endl;
                    this->cards.push_front(DevelopmentCard::MONOPOLY);
                    return true;
                    break;

                case DevelopmentCard:: FREE_ROADS:
                    std::cout << "You got a Free Roads card!" << std::endl;
                    this->cards.push_front(DevelopmentCard::FREE_ROADS);
                    return true;
                    break;

                case DevelopmentCard:: FREE_RESOURCES:
                    std::cout << "You got a Free Resources card!" << std::endl;
                    this->cards.push_front(DevelopmentCard::FREE_RESOURCES);
                    return true;
                    break;

                case DevelopmentCard:: POINTS:
                    std::cout << "You got a Points card!" << std::endl;
                    this->points++; 
                    return true;
                    break;

                case DevelopmentCard:: KNIGHT:
                    std::cout << "You got a Knight card!" << std::endl;
                    this->resources[Place::KNIGHT]++;
                    if(this->resources[Place::KNIGHT]==3){
                        std::cout << "You have 3 Knights" << std::endl;
                        this->points+=2;
                    }
                    return true;
                    break;

                default:
                    std::cout << "unknown option" << std::endl;
                    return false;
                    break;
            }
        }else {
            std::cout << "there is no cards" << std::endl;
            return false;
        }
    } else {
        std::cout << "Not enough resources to buy a development card." << std::endl;
        return false;
    }
    }
    return false;
}

bool ariel::Player::addRoad(int SelectedRoad)
{
        this->roads.push_back(SelectedRoad);
        return true;
    return false;
}

//trade between two players, if it knight check if need to update the points
bool ariel::Player::trade(Player* otherPlayer, int thisPlayerCard, int otherPlayerCard, int thisPlayerAmount, int otherPlayerAmount)
{
    if (isItMyTurn()){
    if((this->resources[thisPlayerCard]-thisPlayerAmount>=0)&&(otherPlayer->resources[otherPlayerCard]-otherPlayerAmount>=0)){
        if (thisPlayerCard == Place::KNIGHT) {
            int afterTrade=this->resources[Place::KNIGHT] - thisPlayerAmount;
            if (this->resources[Place::KNIGHT] == 3 && afterTrade < 3) {
            this->points -= 2;
            }
            afterTrade=otherPlayer->resources[Place::KNIGHT] + thisPlayerAmount;
            if (otherPlayer->resources[Place::KNIGHT] < 3 && afterTrade == 3) {
                std::cout << "You have 3 Knights" << std::endl;
                otherPlayer->points += 2;
            }
        }

        if (otherPlayerCard == Place::KNIGHT) {
            int afterTrade=this->resources[Place::KNIGHT] + otherPlayerAmount;
            if (this->resources[Place::KNIGHT] < 3 && afterTrade == 3) {
                std::cout << "You have 3 Knights" << std::endl;
                this->points += 2;
            }
            afterTrade=otherPlayer->resources[Place::KNIGHT] - otherPlayerAmount;
            if (otherPlayer->resources[Place::KNIGHT] == 3 && afterTrade < 3) {
                otherPlayer->points -= 2;
            }
        }

        this->resources[thisPlayerCard]-=thisPlayerAmount;
        otherPlayer->resources[otherPlayerCard]-=otherPlayerAmount;
        this->resources[otherPlayerCard]+=otherPlayerAmount;
        otherPlayer->resources[thisPlayerCard]+=thisPlayerAmount;
        std::cout << this->name + " and "+ otherPlayer->name + " traded" << endl;
        return true;
    }
    }
        std::cout << "trade fail" << endl;
        return false;
}
