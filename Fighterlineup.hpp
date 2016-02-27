/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/22/2016
** Description: Fighterlineup class prototype which defines the Fighter struct,
** getters and setters, the constructor, and the add and remove figher functions
*******************************************************************************/

#include <string>
#include "Creature.hpp"

#ifndef FIGHTERLINEUP_HPP
#define FIGHTERLINEUP_HPP

using std::string;

struct Fighter {
    Fighter *nextFighter;
    Fighter *previousFighter;
    Creature *fighter;
};

class Fighterlineup {
 private:
    string teamName;
    Fighter *currentFighter;
 public:
    Fighterlineup(string teamName);
    string getTeamName();
    Fighter *getCurrentFighter();
    void setTeamName(string teamName);
    void setCurrentFighter(Fighter *fighter);
    void add(Creature *fighter);
    Creature *remove();
};

#endif
