/**
 * Demo file for Ex3.
 *
 */
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
using namespace std;
using namespace ariel;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Amit");
    DevelopmentCard developmentCard;
    Board board;
    Catan catan(&p1,&p2, &p3,&board,&developmentCard);
    cout << catan.ChooseStartingPlayer()->getName()<<" start the game" << endl;
    if(!catan.isabletoplace(32,Settlement::VILLAGE,&p1,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(50,Settlement::VILLAGE,&p1,true))
        cout << "---wasn't according to game logic" << endl;
    //Yossi not your turn 
    if(!catan.isabletoplace(5,Settlement::VILLAGE,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(5,Settlement::VILLAGE,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(50,Settlement::VILLAGE,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(62,Settlement::NONESettlement,&p1,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(36,Settlement::NONESettlement,&p1,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(63,Settlement::NONESettlement,&p1,true))
        cout << "---wasn't according to game logic" << endl;
    p1.printResources();
    cout << "----------------" << endl;
    catan.endTurn();
    if(!catan.isabletoplace(32,Settlement::VILLAGE,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(46,Settlement::VILLAGE,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(17,Settlement::VILLAGE,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(62,Settlement::NONESettlement,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(17,Settlement::NONESettlement,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(16,Settlement::NONESettlement,&p2,true))
        cout << "---wasn't according to game logic" << endl;
    p2.printResources();
    cout << "----------------" << endl;
    catan.endTurn();
    if(!catan.isabletoplace(30,Settlement::VILLAGE,&p3,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(22,Settlement::VILLAGE,&p3,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(52,Settlement::NONESettlement,&p3,true))
        cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(30,Settlement::NONESettlement,&p3,true))
        cout << "---wasn't according to game logic" << endl;
    p3.printResources();
    cout << "----------------" << endl;
    catan.endTurn();
    catan.rollDice(p1,5);
    p1.printResources();
    p1.trade(&p2,Place::WOOL,Place::WOOD,2,1);
    p1.printResources();
    cout << "----------------" << endl;
    catan.endTurn();
    catan.rollDice(p2,8);
    p2.printResources();
    p2.buyDevelopmentCard(&developmentCard,DevelopmentCard::FREE_RESOURCES);
    p2.freeResources(Place::WOOD,Place::BRICK);
    p2.printResources();
    p2.trade(&p3,Place::WOOD,Place::WHEAT,1,1);
    p2.trade(&p3,Place::BRICK,Place::WHEAT,1,1);
    p2.printResources();
    cout << "----------------" << endl;
    catan.endTurn();
    catan.rollDice(p3,9);
    p3.printResources();
    if(!catan.isabletoplace(29,Settlement::NONESettlement,&p3,false))
         cout << "---wasn't according to game logic" << endl;
    if(!catan.isabletoplace(28,Settlement::VILLAGE,&p3,false))
         cout << "---wasn't according to game logic" << endl;
    p3.printResources();
    cout << "----------------" << endl;
    catan.endTurn();
    catan.printWinner();
}