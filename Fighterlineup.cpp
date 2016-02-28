/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/22/2016
** Description: Fighterlineup methods file which defines the methods of the
** Fighterlineup class that were prototyped within the Fighterlineup header file
*******************************************************************************/
#include <iostream>
#include <string>

#include "Fighterlineup.hpp"
#include "Creature.hpp"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------------*/
/*
    Function Name: Fighterlineup
    Function Parameters: data integer
    What the function does: sets the current queue fighter pointer to NULL, and
                            adds a new queue fighter to the queue
*/
Fighterlineup::Fighterlineup(string name) {
    setTeamName(name);
    setCurrentFighter(NULL);
}

/*----------------------------------------------------------------------------*/
/*
    Function Names: setCurrentFighter, getCurrentFighter, setTeamName, getTeamName
    Functions' Parameters: setters receive string name and Fighter struct
    What the functions do: getter and setter which act as public options to
                           read/write the Fighterlineup class's private members
*/

void Fighterlineup::setTeamName(string name) {
    teamName = name;
}

void Fighterlineup::setCurrentFighter(Fighter *fighter) {
    currentFighter = fighter;
}

string Fighterlineup::getTeamName() {
    return teamName;
}

Fighter *Fighterlineup::getCurrentFighter() {
    return currentFighter;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: add
    Function Parameters: data integer
    What the function does: initializes a new Fighter struct, settings its
                            next and previous queue fighters to NULL, and its data
                            to the provided data integer.  Then gets the current
                            queued fighter; if it is NULL (lineup empty), sets the
                            newly instantiated Fighter as current fighter and returns.
                            Else, recurses through each next fighter in the queue
                            until the last fighter is found and sets the newly
                            instantiated queue fighter as the last fighter's next fighter
*/
void Fighterlineup::add(Creature *fighter) {
    Fighter *queueFighter = new Fighter;
    queueFighter->nextFighter = NULL;
    queueFighter->previousFighter = NULL;
    queueFighter->fighter = fighter;

    Fighter *currFighter = getCurrentFighter();
    Fighter *lastFighter = currFighter;
    if (currFighter == NULL) {
        setCurrentFighter(queueFighter);
    } else {
        while (lastFighter->nextFighter != NULL) {
            lastFighter = lastFighter->nextFighter;
        }

        lastFighter->nextFighter = queueFighter;
        queueFighter->previousFighter = lastFighter;
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: remove
    Function Parameters: N/A
    What the function does: gets the current queued fighter and the next fighter from
                            the current fighter, then sets the next fighter as the new
                            current fighter, deleting the old current fighter and
                            returning its data integer
*/
Creature *Fighterlineup::remove() {
    Fighter *currFighter = getCurrentFighter();
    Fighter *nextFighter = currFighter->nextFighter;
    setCurrentFighter(nextFighter);

    Creature *fighter = currFighter->fighter;
    delete currFighter;
    return fighter;
}
