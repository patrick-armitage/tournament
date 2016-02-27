/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Barbarian class prototypes, which inherit all data members,
** getters and setters from the Creature base class, and implements the virtual
** functions attack, defend, charm and updateStrengthPts, and the constructor
*******************************************************************************/

#include <string>
#include "Creature.hpp"

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

using std::string;

class Barbarian : public Creature {
 public:
    Barbarian(string name, string cName);
    int attack();
    int defend();
    bool charm();
    void updateStrengthPts(int defenseRoll, int opponentAttackRoll);
};

#endif
