//314923822
//morberger444@gmail.com
#include "catan.hpp"
#include "place.hpp"
#include "developmentCard.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
#include "board.hpp"
using namespace std;
using namespace ariel;

Catan::Catan(Player* inputp1,Player* inputp2,Player* inputp3,Board* Inputboard,DevelopmentCard* inputcards) 
    {
        int count=1;
        if(inputp1->getName() == inputp2->getName() && inputp1->getName() == inputp3->getName()){
            count++;
            string name=inputp1->getName() + std::to_string(count);
            inputp2->setName(name);
            count++;
            string name2=inputp1->getName() + std::to_string(count);
            inputp3->setName(name);
        }
        else{
            if(inputp1->getName() == inputp2->getName()){
            count++;
            string name=inputp1->getName() + std::to_string(count);
            inputp2->setName(name);
            }
            if(inputp1->getName() == inputp3->getName()){
            count++;
            string name=inputp1->getName() + std::to_string(count);
            inputp3->setName(name);
            }
            if(inputp3->getName() == inputp2->getName()){
            count++;
            string name=inputp2->getName() + std::to_string(count);
            inputp3->setName(name);
            }
        }
    this->currentMostRoadsPlayer=nullptr;
    this->p1=inputp1;
    this->p2=inputp2;
    this->p3=inputp3;
    this->board=Inputboard;
    this->cards=inputcards;
    std::cout << "created game" << endl;

}

Catan::~Catan() {}

void ariel::Catan::printWinner(){
    if(this->p1->getPoints()>=10){
        std::cout << "p1: "+this->p1->getName()+" won the game" << endl;
    }
        else if(this->p2->getPoints()>=10){
        std::cout << "p2: "+this->p2->getName()+" won the game" << endl;
    }
        else if(this->p3->getPoints()>=10){
        std::cout << "p3: "+this->p3->getName()+" won the game" << endl;
    }

}

Player* ariel::Catan::ChooseStartingPlayer()
{
    this->p1->setTurn(true);
    return this->p1;  
}
DevelopmentCard* ariel::Catan::getcards()
{
    return this->cards;
}
//end turn only if the player has more then 2 roads and settlemnts (validate first turn)
void ariel::Catan::endTurn()
{  
    if(this->p1->getTurn()
    &&p1->getRoads().size()>=2&&p1->getVillages().size()+p1->getCities().size()>=2){
        this->p1->setTurn(false);
        this->p2->setTurn(true);
        std::cout << this->p2->getName() + " start your turn " << endl;
    } else if(this->p2->getTurn()
    &&p2->getRoads().size()>=2&&p2->getVillages().size()+p2->getCities().size()>=2){
        this->p2->setTurn(false);
        this->p3->setTurn(true);
        std::cout << this->p3->getName() + " start your turn " << endl;
    } else if(this->p3->getTurn()
    &&p3->getRoads().size()>=2&&p3->getVillages().size()+p3->getCities().size()>=2){
        this->p3->setTurn(false);
        this->p1->setTurn(true);
        std::cout << this->p1->getName() + " start your turn " << endl;
    }
    printWinner();
}
// after getting sum of 2 cubes, checcking which players get new resources
void ariel::Catan::rollDice(Player& p,int sumDice)
{
    if (p.isItMyTurn())
    {
        std::cout << "sum dice is "<< sumDice << endl;
        Player* list[]={this->p1,this->p2,this->p3};
        for(Player* target:list){
            if(sumDice==7){
                if(target->getResourcesSize()>7){
                    std::cout << "remove "<< target->getResourcesSize()/2 <<" cards for "<<target->getName() << endl;
                    target->removeHalfResources();
                }
            }
            std::list<int> settlementsP= target->getSettlements();
            //going over settlemnts, and places
            for(int settlement:settlementsP){
                std::list<int> placesofSTp= board->getSettlement(settlement)->getPlaces();
                for(int place:placesofSTp){
                    if(board->getPlace(place)->getNumLocation()==sumDice){
                        target->updateONEResource(board->getPlace(place)->getResource(),true);
                        if(board->getSettlement(settlement)->getType()==Settlement::CITY)
                            target->updateONEResource(board->getPlace(place)->getResource(),true);
                    }
                }
            }
        }
    } else
        std::cout << " not p: "+p.getName()+" turn" << endl;
}

// Use the monopoly card to take all resources of a specific type from other players
bool ariel::Catan::monopolyCard(int resource, string name)
{
    Player* players[] = { p1, p2, p3 };
    Player* targetPlayer = getFromName(name);
    if (targetPlayer == nullptr) {
        std::cout << " not found p: "+targetPlayer->getName() << endl;
        return false; // No valid target player found or not enough roads
    }

    if (resource < 0 || resource >= 6) {
        std::cout <<"Invalid resource index"<< endl;
        return false;
    }

    int totalResourceTaken = 0;
    for (Player* player : players) {
        if (player != targetPlayer) {
            totalResourceTaken += player->getResources()[resource];
            player->getResources()[resource] = 0;
        }
    }
    targetPlayer->getResources()[resource] += totalResourceTaken;
    return true;
}
//update the pointer of has most roads and then update the points if needed
void ariel::Catan::hasMostRoads(Player* targetPlayer)
{

    if (currentMostRoadsPlayer != nullptr) {
        if (targetPlayer->getRoads().size() > currentMostRoadsPlayer->getRoads().size()) {
            this->currentMostRoadsPlayer->addPoints(-2);
            targetPlayer->addPoints(2);
            this->currentMostRoadsPlayer=p1;
        }
    } else {
        currentMostRoadsPlayer = targetPlayer;
        currentMostRoadsPlayer->addPoints(2);
    }
    
}

Player* ariel::Catan::getFromName(string name)
{
    Player* players[] = { p1, p2, p3 };
    Player* targetPlayer = nullptr;
    for (Player* player : players) {
        if (player->getName() == name) {
            targetPlayer = player;
            break;
        }
    }
    return targetPlayer;
}
//check if the selected road has in his area settelment, if so checking in board is availble
bool Catan::placeRoad(int SelectedRoad,Player* targetPlayer) {

    std::list<int> roadSettlements = this->board->getRoad(SelectedRoad)->getSettlement();
    std::list<int> neighborRoads;

    // Check if the player has a settlement connected to the selected road
    for (int check : roadSettlements) {
        if (targetPlayer->HasSettlement(check)) {
            return this->board->placeRoad(SelectedRoad);
        }
        std::list<int> listOfRoads=this->board->getSettlement(check)->getRoads();
        // Gather all roads connected to the settlements
        for (int add :listOfRoads) {
            if (add != SelectedRoad) {
                neighborRoads.push_back(add);
            }
        }
    }

    // Check if the player has a road connected to the selected road
    for (int check : neighborRoads) {
        if (targetPlayer->HasRoad(check)) {
            return this->board->placeRoad(SelectedRoad);
        }
    }

    // If no connected settlement or road is found
    std::cout << "No valid settlement or road connection found for player: " << targetPlayer->getName() << std::endl;
    return false;
}
//activate only if the player has the card check the limit amount of roads
bool ariel::Catan::placeRoadCard(int SelectedRoad1, int SelectedRoad2, Player *target)
{
    bool istaken1=this->board->getRoad(SelectedRoad1)->getIsTaken();
    bool istaken2=this->board->getRoad(SelectedRoad2)->getIsTaken();
    if (target->isItMyTurn()&&target->hasCard(DevelopmentCard:: FREE_ROADS))
    {
        if (target->getRoads().size()==15){
            std::cout << "not enought roads" << std::endl;
            return false;
        }
        if(target->getRoads().size()==14){
            if(placeRoad(SelectedRoad1,target)){
                std::cout << "place your first road" << std::endl;
                target->addRoad(SelectedRoad1);
                target->removeCard(DevelopmentCard::FREE_ROADS);
                return true;
            }
        }
        //first place the first road, if worked then the second, if not return to the status before
        if(placeRoad(SelectedRoad1,target)){
            target->addRoad(SelectedRoad1);
            if(placeRoad(SelectedRoad2,target)){
                std::cout << "place your roads" << std::endl;
                target->addRoad(SelectedRoad2);
                target->removeCard(DevelopmentCard::FREE_ROADS);
                return true;
            } else{
                target->removeRoad(SelectedRoad1);
                this->board->removeRoad(SelectedRoad1);
                return false;
            }
        }
    }
    this->board->getRoad(SelectedRoad1)->setIsTaken(istaken1);
    this->board->getRoad(SelectedRoad2)->setIsTaken(istaken2);
    return false;
}


// Check if the player is able to place a specific piece on the board
bool ariel::Catan::isabletoplace(int id, int type, Player *target,bool firstTurn)
{
    // Ensure it's the player's turn
    if (target->isItMyTurn())
    {
        switch (type)
        {
            case Settlement::VILLAGE:
                return caseVillage(id,target,firstTurn);
                break;
            case Settlement::CITY:
                return caseCity(id,target,firstTurn);
                break;
            case Settlement::NONESettlement:
                return caseRoad(id,target,firstTurn);
                break;  
            default:
                return false;
                break;
        }
    }
    return false;
}

//check if it has a connection to road, if so check in board is availble
bool ariel::Catan::placeSettelemnt(int selectedSettlement, Player* targetPlayer,bool firstTurn)
{
    if (firstTurn)
    {
        if(this->board->placeSettelemnt(selectedSettlement)){
            return true;
        }
        return false;
    }
    std::list<int> roadsRequired=this->board->getSettlement(selectedSettlement)->getRoads();
    for (int check:roadsRequired)
    {
        if (targetPlayer->HasRoad(check))
        {
            return this->board->placeSettelemnt(selectedSettlement);
        }
        std::cout << "need to be next to a road" << endl;
        return false;
    }
    return false;
}
//place village, check the limit and update resources
bool ariel::Catan::caseVillage(int id,Player *target, bool firstTurn)
{
    // Check if the player has reached the maximum number of villages
    if (target->getVillages().size() == 5) {
        std::cout << "not enought VILLAGES" << std::endl;
        return false;
    }   
    if (firstTurn&&target->getVillages().size()+target->getCities().size()<2)
    {
        if(placeSettelemnt(id,target,true)){
            target->addSettlement(id,Settlement::VILLAGE);
            std::cout << "place a Settlement " << std::endl;
            std::list<int> resources=board->getResourcesOfSettlement(id);
            for (int resource:resources){
                target->updateONEResource(resource,true);
            }
            return true;
        }
        return false;
    }
    if (target->checkResources({Place::WOOD,Place::BRICK,Place::WHEAT,Place::WOOL})){
        if(placeSettelemnt(id,target,true)){
            target->updateResources({Place::WOOD,Place::BRICK,Place::WHEAT,Place::WOOL},false);
            target->addSettlement(id,Settlement::VILLAGE);
            std::cout << "Bought a village " << std::endl;
            return true;  
        }
    } else {
        std::cout << "not enought resources" << std::endl;
        return false;
    }
    return false;
}

bool ariel::Catan::caseCity(int id, Player *target, bool firstTurn)
{
    if (target->getCities().size()==4){
        std::cout << "not enought CITIES" << std::endl;
        return false;
        }
    if(target->checkResourcesCITY()){
        if(board->updateToCity(id)&&target->HasSettlement(id)){
            target->updateResourcesCITY();
            target->addSettlement(id,Settlement::CITY);
            std::cout << "Bought a city " << std::endl;
            return true;  
        }
        else{
            std::cout << "this settlement is taken" << std::endl;
            return false; 
        }
    }
    std::cout << "not enought resources" << std::endl;
    return false;
}

bool ariel::Catan::caseRoad(int id, Player *target, bool firstTurn)
{
     if (target->getRoads().size()==15){
        std::cout << "not enought roads" << std::endl;
        return false;
    }
    if (target->getRoads().size()<2&&firstTurn)
    {
        if(placeRoad(id,target)){
            target->addRoad(id);
            std::cout << "place a road " << std::endl;
            return true;
        }
        return false;
    }
    if (target->checkResources({Place::WOOD,Place::BRICK})){
        if(placeRoad(id,target)){
            target->updateResources({Place::WOOD,Place::BRICK},false);
            target->addRoad(id);
            std::cout << "Bought a road " << std::endl;
            hasMostRoads(target);
            return true;
        } else {
            std::cout << "this road is unavailble" << std::endl;
            return false;
        }
    }
    std::cout << "not enought resources" << std::endl;
    return false;
}

Board* ariel::Catan::getBoard()
{
        return this->board; 
}
