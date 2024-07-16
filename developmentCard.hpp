//314923822
//morberger444@gmail.com
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP
#include <ostream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

namespace ariel {
    class DevelopmentCard {
    private:
        int cards[5];

    public:
     enum CardType {
        MONOPOLY,
        FREE_ROADS,
        FREE_RESOURCES,
        POINTS,
        KNIGHT,
    };
        DevelopmentCard();
        ~DevelopmentCard();
        int randomCard(int selectedCard);
};
}

#endif