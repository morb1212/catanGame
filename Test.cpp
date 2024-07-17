//314923822
//morberger444@gmail.com

#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "place.hpp"
#include "road.hpp"
#include "board.hpp"
#include "settlement.hpp"
#include "developmentCard.hpp"
#include "doctest.h"

using namespace std;
using namespace ariel;

TEST_CASE("Player")
{
    cout << "Player tests:" << endl;
    // Create a player named Amit
    Player p1("Amit");

    // Create a list of resources and update the player's resources
    std::list<int> resources;
    resources.push_back(Place::IRON);
    resources.push_back(Place::IRON);
    resources.push_back(Place::IRON);
    resources.push_back(Place::WHEAT);
    resources.push_back(Place::WHEAT);

    // Update player resources and check if they can build a city
    p1.updateResources(resources, true);
    CHECK(p1.checkResourcesCITY() == true);

    // Check if it's not the player's turn, then set the turn to true and check again
    CHECK(p1.isItMyTurn() == false);
    p1.setTurn(true);
    CHECK(p1.isItMyTurn() == true);

    p1.addSettlement(10, Settlement::CITY);
    CHECK(p1.getCities().size() == 0);
    p1.addSettlement(10, Settlement::VILLAGE);
    CHECK(p1.getVillages().size() == 1);

    // Add more resources and check them
    std::list<int> checkResources;
    checkResources.push_back(Place::IRON);
    checkResources.push_back(Place::IRON);
    checkResources.push_back(Place::IRON);    
    checkResources.push_back(Place::IRON);
    checkResources.push_back(Place::IRON);
    checkResources.push_back(Place::IRON);
    checkResources.push_back(Place::WHEAT);
    checkResources.push_back(Place::WHEAT);
    checkResources.push_back(Place::WHEAT);
    checkResources.push_back(Place::WHEAT);
    checkResources.push_back(Place::BRICK);
    checkResources.push_back(Place::WOOD);
    checkResources.push_back(Place::WOOL);
    checkResources.push_back(Place::WHEAT);
    resources.push_back(Place::BRICK);
    resources.push_back(Place::WOOD);
    resources.push_back(Place::WOOL);
    resources.push_back(Place::WHEAT);
    p1.updateResources(resources, true);
    CHECK(p1.checkListResources(checkResources)==true);
    //remove half cards
    CHECK(p1.getResourcesSize()==14);
    p1.removeHalfResources();
    CHECK(p1.getResourcesSize()==7);
    std::list<int> checkResources2;
    checkResources2.push_back(Place::IRON);
    checkResources2.push_back(Place::IRON);    
    checkResources2.push_back(Place::IRON);
    checkResources2.push_back(Place::WHEAT);
    checkResources2.push_back(Place::WHEAT);
    checkResources2.push_back(Place::BRICK);
    checkResources2.push_back(Place::WHEAT);
    CHECK(p1.checkListResources(checkResources2)==true);

    //check amount villages
    p1.addSettlement(10, Settlement::VILLAGE);
    CHECK(p1.getVillages().size() == 2);
    CHECK(p1.getPoints() == 2);
    p1.addSettlement(10, Settlement::CITY);
    CHECK(p1.getCities().size() == 1);
    CHECK(p1.getVillages().size() == 0);
    CHECK(p1.getPoints() == 3);

    // Trade resources between players and check development card purchases
    Player p2("Yoni");
    p2.setTurn(true);
    p2.updateONEResource(Place::BRICK, true);
    p1.updateONEResource(Place::WOOL, true);
    CHECK(p1.trade(&p2, Place::WOOL, Place::BRICK, 5, 10) == false);
    CHECK(p1.trade(&p2, Place::WOOL, Place::BRICK, 1, 1) == true);

    // Update resources and check development card purchases
    p1.updateONEResource(Place::WHEAT, true);
    p1.updateONEResource(Place::WOOL, true);
    p1.updateONEResource(Place::IRON, true);
    DevelopmentCard cards;
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::FREE_RESOURCES) == true);
    CHECK(p1.freeResources(Place::WOOD, Place::BRICK) == true);
    CHECK(p1.addRoad(10) == true);
    CHECK(p1.getPoints() == 3);
    CHECK(p2.getPoints() == 0);

    // Update resources and check development card points
    std::list<int> resourcesP2;
    resourcesP2.push_back(Place::WHEAT);
    resourcesP2.push_back(Place::WOOL);
    resourcesP2.push_back(Place::IRON);
    p2.updateResources(resourcesP2,true);
    CHECK(p2.buyDevelopmentCard(&cards, DevelopmentCard::POINTS)==true);
    p1.updateONEResource(Place::WOOL,true);
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::POINTS) == true);
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::POINTS) == false);
    CHECK(p2.getPoints() == 1);
    CHECK(p1.getPoints() == 4);

    // Buy and check development cards for knights
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::KNIGHT)==false);
    p1.updateONEResource(Place::WHEAT, true);
    p1.updateONEResource(Place::WOOL, true);
    p1.updateONEResource(Place::IRON, true);
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::KNIGHT)==true);
    p1.updateONEResource(Place::WHEAT, true);
    p1.updateONEResource(Place::WOOL, true);
    p1.updateONEResource(Place::IRON, true);
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::KNIGHT)==true);
    p1.updateONEResource(Place::WHEAT, true);
    p1.updateONEResource(Place::WOOL, true);
    p1.updateONEResource(Place::IRON, true);
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::KNIGHT)==true);
    CHECK(p1.getPoints() == 6);

    // Test trading and turn setting
    p2.updateONEResource(Place::IRON, true);
    p2.setTurn(false);
    CHECK(p2.trade(&p1, Place::IRON, Place::KNIGHT, 1, 1) == false);
    p2.setTurn(true);
    CHECK(p2.trade(&p1, Place::IRON, Place::KNIGHT, 1, 1) == true);
    CHECK(p1.getPoints() == 4);
    CHECK(p2.getPoints() == 1);
    p1.updateONEResource(Place::WHEAT, true);
    p1.updateONEResource(Place::WOOL, true);
    p1.updateONEResource(Place::IRON, true);
    CHECK(p1.buyDevelopmentCard(&cards, DevelopmentCard::KNIGHT)==false);
    cout << "----------------" << endl;
}

TEST_CASE("Board")
{
    cout << "Board tests:" << endl;
    Board board;
    CHECK(board.placeSettelemnt(10) == true);
    CHECK(board.placeSettelemnt(10) == false);
    CHECK(board.placeRoad(10) == true);
    CHECK(board.placeRoad(10) == false);
    CHECK(board.updateToCity(10) == true);
    CHECK(board.updateToCity(10) == false);
    CHECK(board.updateToCity(11) == false);
    CHECK(board.placeSettelemnt(89) == false);
    CHECK(board.placeRoad(89) == false);
    CHECK(board.updateToCity(89) == false);
    cout << "----------------" << endl;
}

TEST_CASE("Catan")
{
    cout << "Catan tests:" << endl;
    // Create players with duplicate names and test the Catan constructor for exceptions
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Yossi");
    DevelopmentCard developmentCard;
    Board board;
    Catan catan(&p1, &p2, &p3, &board, &developmentCard);
    //check players names
    CHECK(p3.getName()=="Yossi2");
    //start the game with p1, put setlemnts
    CHECK(catan.ChooseStartingPlayer() == &p1);
    CHECK(p1.getTurn()==true);
    CHECK(catan.isabletoplace(32, Settlement::VILLAGE, &p1, true) == true);
    CHECK(catan.isabletoplace(50, Settlement::VILLAGE, &p1, true) == true);
    CHECK(catan.isabletoplace(5, Settlement::VILLAGE, &p2, true) == false);
    CHECK(catan.isabletoplace(57, Settlement::VILLAGE, &p1, true) == false);
    catan.endTurn();
    CHECK(p1.getTurn()==true);
    CHECK(catan.isabletoplace(62, Settlement::NONESettlement, &p1, true) == true);
    CHECK(catan.isabletoplace(36, Settlement::NONESettlement, &p1, true) == false);
    CHECK(catan.isabletoplace(63, Settlement::NONESettlement, &p1, true) == true);
    CHECK(catan.isabletoplace(64, Settlement::NONESettlement, &p1, true) == false);
    
    //check resources
    std::list<int> resources;
    resources.push_back(Place::WOOD);
    resources.push_back(Place::WOOL);
    resources.push_back(Place::WOOL);
    resources.push_back(Place::IRON);
    resources.push_back(Place::IRON);
    resources.push_back(Place::WHEAT);
    CHECK(p1.checkListResources(resources)==true);
    p1.buyDevelopmentCard(&developmentCard, DevelopmentCard::MONOPOLY);
    catan.endTurn();

    CHECK(p1.getTurn()==false);
    CHECK(p1.getPoints()==2);
    CHECK(p2.getTurn()==true);

    CHECK(catan.isabletoplace(24, Settlement::VILLAGE, &p2, true) == true);
    CHECK(catan.isabletoplace(44, Settlement::VILLAGE, &p1, true) == false);
    CHECK(catan.isabletoplace(55, Settlement::NONESettlement, &p1, true) == false);
    CHECK(catan.isabletoplace(55, Settlement::NONESettlement, &p2, true) == true);
    CHECK(catan.isabletoplace(54, Settlement::NONESettlement, &p2, true) == true);
    CHECK(catan.isabletoplace(55, Settlement::NONESettlement, &p2, true) == false);
    CHECK(catan.isabletoplace(43, Settlement::VILLAGE, &p2, false) == false);
    CHECK(catan.isabletoplace(42, Settlement::VILLAGE, &p2, true) == true);
    //there is no card
    CHECK(catan.placeRoadCard(53, 51, &p2) == false);
        //check resources
    std::list<int> resources2;
    resources2.push_back(Place::WOOD);
    resources2.push_back(Place::BRICK);
    resources2.push_back(Place::WOOL);
    resources2.push_back(Place::IRON);
    resources2.push_back(Place::WHEAT);
    CHECK(p2.checkListResources(resources2)==true);

//monopoly
    p2.updateONEResource(Place::WOOD, true);
    p3.updateONEResource(Place::WOOD, true);
    p1.setTurn(true);
    CHECK(p1.monopolyCard(Place::WOOD, catan) == true);
    std::list<int> resources3;
    resources3.push_back(Place::WOOD);
    resources3.push_back(Place::WOOD);
    resources3.push_back(Place::WOOL);
    resources3.push_back(Place::IRON);
    resources3.push_back(Place::WOOD);
    resources3.push_back(Place::WOOD);
    CHECK(p2.checkListResources(resources2)==true);
    CHECK(p1.checkListResources(resources3)==true);
    std::list<int> resources4;
    resources4.push_back(Place::BRICK);
    resources4.push_back(Place::WOOL);
    resources4.push_back(Place::IRON);
    resources4.push_back(Place::WHEAT);
    CHECK(p2.checkListResources(resources4)==true);
    
//roads card and points
    p1.updateONEResource(Place::WHEAT, true);
    p1.updateONEResource(Place::WOOL, true);
    p1.updateONEResource(Place::IRON, true);
    p1.buyDevelopmentCard(&developmentCard, DevelopmentCard::FREE_ROADS);
    CHECK(catan.placeRoadCard(63, 62, &p1) == false);
    CHECK(catan.placeRoadCard(65, 66, &p1) == true);
    CHECK(catan.isabletoplace(43, Settlement::NONESettlement, &p1, false) == false);
    p1.updateONEResource(Place::BRICK, true);
    CHECK(catan.isabletoplace(43, Settlement::NONESettlement, &p1, false) == true);
    CHECK(p1.getPoints() == 4);
    CHECK(catan.isabletoplace(32, Settlement::CITY, &p1, false) == false);


// Roll dice and check resources
    p2.setTurn(false);
    catan.rollDice(p2,5);
    std::list<int> resources5;
    resources5.push_back(Place::WOOD);
    resources5.push_back(Place::WOOD);
    resources5.push_back(Place::WOOL);
    resources5.push_back(Place::WOOL);
    resources5.push_back(Place::WOOL);
    resources5.push_back(Place::IRON);
    resources5.push_back(Place::WOOD);
    CHECK(p1.checkListResources(resources5)==false);
    catan.rollDice(p1,5);
    CHECK(p1.checkListResources(resources5)==true);
    CHECK(p2.checkListResources(resources4)==true);
    catan.rollDice(p1,6);
    resources4.push_back(Place::IRON);
    CHECK(p2.checkListResources(resources4)==true);
    
    //update city buy village
    catan.endTurn();
    CHECK(p1.getTurn()==false);
    CHECK(p2.getTurn()==true);
    catan.rollDice(p2,6);
    resources4.push_back(Place::IRON);
    CHECK(catan.isabletoplace(42,Settlement::CITY,&p2,false)==false);
    CHECK(p2.checkListResources(resources4)==true);
    catan.rollDice(p2,6);
    resources4.push_back(Place::IRON);
    p2.updateONEResource(Place::WHEAT,true);
    resources4.push_back(Place::WHEAT);
    p2.updateONEResource(Place::WHEAT,true);
    p2.updateONEResource(Place::WHEAT,false);
    CHECK(p2.checkResourcesCITY()==true);
    CHECK(p2.checkListResources(resources4)==true);
    
    CHECK(catan.isabletoplace(1,Settlement::CITY,&p2,false)==false);

    p2.updateONEResource(Place::BRICK,true);
    p2.updateONEResource(Place::BRICK,true);
    p2.updateONEResource(Place::WOOD,true);
    p2.updateONEResource(Place::WOOD,true);
    p2.updateONEResource(Place::WOOD,true);
    CHECK(catan.isabletoplace(53,Settlement::NONESettlement,&p2,false)==true);
    CHECK(catan.isabletoplace(51,Settlement::NONESettlement,&p2,false)==true);
    p2.updateONEResource(Place::WOOD,true);
    //closest to village
    CHECK(catan.isabletoplace(43,Settlement::VILLAGE,&p2,false)==false);
    CHECK(catan.isabletoplace(44,Settlement::VILLAGE,&p2,false)==true);
    CHECK(p2.getPoints() == 3);
    p2.updateONEResource(Place::BRICK,true);
    p2.updateONEResource(Place::BRICK,true);
    p2.updateONEResource(Place::WOOD,true);
    p2.updateONEResource(Place::WOOD,true);
    CHECK(catan.isabletoplace(52,Settlement::NONESettlement,&p2,false)==true);
    CHECK(catan.isabletoplace(22,Settlement::NONESettlement,&p2,false)==true);
    CHECK(p1.getPoints() ==2);
    CHECK(p2.getPoints() == 5);
    //p2 has most roads
    p2.updateONEResource(Place::WHEAT,true);
    
    //if it has 7 in sum dice
    CHECK(p1.getResourcesSize() == 10);
    CHECK(p2.getResourcesSize()==7);
    catan.rollDice(p2,7);
    CHECK(p1.getResourcesSize() == 5);
    CHECK(p2.getResourcesSize()==7);

    //create city and check if it replaced from village
    CHECK(catan.isabletoplace(42,Settlement::CITY,&p2,false)==true);
    CHECK(p2.getPoints() == 6);
    CHECK(p2.getVillages().size()==2);
    CHECK(p2.getCities().size()==1);
    cout << "----------------" << endl;
}
