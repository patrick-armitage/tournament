/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Vampire class prototypes, which inherit all data members, getters
** and setters from the Creature base class, and implement the virtual functions
** attack, defend, charm and updateStrengthPts, and also a constructor and a
** Vampire-only vampWink method
*******************************************************************************/

#include <string>
#include "Creature.hpp"

#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP

using std::string;

class Vampire : public Creature {
 public:
    Vampire(string name, string cName);
    int attack();
    int defend();
    bool charm();
    void vampWink();
    void updateStrengthPts(int defenseRoll, int opponentAttackRoll);
};

#endif
