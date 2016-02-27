/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Harry class prototypes, which inherit all data members, getters
** and setters from the Creature base class, and implement the virtual functions
** attack, defend, charm and updateStrengthPts, and also a constructor and a
** Harry-only hasRevived boolean with getter and setter methods
*******************************************************************************/

#include <string>
#include "Creature.hpp"

#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP

using std::string;

class Harrypotter : public Creature {
 private:
    bool hasRevived;

 public:
    Harrypotter(string name, string cName);
    void setHasRevived(bool hasRevived);
    bool getHasRevived();
    int attack();
    int defend();
    bool charm();
    void updateStrengthPts(int defenseRoll, int opponentAttackRoll);
};

#endif
