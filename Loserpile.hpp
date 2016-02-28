/**********************************************************************************
** Author: Patrick Armitage
** Date: 02/22/2016
** Description: Loserpile class prototype which defines the basic functionality
** for a pile, including the Loser struct, the current pile loser Creature pointer
** and its getter and setter, the constructor, and the add and remove loser
** pile methods
**********************************************************************************/

#include "Creature.hpp"

#ifndef LOSERPILE_HPP
#define LOSERPILE_HPP

struct Loser  {
    Loser  *previousLoser;
    Creature *loser;
};

class Loserpile {
 private:
    Loser  *currentLoser;
 public:
    Loserpile();
    Loser  *getCurrentLoser();
    void setCurrentLoser(Loser *loser);
    void add(Creature *loser);
    Creature *remove();
};

#endif
