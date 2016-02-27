/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Medusa class prototypes, which inherit all data members, getters
** and setters from the Creature base class, and implement the virtual functions
** attack, defend, charm and updateStrengthPts, and also a constructor and a
** Medusa-only glare method
*******************************************************************************/

#include <string>
#include "Creature.hpp"

#ifndef MEDUSA_HPP
#define MEDUSA_HPP

using std::string;

class Medusa : public Creature {
 public:
    Medusa(string name, string cName);
    int attack();
    int defend();
    bool charm();
    void glare();
    void updateStrengthPts(int defenseRoll, int opponentAttackRoll);
};

#endif
