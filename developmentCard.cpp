//314923822
//morberger444@gmail.com
#include "developmentCard.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>
using namespace std;
using namespace ariel;


DevelopmentCard::DevelopmentCard() {
    this->cards[MONOPOLY] = 5;
    this->cards[FREE_ROADS] = 5;
    this->cards[FREE_RESOURCES] = 5;
    this->cards[POINTS] = 4;
    this->cards[KNIGHT] = 3;
}

DevelopmentCard::~DevelopmentCard() {}

int DevelopmentCard::randomCard(int selectedCard) {
    if(this->cards[selectedCard]==0){
        return -1;
    } 
    this->cards[selectedCard]--;
    return selectedCard; 
}


