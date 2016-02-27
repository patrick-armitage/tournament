/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/22/2016
** Description: Loserpile methods file which defines the methods of the
** Loserpile class that were prototyped within the Loserpile header file
*******************************************************************************/
#include <iostream>

#include "Loserpile.hpp"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------------*/
/*
    Function Name: Loserpile
    Function Parameters: loser Creature object
    What the function does: adds a new loser to the Loserpile
*/
Loserpile::Loserpile() {
    setCurrentLoser(NULL);
}

/*----------------------------------------------------------------------------*/
/*
    Function Names: setCurrentLoser, getCurrentLoser
    Functions' Parameters: setter receives loser Creatureeger param for queue loser
    What the functions do: getter and setter which act as public options to
                           read/write the Queue class's private queueLoser
*/
void Loserpile::setCurrentLoser(Loser *loser) {
    currentLoser = loser;
}

Loser *Loserpile::getCurrentLoser() {
    return currentLoser;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: add
    Function Parameters: loser Creature object
    What the function does: initializes a new Loser struct, settings its
                            previous stack loser to NULL, and its loser
                            to the provided loser Creatureeger.  Then gets the current
                            stack loser and sets it as the current loser.
*/
void Loserpile::add(Creature *loser) {
    Loser *stackLoser = new Loser;
    Loser *currLoser = getCurrentLoser();
    stackLoser->previousLoser = currLoser;
    stackLoser->loser = loser;
    setCurrentLoser(stackLoser);
    cout << "Added " << getCurrentLoser()->loser->getCreatureName() << " ";
    cout << getCurrentLoser()->loser->getCharaName() << " to the Loserpile!" << endl;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: remove
    Function Parameters: N/A
    What the function does: gets the current stack loser and the previos loser from
                            the current loser, then sets the previous loser as the
                            new current loser, deleting the old current loser and
                            returning its loser Creatureeger
*/
Creature *Loserpile::remove() {
    Loser *currLoser = getCurrentLoser();
    Loser *prevLoser = currLoser->previousLoser;

    setCurrentLoser(prevLoser);
    Creature *loser = currLoser->loser;
    delete currLoser;
    return loser;
}
