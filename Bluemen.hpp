/*********************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Blue Men class prototypes, which inherit all data members, getters
** and setters from the Creature base class, and implement the virtual functions
** attack, defend, charm and updateStrengthPts, and also a constructor and the
** Blue Men-only checkDefenseLevel and showTheBlueMen methods
*********************************************************************************/

#include <string>
#include "Creature.hpp"

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP

using std::string;

class Bluemen : public Creature {
 public:
    Bluemen(string name, string cName);
    int attack();
    int defend();
    bool charm();
    void updateStrengthPts(int defenseRoll, int opponentAttackRoll);
    void checkDefenseLevel();
    void showTheBlueMen(int strengthPts);
};

#endif
